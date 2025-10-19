package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchDetailDTO;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDTO;
import com.zeroone.star.project.j2.store.StoreApis;
import com.zeroone.star.project.query.j2.store.InventoryQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

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

    @GetMapping("/list")
    @ApiOperation(value = "查询商品列表")
    @Override
    public JsonVO<PageDTO<InventoryListDTO>> listGoods(InventoryQuery query) {
        return null;
    }

    @GetMapping("/batch/detail")
    @Override
    public JsonVO<PageDTO<BatchDetailDTO>> getBatchDetail(String id) {
        return null;
    }

    @PutMapping("/entry/update")
    @ApiOperation(value = "修改其他入库单")
    @Override
    public JsonVO<String> updateOtherInList(OtherInListDTO otherInListDTO) {
        return null;
    }

    @PutMapping("/entry/examine")
    @ApiOperation(value = "审核入库单")
    @Override
    public JsonVO<String> examine(List<Integer> ids) {
        return null;
    }

    @PutMapping("/entry/check")
    @ApiOperation(value = "核对入库单")
    @Override
    public JsonVO<String> check(List<Integer> ids) {
        return null;
    }

}
