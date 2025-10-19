package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.j2.store.OtherOutApis;
import io.swagger.annotations.Api;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.controller
 * @Author: 高
 * @CreateTime: 2025-10-19 18:50
 * @Description: 其他出库单控制器类
 * @Version: 1.0
 */
@RestController
@RequestMapping("/otherout")
@Api(tags = "其他出库单相关接口")
public class OtherOutController implements OtherOutApis {
}
