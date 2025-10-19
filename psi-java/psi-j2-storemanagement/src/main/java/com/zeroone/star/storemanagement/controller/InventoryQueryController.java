package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.j2.store.InventoryQueryApis;
import io.swagger.annotations.Api;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.controller
 * @Author: 高
 * @CreateTime: 2025-10-19 18:48
 * @Description: 库存查询控制器类
 * @Version: 1.0
 */
@RestController
@RequestMapping("/store")
@Api(tags = "库存查询相关接口")
public class InventoryQueryController implements InventoryQueryApis {
}
