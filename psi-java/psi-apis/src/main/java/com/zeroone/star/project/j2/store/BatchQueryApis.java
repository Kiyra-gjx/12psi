package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchListDTO;
import com.zeroone.star.project.query.j2.store.BatchQuery;
import com.zeroone.star.project.vo.JsonVO;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 18:44
 * @Description: 批次查询接口
 * @Version: 1.0
 */
public interface BatchQueryApis {
    /**
     * 查询批次列表数据
     * @param query
     * @return 批次列表数据
     */
    JsonVO<PageDTO<BatchListDTO>> listBatch(BatchQuery query);
}
