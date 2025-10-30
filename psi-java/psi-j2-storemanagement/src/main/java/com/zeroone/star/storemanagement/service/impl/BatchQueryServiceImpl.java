package com.zeroone.star.storemanagement.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
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

    /**
     * 获取批次列表信息
     * @param query 查询条件对象，包含商品id，批次号等信息
     * @return PageDTO<BatchListDTO> 分页后的批次列表信息，商品基本信息以及批次的库存详情信息
     */
    @Override
    public PageDTO<BatchListDTO> listBatch(BatchQuery query) {

        // 第一步：直接分页查询商品列表到BatchListDTO
        Page<BatchListDTO> goodsPage = new Page<>(query.getPageIndex(), query.getPageSize());
        Page<BatchListDTO> goodsResult = batchListMapper.selectBatchGoodsList(goodsPage, query);

        if (goodsResult.getRecords().isEmpty()) {
            return PageDTO.create(goodsResult);
        }

        // 提取商品ID列表
        List<String> goodsIds = goodsResult.getRecords().stream()
                .map(BatchListDTO::getId)
                .collect(Collectors.toList());


        // 第二步：批量查询商品相关的库存和批次数据
        Map<String, List<WarehouseStockDTO>> goodsWarehouseStockMap = getGoodsWarehouseStockMap(goodsIds);
        Map<String, List<BatchNumberDTO>> goodsBatchMap = getGoodsBatchMap(goodsIds);

        // 第三步：库存和批次信息
        for (BatchListDTO goods : goodsResult.getRecords()) {
            goods.setWarehouses(goodsWarehouseStockMap.getOrDefault(goods.getId(), Collections.emptyList()));
            goods.setBatches(goodsBatchMap.getOrDefault(goods.getId(), Collections.emptyList()));
        }

        return PageDTO.create(goodsResult);


    }

    /**
     * 获取商品的仓库库存信息映射
     */
    private Map<String, List<WarehouseStockDTO>> getGoodsWarehouseStockMap(List<String> goodsIds) {
        if (goodsIds.isEmpty()) {
            return Collections.emptyMap();
        }
        List<WarehouseStockDTO> warehouseStocks = batchListMapper.selectGoodsWarehouseStock(goodsIds);
        return warehouseStocks.stream()
                .collect(Collectors.groupingBy(WarehouseStockDTO::getGoodsId));
    }

    /**
     * 获取商品的批次信息映射（使用临时字段组装）
     */
    private Map<String, List<BatchNumberDTO>> getGoodsBatchMap(List<String> goodsIds) {
        if (goodsIds.isEmpty()) {
            return Collections.emptyMap();
        }

        // 1.查询批次基本信息
        List<BatchNumberDTO> batchBasicList = batchListMapper.selectBatchBasicInfoByGoodsIds(goodsIds);
        if (batchBasicList.isEmpty()) {
            return Collections.emptyMap();
        }


        // 2.查询批次仓库分布信息
        List<WarehouseStockDTO> batchWarehouses = batchListMapper.selectBatchWarehouseDistribution(goodsIds);
        Map<String, List<WarehouseStockDTO>> batchWarehouseMap = batchWarehouses.stream()
                .collect(Collectors.groupingBy(WarehouseStockDTO::getBatchId));


        // 3.提取批次ID列表查询单据信息
        List<String> batchIds = batchBasicList.stream()
                .map(BatchNumberDTO::getBatchId)
                .collect(Collectors.toList());
        Map<String, List<BatchDocumentDTO>> batchDocumentsMap = getBatchDocumentsMap(batchIds);

        // 4.组装完整的批次信息
        for (BatchNumberDTO batch : batchBasicList) {
            String batchId = batch.getBatchId();
            // 直接设置仓库
            batch.setWarehouses(batchWarehouseMap.getOrDefault(batchId, Collections.emptyList()));
            batch.setBatchDocuments(batchDocumentsMap.getOrDefault(batchId, Collections.emptyList()));
        }

        // 按商品ID分组返回
        Map<String, List<BatchNumberDTO>> result = batchBasicList.stream()
                .collect(Collectors.groupingBy(BatchNumberDTO::getGoodsId));

        return result;
    }

    /**
     * 获取批次单据信息映射（使用临时字段组装warehouses）
     */
    private Map<String, List<BatchDocumentDTO>> getBatchDocumentsMap(List<String> batchIds) {
        if (batchIds.isEmpty()) {
            return Collections.emptyMap();
        }

        // 1. 查询单据基本信息
        List<BatchDocumentDTO> batchDocuments = batchListMapper.selectBatchDocumentsBasicInfo(batchIds);
        if (batchDocuments.isEmpty()) {
            return Collections.emptyMap();
        }

        // 2. 查询单据仓库分布信息
        List<WarehouseStockDTO> documentWarehouses = batchListMapper.selectDocumentWarehouseDistribution(batchIds);

        // 3. 按单据ID分组仓库信息
        Map<String, List<WarehouseStockDTO>> documentWarehouseMap = documentWarehouses.stream()
                .collect(Collectors.groupingBy(WarehouseStockDTO::getDocumentId));

        // 4. 组装完整的单据信息
        for (BatchDocumentDTO document : batchDocuments) {
            String documentId = document.getId();
            List<WarehouseStockDTO> warehouses = documentWarehouseMap.getOrDefault(documentId, Collections.emptyList());

            // 为每个仓库设置商品ID和库存数量
            for (WarehouseStockDTO warehouse : warehouses) {
                warehouse.setGoodsId(document.getGoodsId());
                // 库存数量使用单据数量，可以根据业务调整
                warehouse.setStockNum(document.getNums()); //保持正负号
            }

            document.setWarehouses(warehouses);
        }

        return batchDocuments.stream()
                .collect(Collectors.groupingBy(BatchDocumentDTO::getPid));
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
}
