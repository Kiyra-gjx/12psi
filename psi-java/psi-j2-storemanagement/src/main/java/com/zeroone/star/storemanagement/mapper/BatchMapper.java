package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.storemanagement.entity.BatchDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.math.BigDecimal;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.mapper
 * @Author: 高
 * @CreateTime: 2025-10-24 20:18
 * @Description: 批次查询数据访问层
 * @Version: 1.0
 */
@Mapper
public interface BatchMapper extends BaseMapper<BatchDO> {
    @Select("SELECT EXISTS(SELECT 1 FROM is_batch WHERE number = #{batch})")
    boolean isBatchExist(@Param("batch") String batch);

    @Select("SELECT nums FROM is_batch WHERE number = #{batchNo} AND goods = #{goodsId} AND warehouse = #{warehouseId}")
    BigDecimal getBatchStock(@Param("batchNo") String batchNo, @Param("goodsId") String goodsId,
                             @Param("warehouseId") String warehouseId);

    @Update("UPDATE is_batch SET nums = nums + #{nums} WHERE number = #{batchNo} AND goods = #{goodsId} AND warehouse = #{warehouseId}")
    int updateBatchStock(@Param("batchNo") String batchNo, @Param("goodsId") String goodsId,
                         @Param("warehouseId") String warehouseId, @Param("nums") BigDecimal nums);

    @Update("INSERT INTO is_batch (number, goods, warehouse, nums) VALUES (#{batchNo}, #{goodsId}, #{warehouseId}, #{nums})")
    int createBatchInTargetWarehouse(@Param("batchNo") String batchNo, @Param("goodsId") String goodsId,
                                     @Param("warehouseId") String warehouseId, @Param("nums") BigDecimal nums);

    @Select("SELECT id FROM is_batch WHERE number = #{batchNo} AND goods = #{goodsId} AND warehouse = #{warehouseId}")
    String getBatchId(@Param("batchNo") String batchNo, @Param("goodsId") String goodsId,
                       @Param("warehouseId") String warehouseId);

}
