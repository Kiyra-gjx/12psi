package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.j2.store.StoreApis;
import com.zeroone.star.project.query.j2.store.InventoryQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;

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

    @PostMapping("/modify-transfer")
    @ApiOperation(value = "修改调拨单")
    @Override
    public JsonVO<String> modifyTransfer(
            @ApiParam(value = "调拨单数据", required = true, example = "{\"id\":1,\"warehouse\":\"1号仓库\",\"storehouse\":\"2号仓库\",\"cost\":998.00,\"nums\":1.00,\"remark\":\"紧急调拨\"}")
            @RequestBody TransferDetailDTO dto) {
        return JsonVO.success("修改调拨单成功，ID: " + dto.getId());
    }

    @PostMapping("/batch-audit-transfer")
    @ApiOperation(value = "批量审核/反审核调拨单")
    @Override
    public JsonVO<String> batchAuditTransfer(
            @ApiParam(value = "调拨单ID列表", required = true, example = "1,2,3")
            @RequestParam List<Integer> ids,
            @ApiParam(value = "操作类型（0-未审核，1-已审核）", required = true, example = "1")
            @RequestParam Integer operation) {
        String operationName = operation == 1 ? "审核" : "反审核";
        return JsonVO.success("批量" + operationName + "成功，操作 " + ids.size() + " 条单据");
    }

    @PostMapping("/remove-transfer")
    @ApiOperation(value = "批量删除调拨单")
    @ApiImplicitParam(
            name = "ids",
            value = "调拨单ID列表",
            required = true,
            dataType = "string",
            example = "1,2,3",
            paramType = "query",
            defaultValue = "1,2,3"
    )
    @Override
    public JsonVO<String> removeTransfer(@RequestParam List<Integer> ids) {
        return JsonVO.success("批量删除调拨单成功，删除 " + ids.size() + " 条单据");
    }
}
