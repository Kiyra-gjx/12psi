package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchDetailDTO;
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
     * 获取指定批次详情数据
     * @param id
     * @return
     */
    JsonVO<PageDTO<BatchDetailDTO>> getBatchDetail(int id);
}
