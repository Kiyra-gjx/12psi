package com.zeroone.star.storemanagement.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.*;
import com.zeroone.star.project.query.j2.store.BatchDetailQuery;
import com.zeroone.star.project.query.j2.store.BatchQuery;
import com.zeroone.star.storemanagement.mapper.BatchInfoMapper;
import com.zeroone.star.storemanagement.mapper.BatchListMapper;
import com.zeroone.star.storemanagement.service.IBatchQueryService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.math.BigDecimal;
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

    @Override
    public PageDTO<BatchListDTO> listBatch(BatchQuery query) {

            // 创建分页对象
            Page<BatchListDTO> page = new Page<>(query.getPageIndex(), query.getPageSize());

            // 1. 查询商品基本信息（第一层）
            Page<BatchListDTO> goodsPage = batchListMapper.selectBatchGoodsList(page, query);
            List<BatchListDTO> goodsList = goodsPage.getRecords();

            if (goodsList.isEmpty()) {
                return PageDTO.create(goodsPage);
            }

            // 提取商品ID列表
            List<String> goodsIds = goodsList.stream()
                    .map(BatchListDTO::getId)
                    .collect(Collectors.toList());

            // 2. 查询仓库库存信息（第一层）
            List<WarehouseStockDTO> warehouseStocks = batchListMapper.selectGoodsWarehouseStock(goodsIds);
            Map<String, List<WarehouseStockDTO>> warehouseStockMap = warehouseStocks.stream()
                    .collect(Collectors.groupingBy(WarehouseStockDTO::getGoodsId));

            // 3. 查询批次号信息（第二层）
            List<BatchNumberDTO> batchNumbers = batchListMapper.selectBatchNumbersByGoodsIds(goodsIds);
            // 直接使用 goodsId 字段进行分组
            Map<String, List<BatchNumberDTO>> batchNumberMap = batchNumbers.stream()
                    .collect(Collectors.groupingBy(BatchNumberDTO::getGoodsId));

            // 4. 查询批次详情信息（第三层）
            List<BatchDocumentDTO> batchDocuments = batchListMapper.selectBatchDocumentsByGoodsIds(goodsIds);

            // 按批次号分组批次详情
            Map<String, List<BatchDocumentDTO>> batchDocumentMap = batchDocuments.stream()
                    .collect(Collectors.groupingBy(BatchDocumentDTO::getBatchNumber));

            // 组装数据
            for (BatchListDTO goods : goodsList) {
                String goodsId = goods.getId();

                // 设置仓库库存信息（第一层）
                goods.setWarehouses(warehouseStockMap.getOrDefault(goodsId, new ArrayList<>()));

                // 设置批次信息（第二层 + 第三层）
                List<BatchNumberDTO> goodsBatchNumbers = batchNumberMap.getOrDefault(goodsId, new ArrayList<>());
                for (BatchNumberDTO batchNumber : goodsBatchNumbers) {
                    // 获取该批次号的所有详情（第三层）
                    List<BatchDocumentDTO> documents = batchDocumentMap.getOrDefault(
                            batchNumber.getBatchNumber(), new ArrayList<>());

                    // 设置批次详情
                    batchNumber.setBatchDocuments(documents);

                    // 根据第三层详情计算第二层的总库存
                    BigDecimal totalStock = documents.stream()
                            .map(BatchDocumentDTO::getNums)
                            .reduce(BigDecimal.ZERO, BigDecimal::add);
                    batchNumber.setTotalStock(totalStock);
                }
                goods.setBatches(goodsBatchNumbers);
            }

            // 返回分页结果
            PageDTO<BatchListDTO> pageDTO = PageDTO.create(goodsPage);
            return pageDTO;

    }


    /**
     * 获取指定批次详情数据（分页）
     * @param batchDetailQuery 查询条件对象，包含批次pid、单据类型、时间范围、单据编号等过滤条件以及分页参数
     * @return PageDTO<BatchDetailDTO> 分页后的批次详情数据列表，每条记录包含pid、time、type、number、info、nums等字段
     */
    public PageDTO<BatchDetailDTO> getBatchDetail(BatchDetailQuery batchDetailQuery) {
        // 创建分页对象
        Page<BatchDetailDTO> page = new Page<>(batchDetailQuery.getPageIndex(), batchDetailQuery.getPageSize());
        // 调用mapper层获取批次详情列表数据（分页）
        Page<BatchDetailDTO> resultPage = batchInfoMapper.getBatchDetail(page, batchDetailQuery);
        
        // 为每个批次详情设置所属组织
        // TODO: 后续可以通过其他方式获取实际的组织数据，目前使用默认值

        resultPage.getRecords().forEach(dto -> dto.setFrame("默认组织"));

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
            if (query.getGoodsId() != null) {
                exportQuery.setGoodsId(query.getGoodsId());
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
