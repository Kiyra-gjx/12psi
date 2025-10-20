package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.j2.store.OtherOutListDTO;
import com.zeroone.star.project.dto.j2.store.OtherOutListInfoDTO;
import com.zeroone.star.project.j2.store.OtherOutApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

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
