package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.InventoryDetailDTO;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
import com.zeroone.star.project.j2.store.InventoryQueryApis;
import com.zeroone.star.project.query.j2.store.InventoryDetailQuery;
import com.zeroone.star.project.query.j2.store.InventoryQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.http.ResponseEntity;
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
@Api(tags = "库存查询")
public class InventoryQueryController implements InventoryQueryApis {
    @GetMapping("/query/list/select")
    @ApiOperation(value = "获取库存列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<InventoryListDTO>> getInventoryList(InventoryQuery query) {

        return null;
    }

    @GetMapping("/query/list/select/detail")
    @ApiOperation(value = "获取指定库存详情（条件+分页）")
    @Override
    public JsonVO<PageDTO<InventoryDetailDTO>> getInventoryDetail(InventoryDetailQuery query) {
        return null;
    }


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
