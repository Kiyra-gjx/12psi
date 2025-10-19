package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.query.j2.store.InventoryQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 10:52
 * @Description: 库存查询相关接口
 * @Version: 1.0
 */
public interface StoreApis {

    /**
     * 查询商品列表
     * @param query 查询参数
     * @return 商品列表数据
     */
    JsonVO<PageDTO<InventoryListDTO>> listGoods(InventoryQuery query);

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
