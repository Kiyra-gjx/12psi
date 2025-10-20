package com.zeroone.star.project.j2.store;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.InventoryDetailDTO;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
import com.zeroone.star.project.query.j2.store.InventoryDetailQuery;
import com.zeroone.star.project.query.j2.store.InventoryQuery;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.http.ResponseEntity;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 18:44
 * @Description: 库存查询接口
 * @Version: 1.0
 */
public interface InventoryQueryApis {
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
     * 导出库存列表数据
     * @param inventoryListDTO
     * @return
     */
    ResponseEntity<byte[]> exportInventoryListExcel(InventoryListDTO inventoryListDTO);

    /**
     * 导出库存详情数据
     * @param inventoryDetailDTO
     * @return
     */
    ResponseEntity<byte[]> exportInventoryDetailExcel(InventoryDetailDTO inventoryDetailDTO);
}
