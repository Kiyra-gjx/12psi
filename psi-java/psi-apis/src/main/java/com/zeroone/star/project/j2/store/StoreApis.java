package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchDetailDTO;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
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
     * 查询商品列表
     * @param query 查询参数
     * @return 商品列表数据
     */
    JsonVO<PageDTO<InventoryListDTO>> listGoods(InventoryQuery query);

    /**
     * 获取指定批次详情数据
     * @param id
     * @return
     */
    JsonVO<PageDTO<BatchDetailDTO>> getBatchDetail(String id);
}
