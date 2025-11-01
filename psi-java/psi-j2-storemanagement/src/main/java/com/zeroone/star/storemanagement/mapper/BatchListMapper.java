package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j2.store.BatchDocumentDTO;
import com.zeroone.star.project.dto.j2.store.BatchListDTO;
import com.zeroone.star.project.dto.j2.store.WarehouseStockDTO;
import com.zeroone.star.project.query.j2.store.BatchQuery;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;
@Mapper
public interface BatchListMapper {

    /**
     * 分页查询批次商品列表（第一层：商品基本信息）
     */
    Page<BatchListDTO> selectBatchGoodsList(Page<BatchListDTO> page, @Param("query") BatchQuery query);

    /**
     * 批量查询商品的仓库库存信息（第一层：仓库库存）
     */
    List<WarehouseStockDTO> selectGoodsWarehouseStock(@Param("goodsIds") List<String> goodsIds);

    /**
     * 批量查询批次详情信息（第三层：批次详情）- 严格应用所有条件
     */
    List<BatchDocumentDTO> selectBatchDocumentsByGoodsIds(
            @Param("goodsIds") List<String> goodsIds,
            @Param("query") BatchQuery query);

}