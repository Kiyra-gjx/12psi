package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.j2.store.BatchQueryApis;
import io.swagger.annotations.Api;
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
}
