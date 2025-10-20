package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.j2.store.OtherInListAddDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDetailDTO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j2.store.OtherInApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.query.j2.store.OtherInQuery;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;
import org.springframework.http.ResponseEntity;
import org.springframework.web.multipart.MultipartFile;
import java.util.List;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.controller
 * @Author: 高
 * @CreateTime: 2025-10-19 18:50
 * @Description: 其他入库单控制器类
 * @Version: 1.0
 */
@RestController
@RequestMapping("/otherin")
@Api(tags = "其他入库单相关接口")
public class OtherInController implements OtherInApis {
    @PutMapping("/update")
    @ApiOperation(value = "修改其他入库单")
    @Override
    public JsonVO<String> updateOtherInList(OtherInListDTO otherInListDTO) {
        return null;
    }

    @PutMapping("/examine")
    @ApiOperation(value = "审核入库单")
    @Override
    public JsonVO<String> examine(List<Integer> ids) {
        return null;
    }

    @PutMapping("/check")
    @ApiOperation(value = "核对入库单")
    @Override
    public JsonVO<String> check(List<Integer> ids) {
        return null;
    }

    @GetMapping("/list")
    @ApiOperation(value = "获取指定其他入库单详细")
    @ApiImplicitParam(name = "id", value = "其他入库单编号", required = true, example = "1d7b0520e93e72715d5d6af1fb7d9a37")
    @Override
    public JsonVO<OtherInListDetailDTO> getOtherInList(String id) {
        return null;
    }

    @PostMapping("/add")
    @ApiOperation(value = "新增其他入库单")
    @Override
    public JsonVO<String> addOtherInList(@RequestBody OtherInListAddDTO dto) {
        return null;
    }

    @DeleteMapping("/delete")
    @ApiOperation(value = "删除其他入库单(批量)")
    @Override
    public JsonVO<List<String>> deleteOtherInList(
            @RequestBody
            @ApiParam(value = "删除编号列表", required = true, example = "[\"1d7b0520e93e72715d5d\", \"1d7b0520e93e72715d52\"]")
            List<String> ids) {
        return null;
    }

    @PostMapping("/import")
    @ApiOperation(value = "导入数据")
    @Override
    public JsonVO<String> importExcel(@RequestBody MultipartFile file) {
        return null;
    }

    @PostMapping("/exportEasyExcel")
    @ApiOperation(value = "导出简单报表")
    @Override
    public JsonVO<ResponseEntity<byte[]>> exportEasyExcel(List<Integer> ids) {
        return null;
    }

    @PostMapping("/exportDetailExcel")
    @ApiOperation(value = "导出详细报表")
    @Override
    public JsonVO<ResponseEntity<byte[]>> exportDetailExcel(List<Integer> ids) {
        return null;
    }
    @GetMapping("")
    @ApiOperation(value = "获取其他入库单列表")
    @Override
    public JsonVO<PageDTO<OtherInListDTO>> listOtherIn(OtherInQuery query) {
        return null;
    }
}
