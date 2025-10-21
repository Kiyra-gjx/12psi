package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchListDTO;
import com.zeroone.star.project.dto.j2.store.InventoryVerifyListDTO;
import com.zeroone.star.project.j2.store.InventoryVerifyApis;
import com.zeroone.star.project.query.j2.store.InventoryVerifyQuery;
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
 * @CreateTime: 2025-10-19 18:49
 * @Description: 库存盘点控制器类
 * @Version: 1.0
 */
@RestController
@RequestMapping("/verify")
@Api(tags = "库存盘点")
public class InventoryVerifyController implements InventoryVerifyApis {


    @GetMapping("/list")
    @ApiOperation(value = "获取盘盈单数据")
    @Override
    public JsonVO<PageDTO<InventoryVerifyListDTO>> listInventoryVerify(InventoryVerifyQuery query) {
        return null;
    }


    @GetMapping("/queryProperty")
    @ApiOperation(value = "获取盘亏单数据")
    @Override
    public JsonVO<InventoryVerifyQuery> getinventoryVerifyQueryProperty() {
        return null;
    }

    @GetMapping("/export")
    @ApiOperation(value = "导出库存盘点单")
    @Override
    public JsonVO<byte[]> exportInventoryVerifyExcel() {
        return null;
    }
}
