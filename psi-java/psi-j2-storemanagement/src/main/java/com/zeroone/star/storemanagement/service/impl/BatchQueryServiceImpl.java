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
}
