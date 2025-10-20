package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.j2.store.OtherInListDTO;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

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
     * 修改其他入库单
     * @param otherInListDTO 修改参数
     * @return 修改结果
     */
    JsonVO<String> updateOtherInList(OtherInListDTO otherInListDTO);

    /**
     * 审核或反审核
     * @param ids 审核id列表
     * @return 修改结果
     */
    JsonVO<String> examine(List<Integer> ids);

    /**
     * 核对或反核对
     * @param ids 核对id列表
     * @return 修改结果
     */
    JsonVO<String> check(List<Integer> ids);
}
