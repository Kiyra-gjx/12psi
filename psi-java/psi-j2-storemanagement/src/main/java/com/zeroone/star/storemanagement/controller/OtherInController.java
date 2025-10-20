package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.j2.store.OtherInListDTO;
import com.zeroone.star.project.j2.store.OtherInApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

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
}
