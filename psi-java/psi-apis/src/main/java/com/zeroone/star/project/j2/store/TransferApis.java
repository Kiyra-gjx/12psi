package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 18:46
 * @Description: 调拨单接口
 * @Version: 1.0
 */
public interface TransferApis {

    /**
     * 添加调拨单
     * @param dto 调拨单数据
     * @return 添加结果
     */
    JsonVO<String> modifyTransfer(TransferDetailDTO dto);

    /**
     * 批量审核/反审核调拨单
     * @param ids 调拨单id列表
     * @param operation 操作类型（0-未审核，1-已审核）
     * @return
     */
    JsonVO<String> batchAuditTransfer(List<Integer> ids, Integer operation);

    /**
     * 批量删除调拨单
     * @param ids 调拨单id列表
     * @return
     */
    JsonVO<String> removeTransfer(List<Integer> ids);
}
