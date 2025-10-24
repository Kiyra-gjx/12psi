package com.zeroone.star.storemanagement.mapper;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchDetailDTO;
import com.zeroone.star.project.query.j2.store.BatchDetailQuery;
import org.apache.ibatis.annotations.Mapper;

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

    PageDTO<BatchDetailDTO> getBatchDetail(BatchDetailQuery batchDetailQuery);
}
