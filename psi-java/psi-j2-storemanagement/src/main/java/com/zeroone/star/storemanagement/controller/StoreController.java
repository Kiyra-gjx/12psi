package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchDetailDTO;
import com.zeroone.star.project.dto.j2.store.BatchListDTO;
import com.zeroone.star.project.dto.j2.store.InventoryDetailDTO;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
import com.zeroone.star.project.j2.store.StoreApis;
import com.zeroone.star.project.query.j2.store.BatchQuery;
import com.zeroone.star.project.query.j2.store.InventoryDetailQuery;
import com.zeroone.star.project.query.j2.store.InventoryQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.controller
 * @Author: 高
 * @CreateTime: 2025-10-18 12:15
 * @Description: 商品控制器类
 * @Version: 1.0
 */
@RestController
@RequestMapping("/store")
@Api(tags = "store1")
public class StoreController implements StoreApis {

    @GetMapping("/inventory/list")
    @ApiOperation(value = "查询库存列表")
    @Override
    public JsonVO<PageDTO<InventoryListDTO>> listGoods(InventoryQuery query) {
        return null;
    }

    @GetMapping("/inventory/detail")
    @ApiOperation(value = "查询库存详情")
    @Override
    public JsonVO<PageDTO<InventoryDetailDTO>> getInventoryDetail(InventoryDetailQuery query) {
        return null;
    }

    @GetMapping("/batch/list")
    @ApiOperation(value = "查询批次列表")
    @Override
    public JsonVO<PageDTO<BatchListDTO>> listBatch(BatchQuery query) {
        return null;
    }

    @GetMapping("/batch/detail")
    @Override
    public JsonVO<PageDTO<BatchDetailDTO>> getBatchDetail(String id) {
        return null;
    }

}
