package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchDetailDTO;
import com.zeroone.star.project.dto.j2.store.BatchListDTO;
import com.zeroone.star.project.j2.store.BatchQueryApis;
import com.zeroone.star.project.query.j2.store.BatchDetailQuery;
import com.zeroone.star.project.query.j2.store.BatchQuery;
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
 * @CreateTime: 2025-10-19 18:50
 * @Description: 批次查询控制器类
 * @Version: 1.0
 */
@RestController
@RequestMapping("/batch")
@Api(tags = "批次查询")
public class BatchQueryController implements BatchQueryApis {
    @GetMapping("/batch/list")
    @ApiOperation(value = "获取批次列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<BatchListDTO>> listBatch(BatchQuery query) {
        return null;
    }


    /**
     * 获取指定批次详情数据
     * @param batchDetailQuery
     * @return
     */
    @GetMapping("/detail")
    @ApiOperation(value = "获取指定批次详情数据")
    @Override
    public JsonVO<PageDTO<BatchDetailDTO>> getBatchDetail(BatchDetailQuery batchDetailQuery) {
        return null;
    }
    @GetMapping("/export")
    @ApiOperation(value = "导出批次Excel")
    @Override
    public ResponseEntity<byte[]> exportBatchListExcel(BatchQuery query) {
        return null;
    }

    @GetMapping("/exportDetail")
    @ApiOperation(value = "导出批次详情Excel")
    @Override
    public ResponseEntity<byte[]> exportBatchDetailExcel(BatchDetailQuery query) {
        return null;
    }
}
