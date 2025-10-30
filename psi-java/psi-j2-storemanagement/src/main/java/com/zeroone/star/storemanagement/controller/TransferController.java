package com.zeroone.star.storemanagement.controller;

import cn.hutool.core.date.DateTime;
import com.alibaba.excel.EasyExcel;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsClientComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsFileInfo;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.ShopListDTO;
import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.dto.j2.store.TransferDetailListDTO;
import com.zeroone.star.project.dto.j2.store.TransferListDTO;
import com.zeroone.star.project.j2.store.TransferApis;
import com.zeroone.star.project.query.j2.store.TransferQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.service.ISwapService;
import com.zeroone.star.storemanagement.service.ITransferService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import lombok.SneakyThrows;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.ResponseEntity;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.math.BigDecimal;
import java.nio.charset.StandardCharsets;
import java.time.LocalDate;
import java.util.ArrayList;
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
@Slf4j
public class TransferController implements TransferApis {
    private final ITransferService transferService;

    public TransferController(ITransferService transferService) {
        this.transferService = transferService;
    }

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
            ShopListDTO shopListDto) {
        return null;
    }

    @PostMapping("/add-transferList")
    @ApiOperation(value = "新增调拨单")
    @Override
    public JsonVO<List<TransferDetailListDTO>> addTransferList(
            /*根据商品列表新增调拨单，可以批量*/
            @ApiParam(value = "商品列表", required = false)
            @RequestBody
            List<ShopListDTO> shopListDto) {
        return null;
    }

    @PutMapping("/modify-transfer")
    @ApiOperation(value = "修改调拨单")
    @Override
    public JsonVO<String> modifyTransfer(@RequestBody TransferDetailDTO dto) {
        return transferService.modifyTransfer(dto);
    }

    @PostMapping("/batch-audit-transfer")
    @ApiOperation(value = "审核/反审核(支持批量)")
    @Override
    public JsonVO<String> batchAuditTransfer(
            @ApiParam(value = "调拨单ID列表", required = true, example = "[1,2,3]")
            @RequestBody List<Integer> ids,
            @ApiParam(value = "操作类型（0-未审核，1-已审核）", required = true, example = "1")
            @RequestParam Integer operation) {
        return transferService.batchAuditTransfer(ids, operation);
    }

    @PostMapping("/remove-transfer")
    @ApiOperation(value = "删除调拨单(支持批量)")
    @Override
    public JsonVO<String> removeTransfer(@RequestBody List<Integer> ids) {
        return transferService.deleteTransfer(ids);
    }

    @Resource
    ISwapService swapService;

    @Resource
    EasyExcelComponent excel;

    @Resource
    FastDfsClientComponent dfs;

    @PostMapping("/import")
    @ApiOperation(value = "导入数据")
    public JsonVO<String> importTransferList(@RequestPart("file") MultipartFile file) {

        if(file.isEmpty()) {
            return JsonVO.fail("文件为空");
        }


        return null;
    }

    @SneakyThrows
    @PostMapping("/export")
    @ApiOperation(value = "导出简单报表")
    public ResponseEntity<byte[]> exportTransferList(@RequestBody List<String> idList) {
        if(idList.isEmpty()) {
            return new ResponseEntity<>("列表为空".getBytes(),HttpStatus.BAD_REQUEST);
        }
        ArrayList<TransferListDTO> transferListDTOList = swapService.getTransferListDTOList(idList);
        if (transferListDTOList.isEmpty()) {
            return new ResponseEntity<>("无数据".getBytes(),HttpStatus.BAD_REQUEST);
        }
        ByteArrayOutputStream out = new ByteArrayOutputStream();

        excel.export("简单报表",out,TransferListDTO.class,transferListDTOList);

        HttpHeaders headers = new HttpHeaders();
        String filename = DateTime.now().toString("yyyyMMddHHmmssS")+ ".xlsx";
        headers.setContentDispositionFormData("attachment", filename);
        headers.setContentType(MediaType.APPLICATION_OCTET_STREAM);
        ResponseEntity<byte[]> res = new ResponseEntity<>(out.toByteArray(),headers,HttpStatus.CREATED);
        out.close();
        return res;
    }

    @PostMapping("/exportDetail")
    @ApiOperation(value = "导出详细报表")
    public ResponseEntity<byte[]> exportTransferDetailList(@RequestBody List<String> idList) {
        return null;
    }


}
