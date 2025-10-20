package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDTO;
import com.zeroone.star.project.dto.j2.store.OtherOutListDTO;
import com.zeroone.star.project.dto.j2.store.OtherOutListInfoDTO;
import com.zeroone.star.project.j2.store.OtherOutApis;
import com.zeroone.star.project.query.j2.store.OtherInQuery;
import com.zeroone.star.project.query.j2.store.OtherOutQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.*;
import java.util.List;
import org.springframework.web.multipart.MultipartFile;


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
@Api(tags = "其他出库单")
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

    @GetMapping("/list")
    @ApiOperation(value = "获取出库单列表")
    @Override
    public JsonVO<PageDTO<OtherOutListDTO>> listOtherOut(OtherOutQuery query) {
        return null;
    }

    @GetMapping("/getInfo")
    @ApiOperation(value = "获取出库单详情")
    @ApiImplicitParam(name = "id", value = "其他出库单编号", required = true, example = "1d7b0520e93e72715d5d6af1fb7d9a37")
    @Override
    public JsonVO<String> getOtherOutListInfo(Integer id) {
        return null;
    }

    @PostMapping("/add")
    @ApiOperation(value = "添加出库单")
    @Override
    public JsonVO<String> addOtherOutList(OtherOutListDTO otherOutListDTO) {
        return JsonVO.success("添加成功");
    }


    @GetMapping("/export")
    @ApiOperation(value = "导出其他出库单数据Excel")
    @Override
    public ResponseEntity<byte[]> exportOrderListExcel(OtherOutListDTO otherInListDTO) {
        return null;
    }

    @GetMapping("/exportDetail")
    @ApiOperation(value = "导出其他出库单详情数据Excel")
    @Override
    public ResponseEntity<byte[]> exportOrderDetailExcel(OtherOutListInfoDTO otherInListInfoDTO) {
        return null;
    }

    @PostMapping("/import")
    @ApiOperation(value = "批量导入其他出库单")
    @Override
    public ResponseEntity<JsonVO<String>> importOrderList(MultipartFile file) {return null;}

}
