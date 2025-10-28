package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j2.store.BatchDetailDTO;
import com.zeroone.star.project.query.j2.store.BatchDetailQuery;
import com.zeroone.star.storemanagement.entity.BatchDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.mapper
 * @Author: 高
 * @CreateTime: 2025-10-24 20:18
 * @Description: TODO
 * @Version: 1.0
 */
@Mapper
public interface BatchMapper extends BaseMapper<BatchDO> {

    /**
     * 获取批次详情数据列表
     * @param batchDetailQuery 查询条件
     * @return 批次详情数据列表
     */
    List<BatchDetailDTO> getBatchDetail(@Param("batchDetailQuery") BatchDetailQuery batchDetailQuery);
    
    /**
     * 获取批次详情数据总数
     * @param batchDetailQuery 查询条件
     * @return 数据总数
     */
    long getBatchDetailCount(@Param("batchDetailQuery") BatchDetailQuery batchDetailQuery);
}
