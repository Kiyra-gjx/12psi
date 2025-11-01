package com.zeroone.star.storemanagement.service.impl;


import cn.hutool.core.date.DateTime;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import java.math.BigDecimal;
import java.util.ArrayList;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsClientComponent;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.*;
import com.zeroone.star.project.query.j2.store.InventoryDetailQuery;
import com.zeroone.star.project.query.j2.store.InventoryQuery;
import com.zeroone.star.storemanagement.mapper.InventoryDetailMapper;
import com.zeroone.star.storemanagement.mapper.InventoryMapper;
import com.zeroone.star.storemanagement.service.IInventoryQueryService;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.util.*;
import java.util.stream.Collectors;
@Service
@Slf4j
public class InventoryQueryServiceImpl  implements IInventoryQueryService {

    @Resource
    private InventoryMapper inventoryMapper;


    @Resource
    private InventoryDetailMapper inventoryDetailMapper;

    @Resource
    private FastDfsClientComponent dfs;
    @Resource
    private EasyExcelComponent excel;
    @Resource
    UserHolder userHolder;

    /**
     * 获取库存列表数据（分页）
     * @param query 查询条件对象，包含商品ID、仓库ID、辅助属性ID、时间范围、库存数量范围、库存状态等过滤条件以及分页参数
     * @return PageDTO<InventoryListDTO> 分页后的库存列表数据，每条记录包含商品ID、商品名称、仓库ID、仓库名称、辅助属性ID、辅助属性名称、库存数量、库存状态等字段
     */
    @Override
    public PageDTO<InventoryListDTO> getInventoryList(InventoryQuery query) {
        // 如果传入了类别ID，递归查询所有子孙类别
        if (query.getGoodsCategoryId() != null && !query.getGoodsCategoryId().isEmpty()) {
            Set<String> allCategoryIds = getCategoryTreeIds(query.getGoodsCategoryId());
            query.setGoodsCategoryIds(new ArrayList<>(allCategoryIds));
        }

        //1.查询商品的基本信息（分页）
        Page<InventoryListDTO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        Page<InventoryListDTO> goodsPage = inventoryMapper.selectInventoryBaseList(page, query);

        if (goodsPage.getRecords().isEmpty()){
            return PageDTO.create(goodsPage);
        }

        //提取商品ID列表
        List<String> goodIds = goodsPage.getRecords().stream()
                .map(InventoryListDTO::getId)
                .collect(Collectors.toList());

        //2.查询属性信息
        List<AttrStockDTO> attributes = inventoryMapper.selectAttrStockByGoodsIds(goodIds);

        //3.查询仓库信息
        List<WarehouseStockDTO> warehouseStocks = inventoryMapper.selectWarehouseStockByGoodsIds(goodIds, query.getWarehouseId());

        //4.组装数据
        assembleInventoryData(goodsPage.getRecords(), attributes, warehouseStocks);

        // 5. 根据库存状态过滤
        if (query.getStockState() != null) {
            filterByStockState(goodsPage.getRecords(), query.getStockState(), query.getWarehouseId());
        }

        return PageDTO.create(goodsPage);
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
        List<String> childIds = inventoryMapper.selectChildCategoryIds(parentId);
        if (childIds != null && !childIds.isEmpty()) {
            for (String childId : childIds) {
                if (!result.contains(childId)) {
                    result.add(childId);
                    findChildCategoriesRecursive(childId, result);
                }
            }
        }
    }

    /**
     * 组装库存数据
     */
    private void assembleInventoryData(List<InventoryListDTO> goodsList,
                                       List<AttrStockDTO> attributes,
                                       List<WarehouseStockDTO> warehouseStocks){
        //1.将库存信息构建两层Map：goodsId->attrId -> List<WarehouseStockDTO>
        Map<String, Map<String, List<WarehouseStockDTO>>> warehouseGroupMap = warehouseStocks.stream()
                .collect(Collectors.groupingBy(
                        WarehouseStockDTO::getGoodsId,
                        Collectors.groupingBy(WarehouseStockDTO::getAttrId)
                ));

        //2.将属性信息构建Map：goodsId->List<AttrStockDTO>
        Map<String, List<AttrStockDTO>> goodsAttrMap = attributes.stream()
                .collect(Collectors.groupingBy(AttrStockDTO::getPid));

        //执行组装逻辑
        for (InventoryListDTO goods : goodsList){
            String goodsId = goods.getId();

            //获取商品的所有库存分组
            Map<String, List<WarehouseStockDTO>> goodsStockMap = warehouseGroupMap.getOrDefault(goodsId, new HashMap<>());

            //判断是否有属性
            boolean hasAttributes = goodsAttrMap.containsKey(goodsId);

            if(hasAttributes){
                //有属性值
                List<AttrStockDTO> goodAttrs = goodsAttrMap.get(goodsId);
                List<AttrStockDTO> validAttrs = new ArrayList<>(); // 用于存储所有属性
                List<WarehouseStockDTO> allWarehouseStocks = new ArrayList<>(); // 存储所有仓库库存信息

                for (AttrStockDTO attr : goodAttrs){
                    //给每个属性设置库存
                    List<WarehouseStockDTO> attrStocks = goodsStockMap.getOrDefault(attr.getAttrId(), new ArrayList<>());
                    attr.setWarehouses(attrStocks);

                    //计算属性总库存
                    BigDecimal attrTotalStock = attrStocks.stream()
                            .map(WarehouseStockDTO::getStockNum)
                            .reduce(BigDecimal.ZERO, BigDecimal::add);
                    attr.setTotalStock(attrTotalStock);

                    // 确保所有属性都被保留
                    validAttrs.add(attr);

                    // 将属性库存信息添加到总仓库列表中
                    allWarehouseStocks.addAll(attrStocks);
                }
                goods.setAttrs(validAttrs);

                // 有属性时，warehouses按仓库分组计算库存总和
                Map<String, WarehouseStockDTO> warehouseSumMap = new HashMap<>();
                for (WarehouseStockDTO stock : allWarehouseStocks) {
                    String warehouseId = stock.getWarehouseId();
                    if (!warehouseSumMap.containsKey(warehouseId)) {
                        // 创建新的仓库汇总对象
                        WarehouseStockDTO sumStock = new WarehouseStockDTO();
                        sumStock.setWarehouseId(warehouseId);
                        sumStock.setWarehouseName(stock.getWarehouseName());
                        sumStock.setGoodsId(goodsId);
                        sumStock.setStockNum(BigDecimal.ZERO);
                        warehouseSumMap.put(warehouseId, sumStock);
                    }
                    // 累加库存
                    WarehouseStockDTO sumStock = warehouseSumMap.get(warehouseId);
                    sumStock.setStockNum(sumStock.getStockNum().add(stock.getStockNum()));
                }
                goods.setWarehouses(new ArrayList<>(warehouseSumMap.values()));

            }else{
                //没有属性值
                //设置商品库存列表
                List<WarehouseStockDTO> goodsStock = goodsStockMap.getOrDefault("", new ArrayList<>());
                goods.setWarehouses(goodsStock);
                goods.setAttrs(new ArrayList<>());
            }
        }
    }

    /**
     * 根据库存状态过滤
     * @param goodsList 商品列表
     * @param stockState 库存状态
     * @param selectedWarehouseIds 选中的仓库ID列表
     */
    private void filterByStockState(List<InventoryListDTO> goodsList, Integer stockState, List<String> selectedWarehouseIds) {
        if (stockState == 1) {
            // 非零库存过滤
            filterNonZeroStock(goodsList);
        } else if (stockState == 2) {
            // 预警库存过滤
            filterWarningStock(goodsList, selectedWarehouseIds);
        }
        // stockState == 0 常规库存，不进行过滤
    }

    /**
     * 预警库存过滤
     */
    private void filterWarningStock(List<InventoryListDTO> goodsList, List<String> selectedWarehouseIds) {
        Iterator<InventoryListDTO> iterator = goodsList.iterator();
        while (iterator.hasNext()) {
            InventoryListDTO goods = iterator.next();
            boolean hasWarning = false;

            // 1.检查商品是否有预警
            if (goods.getAttrs() != null && !goods.getAttrs().isEmpty()) {
                // 1.1有属性商品：检查每个属性是否有预警
                Iterator<AttrStockDTO> attrIterator = goods.getAttrs().iterator();
                while (attrIterator.hasNext()) {
                    AttrStockDTO attr = attrIterator.next();

                    // 检查单个属性是否有预警
                    boolean attrHasWarning = checkIfAttributeHasWarningStock(attr, goods.getStock(), selectedWarehouseIds);

                    if (attrHasWarning) {
                        hasWarning = true;
                        // 有预警，保留该属性
                    } else {
                        // 没有预警，移除该属性
                        attrIterator.remove();
                    }
                }
                // 如果所有属性都被移除了，商品本身也没有预警
                if (goods.getAttrs().isEmpty()) {
                    hasWarning = false;
                }
            } else {
                // 1.2无属性商品：检查商品是否有预警
                hasWarning = checkIfGoodsHasWarningStock(goods, selectedWarehouseIds);
            }

            // 如果商品没有预警库存，移除该商品
            if (!hasWarning) {
                iterator.remove();
            }else{
                // 3.额外检查：检查在仓库中是否有任何库存记录
                boolean hasAnyRecordInWarehouses = checkIfHasAnyRecordInWarehouses(goods, selectedWarehouseIds);
                if (!hasAnyRecordInWarehouses) {
                    iterator.remove();
                }
            }
        }
    }

    /**
     * 检查有属性的商品是否是预警库存
     */
    private boolean checkIfAttributeHasWarningStock(AttrStockDTO attr, BigDecimal stockThreshold, List<String> selectedWarehouseIds) {
        // 确定要检查的仓库列表
        List<String> warehouseIdsToCheck = selectedWarehouseIds;
        if (warehouseIdsToCheck == null || warehouseIdsToCheck.isEmpty()) {
            // 如果没选仓库，就查所有仓库
            warehouseIdsToCheck = inventoryMapper.selectAllWarehouseIds();
        }
        List<WarehouseStockDTO> attrStocks = attr.getWarehouses();

        // 对每个仓库进行检查
        for (String warehouseId : warehouseIdsToCheck) {
            Optional<WarehouseStockDTO> stockRecord = attrStocks.stream()
                    .filter(stock -> warehouseId.equals(stock.getWarehouseId()))
                    .findFirst();
            //有记录用实际库存，没有记录库存为0
            BigDecimal stockNum = stockRecord.isPresent() ? stockRecord.get().getStockNum() : BigDecimal.ZERO;

            if (stockNum.compareTo(stockThreshold) <= 0) {
                return true;// 只要有一个仓库预警，就返回true
            }
        }
        return false;// 所有仓库都不预警
    }

    /**
     * 检查没有属性的商品是否有预警库存
     */
    private boolean checkIfGoodsHasWarningStock(InventoryListDTO goods, List<String> selectedWarehouseIds) {
        // 确定要检查的仓库列表
        List<String> warehouseIdsToCheck = selectedWarehouseIds;
        if (warehouseIdsToCheck == null || warehouseIdsToCheck.isEmpty()) {
            // 如果没选仓库，就查所有仓库
            warehouseIdsToCheck = inventoryMapper.selectAllWarehouseIds();
        }

        List<WarehouseStockDTO> goodsStocks = goods.getWarehouses();

        for (String warehouseId : warehouseIdsToCheck) {
            Optional<WarehouseStockDTO> stockRecord = goodsStocks.stream()
                    .filter(stock -> warehouseId.equals(stock.getWarehouseId()))
                    .findFirst();

            BigDecimal stockNum = stockRecord.isPresent() ? stockRecord.get().getStockNum() : BigDecimal.ZERO;

            if (stockNum.compareTo(goods.getStock()) <= 0) {
                return true;
            }
        }
        return false;
    }
    /**
     * 检查商品在仓库中是否有任何库存记录
     */
    private boolean checkIfHasAnyRecordInWarehouses(InventoryListDTO goods, List<String> selectedWarehouseIds) {
        // 确定要检查的仓库列表
        List<String> warehouseIdsToCheck = selectedWarehouseIds;
        if (warehouseIdsToCheck == null || warehouseIdsToCheck.isEmpty()) {
            // 如果没选仓库，就查所有仓库
            warehouseIdsToCheck = inventoryMapper.selectAllWarehouseIds();
        }

        if (goods.getAttrs() != null && !goods.getAttrs().isEmpty()) {
            // 有属性商品：检查所有属性在仓库中是否有记录
            for (AttrStockDTO attr : goods.getAttrs()) {
                for (WarehouseStockDTO stock : attr.getWarehouses()) {
                    if (warehouseIdsToCheck.contains(stock.getWarehouseId())) {
                        return true;  // 找到一条记录就返回
                    }
                }
            }
        } else {
            // 无属性商品：检查在仓库中是否有记录
            for (WarehouseStockDTO stock : goods.getWarehouses()) {
                if (warehouseIdsToCheck.contains(stock.getWarehouseId())) {
                    return true;
                }
            }
        }
        return false; // 没有任何记录
    }
    /**
     * 过滤非零库存
     */
    private void filterNonZeroStock(List<InventoryListDTO> goodsList) {
        Iterator<InventoryListDTO> iterator = goodsList.iterator();
        while (iterator.hasNext()) {
            InventoryListDTO goods = iterator.next();
            boolean hasStock = false;

            if (goods.getAttrs() != null && !goods.getAttrs().isEmpty()) {
                // 有属性商品：检查每个属性是否有库存
                Iterator<AttrStockDTO> attrIterator = goods.getAttrs().iterator();
                while (attrIterator.hasNext()) {
                    AttrStockDTO attr = attrIterator.next();
                    // 检查属性是否有非零库存
                    boolean attrHasStock = attr.getWarehouses().stream()
                            .anyMatch(stock -> stock.getStockNum().compareTo(BigDecimal.ZERO) != 0);

                    if (attrHasStock) {
                        hasStock = true;
                        // 有库存，保留该属性
                    } else {
                        // 没有库存，移除该属性
                        attrIterator.remove();
                    }
                }
            } else {
                // 无属性商品：检查商品是否有库存
                hasStock = goods.getWarehouses().stream()
                        .anyMatch(stock -> stock.getStockNum().compareTo(BigDecimal.ZERO) != 0);
            }

            // 如果商品没有库存，移除该商品
            if (!hasStock) {
                iterator.remove();
            }
        }
    }



    /**
     * 获取库存详情数据（分页）
     * @param query 详情查询条件对象，包含商品ID、仓库ID、辅助属性ID、时间范围、库存数量范围、库存状态等过滤条件以及分页参数
     * @return PageDTO<InventoryDetailDTO> 分页后的库存详情数据，每条记录包含商品ID、商品名称、仓库ID、仓库名称、辅助属性ID、辅助属性名称、库存数量、库存状态等字段
     */
    @Override
    public PageDTO<InventoryDetailDTO> getInventoryDetail(InventoryDetailQuery query) {
        //TODO:后续可以使用校验注解优化
        if (query.getGoodsId() == null) {
            throw new IllegalArgumentException("商品ID不能为空");
        }

        Page<InventoryDetailDTO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        Page<InventoryDetailDTO> resultPage = inventoryDetailMapper.selectInventoryDetailList(page, query);

        return PageDTO.create(resultPage);

    }

    /**
     * 导出库存列表数据Excel
     * @param query
     * @return
     */
    @SneakyThrows
    @Override
    public ResponseEntity<byte[]> getListExport(InventoryQuery query) {
        // 定义输出流
        ByteArrayOutputStream out = new ByteArrayOutputStream();

        // TODO 获取库存列表数据
//        List<InventoryListDTO> inventoryListDTOS = inventoryMapper.getInventroyList();
        List<InventoryListDTO> inventoryListDTOS = null;

        // 生成Excel
        excel.export("库存列表",out,InventoryListDTO.class,inventoryListDTOS);

        // 响应给前端
        HttpHeaders headers = new HttpHeaders();
        String filename = "库存列表" + DateTime.now().toString("yyyyMMddHHmmssS") + ".xlsx";
        headers.setContentDispositionFormData("attachment", filename);
        headers.setContentType(MediaType.APPLICATION_OCTET_STREAM);
        ResponseEntity<byte[]> res = new ResponseEntity<>(out.toByteArray(), headers, HttpStatus.CREATED);
        out.close();

        return res;
    }

    /**
     * 导出库存详情数据Excel
     * @param id
     * @return
     */
    @SneakyThrows
    @Override
    public ResponseEntity<byte[]> getDetailExport(String id) {
        // 定义输出流
        ByteArrayOutputStream out = new ByteArrayOutputStream();

        // 获取库存详情数据
        List<InventoryDetailExcelDTO> inventoryDetailDTOS = inventoryDetailMapper.getDetailList(id);

        // 处理数据并设置默认值
        if (inventoryDetailDTOS != null) {
            for (InventoryDetailExcelDTO dto : inventoryDetailDTOS) {
                // 设置所属组织
                dto.setName(userHolder != null && userHolder.getCurrentUser() != null && userHolder.getCurrentUser().getFrameName() != null ? userHolder.getCurrentUser().getFrameName() : "默认组织");
                // 确保其他必要字段不为空
                if (dto.getType() == null) {
                    dto.setType("");
                }
                if (dto.getNumber() == null) {
                    dto.setNumber("");
                }
                if (dto.getDirection() == null) {
                    dto.setDirection(String.valueOf(0));
                }
                if (dto.getNums() == null) {
                    dto.setNums(BigDecimal.ZERO);
                }
            }
        } else {
            // 如果没有数据，创建空列表避免NPE
            inventoryDetailDTOS = new ArrayList<>();
        }

        // 生成Excel
        excel.export("库存详情", out, InventoryDetailExcelDTO.class, inventoryDetailDTOS);

        // 响应给前端
        HttpHeaders headers = new HttpHeaders();
        String filename = "库存详情" + DateTime.now().toString("yyyyMMddHHmmssS") + ".xlsx";
        headers.setContentDispositionFormData("attachment", filename);
        headers.setContentType(MediaType.APPLICATION_OCTET_STREAM);
        ResponseEntity<byte[]> res = new ResponseEntity<>(out.toByteArray(), headers, HttpStatus.CREATED);
        out.close();
        return res;
    }
}
