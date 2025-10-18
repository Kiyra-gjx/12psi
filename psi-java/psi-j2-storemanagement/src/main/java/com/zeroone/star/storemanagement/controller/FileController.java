package com.zeroone.star.storemanagement.controller;

import cn.hutool.core.date.DateTime;
import com.zeroone.star.project.components.fastdfs.FastDfsClientComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsFileInfo;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.SneakyThrows;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;

/**
 * <p>
 * 描述：文件操作示例接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Controller
@RequestMapping("/file")
@Api(tags = "文件操作示例接口")
public class FileController {
    @Resource
    FastDfsClientComponent dfs;

    @Value("${fastdfs.nginx-servers}")
    private String fileServerUrl;

    @SneakyThrows
    @PostMapping("/upload")
    @ResponseBody
    @ApiOperation(value = "上传文件")
    public JsonVO<String> uploadFile(MultipartFile file) {
        // 获取文件后缀名
        String filename = file.getOriginalFilename();
        assert filename != null;
        String extName = filename.substring(filename.lastIndexOf(".") + 1);
        // 上传文件
        FastDfsFileInfo info = dfs.uploadFile(file.getBytes(), extName);
        if (info != null) {
            return JsonVO.success(dfs.fetchUrl(info, fileServerUrl, true));
        }
        return JsonVO.fail(null);
    }

    @SneakyThrows
    @GetMapping(value = "/download", produces = "image/png")
    @ApiOperation(value = "下载文件")
    public ResponseEntity<byte[]> download(String group, String storageId) {
        // 下载文件到内存中
        FastDfsFileInfo info = FastDfsFileInfo.builder()
                .group(group)
                .storageId(storageId)
                .build();
        byte[] bytes = dfs.downloadFile(info);
        // 响应文件给前端
        HttpHeaders headers = new HttpHeaders();
        String filename = "img-" + DateTime.now().toString("yyyyMMddHHmmssS") + ".png";
        headers.setContentDispositionFormData("attachment", filename);
        headers.setContentType(MediaType.IMAGE_PNG);
        return new ResponseEntity<>(bytes, headers, HttpStatus.CREATED);
    }

    @SneakyThrows
    @ResponseBody
    @DeleteMapping("/delete")
    @ApiOperation(value = "删除文件")
    public JsonVO<Integer> deleteFile(String group, String storageId) {
        // 删除文件
        FastDfsFileInfo info = FastDfsFileInfo.builder()
                .group(group)
                .storageId(storageId)
                .build();
        int i = dfs.deleteFile(info);
        if (i == 0) {
            return JsonVO.success(i);
        }
        return JsonVO.fail(i);
    }
}
