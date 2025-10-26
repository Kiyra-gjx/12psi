package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.InventoryDetailDTO;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
import com.zeroone.star.project.j2.store.InventoryQueryApis;
import com.zeroone.star.project.query.j2.store.InventoryDetailQuery;
import com.zeroone.star.project.query.j2.store.InventoryQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.service.IInventoryDetailService;
import com.zeroone.star.storemanagement.service.IInventoryService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.models.auth.In;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import java.util.List;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.controller
 * @Author: 高
 * @CreateTime: 2025-10-19 18:48
 * @Description: 库存查询控制器类
 * @Version: 1.0
 */
@RestController
@RequestMapping("/inventory")
@Api(tags = "库存查询")
public class InventoryQueryController implements InventoryQueryApis {

    @Resource
    private IInventoryService inventoryService;

    @Resource
    private IInventoryDetailService inventoryDetailService;

    @GetMapping("/query/list/select")
    @ApiOperation(value = "获取库存列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<InventoryListDTO>> getInventoryList(InventoryQuery query) {
        JsonVO<PageDTO<InventoryListDTO>> inventoryList = inventoryService.getInventoryList(query);

        return inventoryService.getInventoryList(query);
    }

    @GetMapping("/query/list/select/detail")
    @ApiOperation(value = "获取指定库存详情（条件+分页）")
    @Override
    public JsonVO<PageDTO<InventoryDetailDTO>> getInventoryDetail(InventoryDetailQuery query) {
        return inventoryDetailService.getInventoryDetail(query);
    }


    @GetMapping("/export")
    @ApiOperation(value = "导出库存列表数据Excel")
    @Override
    public ResponseEntity<byte[]> exportInventoryListExcel(List<String> idList) {
        return null;
    }

    @GetMapping("/exportDetail")
    @ApiOperation(value = "导出库存详情数据Excel")
    @Override
    public ResponseEntity<byte[]> exportInventoryDetailExcel(List<String> idList) {
        return null;
    }


}
