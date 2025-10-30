package com.zeroone.star.storemanagement.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchDetailDTO;
import com.zeroone.star.project.dto.j2.store.BatchListDTO;
import com.zeroone.star.project.query.j2.store.BatchDetailQuery;
import com.zeroone.star.project.query.j2.store.BatchQuery;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.service
 * @Author: 高
 * @CreateTime: 2025-10-24 20:16
 * @Description: TODO
 * @Version: 1.0
 */
public interface IBatchQueryService {

    /**
     * 查询批次列表
     */
    PageDTO<BatchListDTO> listBatch(BatchQuery query);

    /**
     * 获取指定批次详情数据
     * @param batchDetailQuery
     * @return
     */
    PageDTO<BatchDetailDTO> getBatchDetail(BatchDetailQuery batchDetailQuery);
}
