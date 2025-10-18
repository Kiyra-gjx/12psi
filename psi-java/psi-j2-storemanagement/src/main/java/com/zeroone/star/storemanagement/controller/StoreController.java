package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.j2.store.StoreApis;
import io.swagger.annotations.Api;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.controller
 * @Author: 高
 * @CreateTime: 2025-10-18 12:15
 * @Description: TODO
 * @Version: 1.0
 */
@RestController
@RequestMapping("/store")
@Api(tags = "仓库管理")
@Validated
public class StoreController implements StoreApis {

}
