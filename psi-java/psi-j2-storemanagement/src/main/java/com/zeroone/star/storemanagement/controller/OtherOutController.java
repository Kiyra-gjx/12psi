package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.j2.store.OtherOutListDTO;
import com.zeroone.star.project.j2.store.OtherOutApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.*;
import java.util.List;


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
    @PutMapping("/examine")
    @ApiOperation(value = "审核出库单")
    @Override
    public JsonVO<String> examine(List<Integer> ids) {
        return null;
    }
    @PutMapping("/check")
    @ApiOperation(value = "核对出库单")
    @Override
    public JsonVO<String> check(List<Integer> ids) {
        return null;
    }
    @PutMapping("/update")
    @ApiOperation(value = "修改其他出库单")
    @Override
    public JsonVO<String> updateOtherOutList(OtherOutListDTO otherOutListDTO) {
        // TODO: 实现修改其他出库单的业务逻辑
        // 1. 参数验证
        // 2. 检查出库单是否存在
        // 3. 检查出库单状态是否允许修改
        // 4. 更新出库单信息
        // 5. 更新库存信息
        // 6. 记录操作日志
        return JsonVO.success("修改成功");
    }
    @DeleteMapping("/delete")
    @ApiOperation(value = "删除其他出库单")
    @Override
    public JsonVO<String> deleteOtherOutList(List<Integer> ids) {
        // TODO: 实现删除其他出库单的业务逻辑
        // 1. 参数验证
        // 2. 检查出库单是否存在
        // 3. 检查出库单状态是否允许删除
        // 4. 删除出库单明细
        // 5. 删除出库单主表
        // 6. 恢复库存信息
        // 7. 记录操作日志
        return JsonVO.success("删除成功");
    }


}
