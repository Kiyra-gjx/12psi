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
        try {
            // 创建分页对象
            Page<BatchListDTO> page = new Page<>(query.getPageIndex(), query.getPageSize());

            // 1. 查询商品基本信息（第一层）- 商品级别筛选
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

            // 3. 查询批次详情信息（第三层）- 严格应用所有批次条件
            List<BatchDocumentDTO> allBatchDocuments = batchListMapper.selectBatchDocumentsByGoodsIds(goodsIds, query);

            // 4. 按商品ID和批次号进行双重分组
            Map<String, Map<String, List<BatchDocumentDTO>>> batchGroupMap = allBatchDocuments.stream()
                    .collect(Collectors.groupingBy(
                            BatchDocumentDTO::getGoodsId,
                            Collectors.groupingBy(BatchDocumentDTO::getBatchNumber)
                    ));

            // 5. 组装数据
            for (BatchListDTO goods : goodsList) {
                String goodsId = goods.getId();

                // 设置仓库库存信息
                goods.setWarehouses(warehouseStockMap.getOrDefault(goodsId, new ArrayList<>()));

                // 设置批次信息
                Map<String, List<BatchDocumentDTO>> goodsBatchMap = batchGroupMap.getOrDefault(goodsId, new HashMap<>());
                List<BatchNumberDTO> batchNumbers = new ArrayList<>();

                for (Map.Entry<String, List<BatchDocumentDTO>> entry : goodsBatchMap.entrySet()) {
                    BatchNumberDTO batchNumberDTO = new BatchNumberDTO();
                    batchNumberDTO.setBatchNumber(entry.getKey());
                    batchNumberDTO.setGoodsId(goodsId);
                    batchNumberDTO.setBatchDocuments(entry.getValue());

                    // 计算该批次号的总库存
                    BigDecimal totalStock = entry.getValue().stream()
                            .map(BatchDocumentDTO::getNums)
                            .reduce(BigDecimal.ZERO, BigDecimal::add);
                    batchNumberDTO.setTotalStock(totalStock);

                    batchNumbers.add(batchNumberDTO);
                }

                goods.setBatches(batchNumbers);
            }

            // 返回分页结果
            return PageDTO.create(goodsPage);

        } catch (Exception e) {
            log.error("查询批次列表失败", e);
            throw new RuntimeException("查询批次列表失败", e);
        }
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
