package com.zeroone.star.project.j2.store;


import com.zeroone.star.project.dto.j2.store.InventoryDetailDTO;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
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
