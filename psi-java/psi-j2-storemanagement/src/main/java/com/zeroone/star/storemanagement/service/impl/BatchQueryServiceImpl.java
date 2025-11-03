package com.zeroone.star.storemanagement.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.*;
import com.zeroone.star.project.query.j2.store.BatchDetailQuery;
import com.zeroone.star.project.query.j2.store.BatchQuery;
import com.zeroone.star.storemanagement.mapper.BatchInfoMapper;
import com.zeroone.star.storemanagement.mapper.BatchListMapper;
import com.zeroone.star.storemanagement.service.IBatchQueryService;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collectors;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.service.impl
 * @Author: 高
 * @CreateTime: 2025-10-24 20:16
 * @Description: 批次查询服务实现类
 * @Version: 1.0
 */
@Service
@Slf4j
public class BatchQueryServiceImpl implements IBatchQueryService {

    @Resource
    private BatchInfoMapper batchInfoMapper;

    @Resource
    private BatchListMapper batchListMapper;

    @Resource
    private EasyExcelComponent easyExcelComponent;

    @Resource
    UserHolder userHolder;

    @Override
    public PageDTO<BatchListDTO> listBatch(BatchQuery query) {
        try {
            // 处理分类递归查询
            if (query.getGoodsCategoryId() != null && !query.getGoodsCategoryId().isEmpty()) {
                Set<String> allCategoryIds = getCategoryTreeIds(query.getGoodsCategoryId());
                query.setGoodsCategoryIds(new ArrayList<>(allCategoryIds));
            }

            // 创建分页对象
            Page<BatchListDTO> page = new Page<>(query.getPageIndex(), query.getPageSize());

            // 1. 查询商品基本信息（第一层）
            Page<BatchListDTO> goodsPage = batchListMapper.selectBatchGoodsList(page, query);
            List<BatchListDTO> goodsList = goodsPage.getRecords();

            if (goodsList.isEmpty()) {
                return PageDTO.create(goodsPage);
            }

            // 注意：不管是不是预警批次，都过滤没有库存记录的商品
            goodsList = goodsList.stream()
                    .filter(goods -> goods.getTotalStock().compareTo(BigDecimal.ZERO) > 0)
                    .collect(Collectors.toList());

            // 如果过滤后没有商品，直接返回空结果
            if (goodsList.isEmpty()) {
                goodsPage.setRecords(new ArrayList<>());
                goodsPage.setTotal(0);
                return PageDTO.create(goodsPage);
            }

            // 更新分页对象的记录
            goodsPage.setRecords(goodsList);
            goodsPage.setTotal(goodsList.size());

            // 提取商品ID列表和商品信息
            List<String> goodsIds = goodsList.stream()
                    .map(BatchListDTO::getId)
                    .collect(Collectors.toList());

            Map<String, BigDecimal> goodsStockMap = goodsList.stream()
                    .collect(Collectors.toMap(BatchListDTO::getId, BatchListDTO::getStock));

            Map<String, Integer> goodsProtectMap = goodsList.stream()
                    .collect(Collectors.toMap(BatchListDTO::getId, BatchListDTO::getProtect));

            // 2. 查询商品属性信息
            List<BatchAttrDTO> attrStocks = batchListMapper.selectGoodsAttrStock(goodsIds, query);
            Map<String, List<BatchAttrDTO>> goodsAttrMap = attrStocks.stream()
                    .collect(Collectors.groupingBy(BatchAttrDTO::getGoodsId));

            // 3. 查询批次详情信息
            List<BatchDocumentDTO> allBatchDocuments = batchListMapper.selectBatchDocumentsByGoodsIds(goodsIds, query);

            // 4. 设置预警状态和过期日期
            for (BatchDocumentDTO document : allBatchDocuments) {
                BigDecimal stockThreshold = goodsStockMap.get(document.getGoodsId());
                document.setIsWarning(document.getNums().compareTo(stockThreshold) <= 0);

                // 计算过期日期：生产日期 + 保质期天数
                Integer protectDays = goodsProtectMap.get(document.getGoodsId());
                if (document.getProductDate() != null && protectDays != null && protectDays > 0) {
                    LocalDate expireDate = document.getProductDate().plusDays(protectDays);
                    document.setExpireDate(expireDate);
                }
            }

            // 5. 按商品ID、属性名称、批次号进行分组
            Map<String, Map<String, Map<String, List<BatchDocumentDTO>>>> batchGroupMap = allBatchDocuments.stream()
                    .collect(Collectors.groupingBy(
                            BatchDocumentDTO::getGoodsId,
                            Collectors.groupingBy(
                                    dto -> {
                                        // 修正无属性商品的处理
                                        if (dto.getAttrName() == null || dto.getAttrName().isEmpty()) {
                                            return "NO_ATTR";
                                        }
                                        return dto.getAttrName();
                                    },
                                    Collectors.groupingBy(BatchDocumentDTO::getBatchNumber)
                            )
                    ));

            // 6. 组装数据
            for (BatchListDTO goods : goodsList) {
                String goodsId = goods.getId();
                BigDecimal stockThreshold = goods.getStock();

                // 判断商品是否有属性
                List<BatchAttrDTO> attrs = goodsAttrMap.get(goodsId);
                boolean hasAttr = attrs != null && !attrs.isEmpty();

                goods.setHasAttr(hasAttr);

                if (hasAttr) {
                    // 有属性商品：按属性分组
                    List<BatchAttrDTO> attrBatches = new ArrayList<>();

                    for (BatchAttrDTO attr : attrs) {
                        BatchAttrDTO attrDTO = new BatchAttrDTO();
                        attrDTO.setAttrName(attr.getAttrName());
                        attrDTO.setAttrStock(attr.getAttrStock());

                        // 获取该属性下的批次信息
                        Map<String, Map<String, List<BatchDocumentDTO>>> goodsBatchMap = batchGroupMap.getOrDefault(goodsId, new HashMap<>());
                        Map<String, List<BatchDocumentDTO>> attrBatchMap = goodsBatchMap.getOrDefault(attr.getAttrName(), new HashMap<>());

                        List<BatchNumberDTO> batchNumbers = buildBatchNumbers(attrBatchMap, stockThreshold, query);
                        attrDTO.setBatches(batchNumbers);

                        attrBatches.add(attrDTO);
                    }

                    goods.setAttrBatches(attrBatches);
                    goods.setNoAttrBatches(new ArrayList<>());
                } else {
                    // 无属性商品：直接显示批次
                    Map<String, Map<String, List<BatchDocumentDTO>>> goodsBatchMap = batchGroupMap.getOrDefault(goodsId, new HashMap<>());
                    Map<String, List<BatchDocumentDTO>> noAttrBatchMap = goodsBatchMap.getOrDefault("NO_ATTR", new HashMap<>());

                    List<BatchNumberDTO> batchNumbers = buildBatchNumbers(noAttrBatchMap, stockThreshold, query);

                    // 只有当有批次数据时才设置
                    if (!batchNumbers.isEmpty()) {
                        goods.setNoAttrBatches(batchNumbers);
                    } else {
                        goods.setNoAttrBatches(new ArrayList<>());
                    }
                    goods.setAttrBatches(new ArrayList<>());
                }
            }

            return PageDTO.create(goodsPage);

        } catch (Exception e) {
            log.error("查询批次列表失败", e);
            throw new RuntimeException("查询批次列表失败", e);
        }
    }

    /**
     * 递归获取类别树的所有ID
     */
    private Set<String> getCategoryTreeIds(String categoryId) {
        Set<String> result = new HashSet<>();
        result.add(categoryId);
        findChildCategoriesRecursive(categoryId, result);
        return result;
    }

    /**
     * 具体的递归方法
     */
    private void findChildCategoriesRecursive(String parentId, Set<String> result) {
        List<String> childIds = batchListMapper.selectChildCategoryIds(parentId);
        if (childIds != null && !childIds.isEmpty()) {
            for (String childId : childIds) {
                if (!result.contains(childId)) {
                    result.add(childId);
                    findChildCategoriesRecursive(childId, result);
                }
            }
        }
    }

    private List<BatchNumberDTO> buildBatchNumbers(Map<String, List<BatchDocumentDTO>> batchMap, BigDecimal stockThreshold, BatchQuery query) {
        List<BatchNumberDTO> batchNumbers = new ArrayList<>();

        for (Map.Entry<String, List<BatchDocumentDTO>> entry : batchMap.entrySet()) {
            String batchNumber = entry.getKey();
            List<BatchDocumentDTO> documents = entry.getValue();

            // 判断批次号是否预警：只要有一个明细记录 nums <= stock
            boolean isBatchWarning = documents.stream()
                    .anyMatch(doc -> doc.getNums().compareTo(stockThreshold) <= 0);

            // 如果是预警批次查询，只显示预警的批次
            if (query.getBatchState() != null && query.getBatchState() == 1 && !isBatchWarning) {
                continue; // 跳过非预警批次
            }

            BatchNumberDTO batchNumberDTO = new BatchNumberDTO();
            batchNumberDTO.setBatchNumber(batchNumber);
            batchNumberDTO.setBatchDocuments(documents);

            // 计算该批次总库存
            BigDecimal totalStock = documents.stream()
                    .map(BatchDocumentDTO::getNums)
                    .reduce(BigDecimal.ZERO, BigDecimal::add);
            batchNumberDTO.setTotalStock(totalStock);
            batchNumberDTO.setIsWarning(isBatchWarning);

            batchNumbers.add(batchNumberDTO);
        }

        return batchNumbers;
    }


    /**
     * 获取指定批次详情数据（分页）
     * @param batchDetailQuery 查询条件对象，包含批次pid、单据类型、时间范围、单据编号等过滤条件以及分页参数
     * @return PageDTO<BatchDetailDTO> 分页后的批次详情数据列表，每条记录包含pid、time、type、number、info、nums等字段
     */
    @SneakyThrows
    public PageDTO<BatchDetailDTO> getBatchDetail(BatchDetailQuery batchDetailQuery) {
        // 创建分页对象
        Page<BatchDetailDTO> page = new Page<>(batchDetailQuery.getPageIndex(), batchDetailQuery.getPageSize());
        // 调用mapper层获取批次详情列表数据（分页）
        Page<BatchDetailDTO> resultPage = batchInfoMapper.getBatchDetail(page, batchDetailQuery);
        
        // 为每个批次详情设置所属组织
        // 从当前用户获取组织名称
        UserDTO user = userHolder.getCurrentUser();
        resultPage.getRecords().forEach(dto -> dto.setFrame(user != null ? user.getFrameName() : "默认组织"));

        return PageDTO.create(resultPage);
    }

    /**
     * 导出批次列表到Excel
     *
     * @param query 批次查询条件
     * @return Excel文件字节流
     * @throws IOException IO异常
     */
    @Override
    public ByteArrayOutputStream exportBatchListExcel(BatchQuery query) throws IOException {
        try {
            log.info("开始导出批次列表Excel，查询条件: {}", query);

            // 设置一个较大的分页查询，获取所有数据用于导出
            // 如果数据量特别大，可以考虑分批导出
            BatchQuery exportQuery = new BatchQuery();
            exportQuery.setPageIndex(1L);
            exportQuery.setPageSize(10000L);  // 设置一个较大的数字获取所有数据

            // 复制原查询条件的过滤参数
            if (query.getGoodsName() != null) {
                exportQuery.setGoodsName(query.getGoodsName());
            }
            if (query.getGoodsNumber() != null) {
                exportQuery.setGoodsNumber(query.getGoodsNumber());
            }
            if (query.getBatchNumber() != null) {
                exportQuery.setBatchNumber(query.getBatchNumber());
            }
            if (query.getProductDate() != null) {
                exportQuery.setProductDate(query.getProductDate());
            }
            if (query.getGoodsSpec() != null) {
                exportQuery.setGoodsSpec(query.getGoodsSpec());
            }
            if (query.getGoodsCategoryId() != null) {
                exportQuery.setGoodsCategoryId(query.getGoodsCategoryId());
            }
            if (query.getGoodsBrand() != null) {
                exportQuery.setGoodsBrand(query.getGoodsBrand());
            }
            if (query.getGoodsCode() != null) {
                exportQuery.setGoodsCode(query.getGoodsCode());
            }
            if (query.getBatchState() != null) {
                exportQuery.setBatchState(query.getBatchState());
            }

            // 查询数据
            PageDTO<BatchListDTO> batchData = this.listBatch(exportQuery);
            List<BatchListDTO> dataList = batchData.getRows();

            if (dataList == null || dataList.isEmpty()) {
                log.warn("批次列表数据为空，将导出空Excel");
                dataList = new ArrayList<>();
            }

            // 使用EasyExcel组件导出数据
            ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
            easyExcelComponent.export("批次列表", outputStream, BatchListDTO.class, dataList);

            log.info("成功导出批次列表Excel，共{}条记录", dataList.size());
            return outputStream;

        } catch (Exception e) {
            log.error("导出批次列表Excel失败", e);
            throw new IOException("导出批次列表Excel失败: " + e.getMessage(), e);
        }
    }

    /**
     * 导出批次详情到Excel
     * @param query 批次详情查询条件
     * @return Excel文件字节流
     * @throws IOException IO异常
     */
    @Override
    public ByteArrayOutputStream exportBatchDetailExcel(BatchDetailQuery query) throws IOException {
        try {
            log.info("开始导出批次详情Excel，批次ID: {}", query.getPid());

            // 设置一个较大的分页查询，获取所有数据用于导出
            BatchDetailQuery exportQuery = new BatchDetailQuery();
            exportQuery.setPageIndex(1L);
            exportQuery.setPageSize(10000L);  // 设置一个较大的数字获取所有数据
            exportQuery.setPid(query.getPid());  // 设置批次ID

            // 复制原查询条件的过滤参数
            if (query.getNumber() != null) {
                exportQuery.setNumber(query.getNumber());
            }
            if (query.getType() != null) {
                exportQuery.setType(query.getType());
            }
            if (query.getStartTime() != null) {
                exportQuery.setStartTime(query.getStartTime());
            }
            if (query.getEndTime() != null) {
                exportQuery.setEndTime(query.getEndTime());
            }

            // 查询数据
            PageDTO<BatchDetailDTO> detailData = this.getBatchDetail(exportQuery);
            List<BatchDetailDTO> dataList = detailData.getRows();

            if (dataList == null || dataList.isEmpty()) {
                log.warn("批次详情数据为空，将导出空Excel");
                dataList = new ArrayList<>();
            }

            // 使用EasyExcel组件导出数据
            ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
            easyExcelComponent.export("批次详情", outputStream, BatchDetailDTO.class, dataList);

            log.info("成功导出批次详情Excel，共{}条记录", dataList.size());
            return outputStream;

        } catch (Exception e) {
            log.error("导出批次详情Excel失败", e);
            throw new IOException("导出批次详情Excel失败: " + e.getMessage(), e);
        }
    }
}
