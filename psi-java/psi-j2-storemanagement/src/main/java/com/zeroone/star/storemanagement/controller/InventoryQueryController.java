package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.j2.store.InventoryDetailDTO;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
import com.zeroone.star.project.j2.store.InventoryQueryApis;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.controller
 * @Author: 高
 * @CreateTime: 2025-10-19 18:48
 * @Description: 库存查询控制器类
 * @Version: 1.0
 */
@RestController
@RequestMapping("/store")
@Api(tags = "库存查询相关接口")
public class InventoryQueryController implements InventoryQueryApis {


    @GetMapping("/export")
    @ApiOperation(value = "导出库存列表数据Excel")
    @Override
    public ResponseEntity<byte[]> exportInventoryListExcel(InventoryListDTO inventoryListDTO) {
        return null;
    }

    @GetMapping("/exportDetail")
    @ApiOperation(value = "导出库存详情数据Excel")
    @Override
    public ResponseEntity<byte[]> exportInventoryDetailExcel(InventoryDetailDTO inventoryDetailDTO) {
        return null;
    }


}
