package com.zeroone.star.storemanagement.controller;

import cn.hutool.core.date.DateTime;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.storemanagement.test.entity.User;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.SneakyThrows;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import javax.annotation.PostConstruct;
import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.util.ArrayList;
import java.util.List;

/**
 * <p>
 * 描述：Excel操作示例接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Controller
@RequestMapping("/excel")
@Api(tags = "Excel操作示例接口")
public class ExcelController {
    private List<User> users;

    @PostConstruct
    public void initData() {
        users = new ArrayList<>();
        for (int i = 1; i < 11; i++) {
            User user = new User();
            user.setId(i);
            user.setName("Controller" + i);
            user.setPhone("1234567890" + i);
            users.add(user);
        }
    }

    @Resource
    EasyExcelComponent excel;

    @SneakyThrows
    @GetMapping(value = "/export", produces = "application/octet-stream")
    @ApiOperation(value = "导出Excel")
    public ResponseEntity<byte[]> exportExcel() {
        // 定义输出流
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        // 生成Excel
        excel.export("用户信息", out, User.class, users);
        // 响应给前端
        HttpHeaders headers = new HttpHeaders();
        String filename = "rep-" + DateTime.now().toString("yyyyMMddHHmmssS") + ".xlsx";
        headers.setContentDispositionFormData("attachment", filename);
        headers.setContentType(MediaType.APPLICATION_OCTET_STREAM);
        ResponseEntity<byte[]> res = new ResponseEntity<>(out.toByteArray(), headers, HttpStatus.CREATED);
        out.close();
        return res;
    }
}
