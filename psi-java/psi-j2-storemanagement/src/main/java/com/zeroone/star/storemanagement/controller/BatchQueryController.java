package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.j2.store.BatchQueryApis;
import com.zeroone.star.project.query.j2.store.BatchDetailQuery;
import com.zeroone.star.project.query.j2.store.BatchQuery;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
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
@Api(tags = "批次查询相关接口")
public class BatchQueryController implements BatchQueryApis {
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
