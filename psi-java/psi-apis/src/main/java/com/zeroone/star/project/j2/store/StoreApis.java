package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchDetailDTO;
import com.zeroone.star.project.dto.j2.store.BatchListDTO;
import com.zeroone.star.project.dto.j2.store.InventoryDetailDTO;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
import com.zeroone.star.project.query.j2.store.BatchQuery;
import com.zeroone.star.project.query.j2.store.InventoryDetailQuery;
import com.zeroone.star.project.query.j2.store.InventoryQuery;
import com.zeroone.star.project.vo.JsonVO;

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
     * 查询库存列表数据
     * @param query 查询参数
     * @return 商品列表数据
     */
    JsonVO<PageDTO<InventoryListDTO>> listGoods(InventoryQuery query);

    /**
     * 获取指定库存详情数据
     * @param query
     * @return 库存详情数据
     */
    JsonVO<PageDTO<InventoryDetailDTO>> getInventoryDetail(InventoryDetailQuery query);

    /**
     * 查询批次列表数据
     * @param query
     * @return 批次列表数据
     */
    JsonVO<PageDTO<BatchListDTO>> listBatch(BatchQuery query);

    /**
     * 获取指定批次详情数据
     * @param id
     * @return
     */
    JsonVO<PageDTO<BatchDetailDTO>> getBatchDetail(String id);

}
