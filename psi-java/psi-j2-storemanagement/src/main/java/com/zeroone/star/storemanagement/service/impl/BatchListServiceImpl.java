package com.zeroone.star.storemanagement.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchDocumentDTO;
import com.zeroone.star.project.dto.j2.store.BatchListDTO;
import com.zeroone.star.project.dto.j2.store.BatchNumberDTO;
import com.zeroone.star.project.dto.j2.store.WarehouseStockDTO;
import com.zeroone.star.project.query.j2.store.BatchQuery;
import com.zeroone.star.storemanagement.mapper.BatchListMapper;
import com.zeroone.star.storemanagement.service.IBatchListService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.*;
import java.util.stream.Collectors;

@Service
@Slf4j
public class BatchListServiceImpl implements IBatchListService {

    @Autowired
    private BatchListMapper batchListMapper;

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
                goods.setWarehouses(goodsWarehouseStockMap.getOrDefault(goods.getId(), new ArrayList<>()));
                goods.setBatches(goodsBatchMap.getOrDefault(goods.getId(), new ArrayList<>()));
            }

            return PageDTO.create(goodsResult);


    }

    /**
     * 获取商品的仓库库存信息映射
     */
    private Map<String, List<WarehouseStockDTO>> getGoodsWarehouseStockMap(List<String> goodsIds) {
        List<WarehouseStockDTO> warehouseStocks = batchListMapper.selectGoodsWarehouseStock(goodsIds);
        return warehouseStocks.stream()
                .collect(Collectors.groupingBy(WarehouseStockDTO::getGoodsId));
    }

    /**
     * 获取商品的批次信息映射（使用临时字段组装）
     */
    private Map<String, List<BatchNumberDTO>> getGoodsBatchMap(List<String> goodsIds) {
        // 查询批次基本信息（包含临时字段）
        List<BatchNumberDTO> batchRawData = batchListMapper.selectBatchInfoByGoodsIds(goodsIds);
        if (batchRawData.isEmpty()) {
            return new HashMap<>();
        }

        // 按批次ID分组，组装每个批次在各个仓库的分布
        Map<String, BatchNumberDTO> batchMap = new LinkedHashMap<>();
        Map<String, List<WarehouseStockDTO>> batchWarehouseMap = new HashMap<>();

        for (BatchNumberDTO batchData : batchRawData) {
            String batchId = batchData.getBatchId();

            if (!batchMap.containsKey(batchId)) {
                // 创建批次主信息（去重）
                BatchNumberDTO mainBatch = new BatchNumberDTO();
                mainBatch.setBatchId(batchData.getBatchId());
                mainBatch.setBatchNumber(batchData.getBatchNumber());
                mainBatch.setCreateTime(batchData.getCreateTime());
                mainBatch.setNums(batchData.getNums()); // 总库存
                mainBatch.setGoodsId(batchData.getGoodsId());
                mainBatch.setRoom(batchData.getRoom());
                mainBatch.setWarehouses(new ArrayList<>());
                batchMap.put(batchId, mainBatch);
                batchWarehouseMap.put(batchId, new ArrayList<>());
            }

            // 使用临时字段组装warehouses
            if (batchData.getWarehouseStock() != null) {
                WarehouseStockDTO warehouseStock = batchData.getWarehouseStock();
                batchWarehouseMap.get(batchId).add(warehouseStock);
            }
        }

        // 设置每个批次的仓库分布
        for (BatchNumberDTO batch : batchMap.values()) {
            batch.setWarehouses(batchWarehouseMap.get(batch.getBatchId()));
        }

        List<BatchNumberDTO> finalBatchList = new ArrayList<>(batchMap.values());

        // 提取批次ID列表查询单据信息
        List<String> batchIds = finalBatchList.stream()
                .map(BatchNumberDTO::getBatchId)
                .collect(Collectors.toList());

        // 查询批次单据信息
        Map<String, List<BatchDocumentDTO>> batchDocumentsMap = getBatchDocumentsMap(batchIds);

        // 组装批次单据信息
        for (BatchNumberDTO batch : finalBatchList) {
            batch.setBatchDocuments(batchDocumentsMap.getOrDefault(batch.getBatchId(), new ArrayList<>()));
        }

        // 按商品ID分组
        return finalBatchList.stream()
                .collect(Collectors.groupingBy(BatchNumberDTO::getGoodsId));
    }

    /**
     * 获取批次单据信息映射（使用临时字段组装warehouses）
     */
    private Map<String, List<BatchDocumentDTO>> getBatchDocumentsMap(List<String> batchIds) {
        List<BatchDocumentDTO> batchDocuments = batchListMapper.selectBatchDocumentsByBatchIds(batchIds);

        // 使用临时字段组装warehouses
        for (BatchDocumentDTO document : batchDocuments) {
            if (document.getWarehouseStock() != null) {
                WarehouseStockDTO warehouse = document.getWarehouseStock();
                warehouse.setGoodsId(document.getGoodsId());
                warehouse.setStockNum(document.getNums().abs()); // 单据的库存数量就是单据的数量
                document.setWarehouses(Collections.singletonList(warehouse));
            } else {
                document.setWarehouses(new ArrayList<>());
            }
        }

        return batchDocuments.stream()
                .collect(Collectors.groupingBy(BatchDocumentDTO::getPid));
    }
}