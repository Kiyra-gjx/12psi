package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j2.store.BatchAttrDTO;
import com.zeroone.star.project.dto.j2.store.BatchDocumentDTO;
import com.zeroone.star.project.dto.j2.store.BatchListDTO;
import com.zeroone.star.project.query.j2.store.BatchQuery;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;
@Mapper
public interface BatchListMapper {

    /**
     * 分页查询批次商品列表
     */
    Page<BatchListDTO> selectBatchGoodsList(Page<BatchListDTO> page, @Param("query") BatchQuery query);

    /**
     * 查询商品属性库存信息
     */
    List<BatchAttrDTO> selectGoodsAttrStock(@Param("goodsIds") List<String> goodsIds, @Param("query") BatchQuery query);

    /**
     * 批量查询批次详情信息
     */
    List<BatchDocumentDTO> selectBatchDocumentsByGoodsIds(@Param("goodsIds") List<String> goodsIds, @Param("query") BatchQuery query);

    /**
     * 查询指定父分类下的所有子分类ID
     */
    List<String> selectChildCategoryIds(@Param("parentId") String parentId);


}