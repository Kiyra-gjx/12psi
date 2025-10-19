package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDTO;
import com.zeroone.star.project.query.j2.store.OtherInQuery;
import com.zeroone.star.project.vo.JsonVO;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 18:46
 * @Description: 其他入库单接口
 * @Version: 1.0
 */
public interface OtherInApis {
    /**
     * 获取其他入库单列表
     * @param query 查询参数
     * @return
     */
    JsonVO<PageDTO<OtherInListDTO>> listOtherIn(OtherInQuery query);
}
