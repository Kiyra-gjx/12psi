package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.ShopListDto;
import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.dto.j2.store.TransferDetailListDTO;
import com.zeroone.star.project.dto.j2.store.TransferListDTO;
import com.zeroone.star.project.j2.store.TransferApis;
import com.zeroone.star.project.query.j2.store.TransferQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.util.List;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.controller
 * @Author: 高
 * @CreateTime: 2025-10-19 18:51
 * @Description: 调拨单控制器类
 * @Version: 1.0
 */
@RestController
@RequestMapping("/transfer")
@Api(tags = "调拨单")
public class TransferController implements TransferApis {
    @GetMapping("/query-transferList")
    @ApiOperation(value = "获取调拨单列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<TransferListDTO>> queryTransferList(
            @ApiParam(value = "调拨单查询条件", required = true)
            @RequestBody
            TransferQuery transferQuery) {
        return null;
    }

    @GetMapping("/detail-transferInfo")
    @ApiOperation(value = "获取指定调拨单详细信息")
    @Override
    public JsonVO<TransferDetailListDTO> detailTransferList(
            /*根据商品信息获取调拨单*/
            @ApiParam(value = "商品信息", required = false)
            @RequestBody
            ShopListDto shopListDto) {
        return null;
    }

    @PostMapping("/add-transferList")
    @ApiOperation(value = "新增调拨单")
    @Override
    public JsonVO<List<TransferDetailListDTO>> addTransferList(
            /*根据商品列表新增调拨单，可以批量*/
            @ApiParam(value = "商品列表", required = false)
            @RequestBody
            List<ShopListDto> shopListDto) {
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
    @ApiOperation(value = "审核/反审核(支持批量)")
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
    @ApiOperation(value = "删除调拨单(支持批量)")
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

    @PostMapping("/import")
    @ApiOperation(value = "导入数据")
    public JsonVO<String> importTransferList(@RequestPart("file") MultipartFile file) {
        return null;
    }

    @PostMapping("/export")
    @ApiOperation(value = "导出简单报表")
    public ResponseEntity<byte[]> exportTransferList(@RequestBody List<String> idList) {
        return null;
    }

    @PostMapping("/exportDetail")
    @ApiOperation(value = "导出详细报表")
    public ResponseEntity<byte[]> exportTransferDetailList(@RequestBody List<String> idList) {
        return null;
    }
}
