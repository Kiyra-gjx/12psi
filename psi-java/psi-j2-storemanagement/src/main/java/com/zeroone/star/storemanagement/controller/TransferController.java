package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.j2.store.ModifyTransferRequestDTO;
import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.dto.j2.store.TransferResponseDTO;
import com.zeroone.star.project.j2.store.TransferApis;
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
@Api(tags = "调拨单相关接口")
public class TransferController implements TransferApis {

    @PostMapping("/modify-transfer")
    @ApiOperation(value = "修改调拨单")
    @Override
    public TransferResponseDTO modifyTransfer(
            @RequestBody ModifyTransferRequestDTO requestData) {

        TransferResponseDTO response = new TransferResponseDTO();
        response.setState("success");
        response.setInfo("4");
        return response;
    }

    @PostMapping("/batch-audit-transfer")
    @ApiOperation(value = "审核/反审核(支持批量)")
    @Override
    public TransferResponseDTO batchAuditTransfer(
            @ApiParam(value = "调拨单ID列表", required = true, example = "{1,2,3}")
            @RequestBody List<Integer> request,
            @ApiParam(value = "操作类型（0-反审核，1-审核）", required = true, example = "1")
            @RequestParam Integer operation) {
        TransferResponseDTO response = new TransferResponseDTO();
        response.setState("success");
        response.setInfo(4);
        return response;
    }

    @PostMapping("/remove-transfer")
    @ApiOperation(value = "删除调拨单（支持批量）")
    @Override
    public TransferResponseDTO removeTransfer(
            @ApiParam(value = "调拨单ID列表", required = true, example = "{1,2,3}")
            @RequestBody List<Integer> parm) {

        TransferResponseDTO response = new TransferResponseDTO();
        response.setState("success");
        response.setInfo(4);
        return response;
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
