package com.zeroone.star.storemanagement.mapper;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchDetailDTO;
import com.zeroone.star.project.query.j2.store.BatchDetailQuery;
import org.apache.ibatis.annotations.Mapper;

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
public interface BatchMapper {

    /**
     * 获取批次详情数据列表
     * @param batchDetailQuery 查询条件
     * @return 批次详情数据列表
     */
    List<BatchDetailDTO> getBatchDetail(BatchDetailQuery batchDetailQuery);
    
    /**
     * 获取批次详情数据总数
     * @param batchDetailQuery 查询条件
     * @return 数据总数
     */
    long getBatchDetailCount(BatchDetailQuery batchDetailQuery);
}
