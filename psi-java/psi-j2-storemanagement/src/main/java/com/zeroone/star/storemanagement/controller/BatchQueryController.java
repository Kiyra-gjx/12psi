package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchDetailDTO;
import com.zeroone.star.project.j2.store.BatchQueryApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
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


    /**
     * 获取指定批次详情数据
     * @param id
     * @return
     */
    @RequestMapping("/detailRecord")
    @ApiOperation(value = "获取指定批次详情数据")
    @Override
    public JsonVO<PageDTO<BatchDetailDTO>> getBatchDetail(int id) {
        return null;
    }
}
