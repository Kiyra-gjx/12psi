package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.j2.store.SequenceQueryApis;
import io.swagger.annotations.Api;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.controller
 * @Author: 高
 * @CreateTime: 2025-10-19 19:49
 * @Description: 序列查询相关接口
 * @Version: 1.0
 */
@RestController
@RequestMapping("/verify")
@Api(tags = "序列查询相关接口")
public class SequenceQueryController implements SequenceQueryApis {
}
