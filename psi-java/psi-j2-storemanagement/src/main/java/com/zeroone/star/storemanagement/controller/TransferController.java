package com.zeroone.star.storemanagement.controller;

import cn.hutool.core.date.DateTime;
import cn.hutool.core.util.IdUtil;
import com.alibaba.excel.EasyExcel;
import com.alibaba.excel.context.AnalysisContext;
import com.alibaba.excel.event.AnalysisEventListener;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsClientComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsFileInfo;
import com.zeroone.star.project.components.jwt.JwtComponent;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.ShopListDTO;
import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.dto.j2.store.TransferDetailListDTO;
import com.zeroone.star.project.dto.j2.store.TransferListDTO;
import com.zeroone.star.project.j2.store.TransferApis;
import com.zeroone.star.project.query.j2.store.TransferQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.entity.GoodsDO;
import com.zeroone.star.storemanagement.entity.SwapDO;
import com.zeroone.star.storemanagement.entity.SwapInfoDO;
import com.zeroone.star.storemanagement.mapper.GoodsMapper;
import com.zeroone.star.storemanagement.mapper.SwapInfoMapper;
import com.zeroone.star.storemanagement.mapper.SwapMapper;
import com.zeroone.star.storemanagement.service.ISwapService;
import com.zeroone.star.storemanagement.service.ITransferService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import lombok.SneakyThrows;
import org.apache.poi.hpsf.Decimal;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.ResponseEntity;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.math.BigDecimal;
import java.nio.charset.StandardCharsets;
import java.time.LocalDate;
import java.util.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.controller
 * @Author: 高
 * @CreateTime: 2025-10-19 18:51
 * @Description: 调拨单控制器类
 * @Version: 1.0
 */
@RestController
@RequestMapping("/transfer")
@Api(tags = "调拨单")
@Slf4j
public class TransferController implements TransferApis {
    private final ITransferService transferService;
    @Autowired
    private SwapMapper swapMapper;

    public TransferController(ITransferService transferService) {
        this.transferService = transferService;
    }

    @GetMapping("/query-transferList")
    @ApiOperation(value = "获取调拨单列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<TransferListDTO>> queryTransferList(
            @ApiParam(value = "调拨单查询条件", required = true)
            @RequestBody
            TransferQuery transferQuery) {
        return null;
    }

    @GetMapping("/detail-transferInfo")
    @ApiOperation(value = "获取指定调拨单详细信息")
    @Override
    public JsonVO<TransferDetailListDTO> detailTransferList(
            /*根据商品信息获取调拨单*/
            @ApiParam(value = "商品信息", required = false)
            @RequestBody
            ShopListDTO shopListDto) {
        return null;
    }

    @PostMapping("/add-transferList")
    @ApiOperation(value = "新增调拨单")
    @Override
    public JsonVO<List<TransferDetailListDTO>> addTransferList(
            /*根据商品列表新增调拨单，可以批量*/
            @ApiParam(value = "商品列表", required = false)
            @RequestBody
            List<ShopListDTO> shopListDto) {
        return null;
    }

    @PutMapping("/modify-transfer")
    @ApiOperation(value = "修改调拨单")
    @Override
    public JsonVO<String> modifyTransfer(@RequestBody TransferDetailDTO dto) {
        return transferService.modifyTransfer(dto);
    }

    @PostMapping("/batch-audit-transfer")
    @ApiOperation(value = "审核/反审核(支持批量)")
    @Override
    public JsonVO<String> batchAuditTransfer(
            @ApiParam(value = "调拨单ID列表", required = true, example = "[1,2,3]")
            @RequestBody List<Integer> ids,
            @ApiParam(value = "操作类型（0-未审核，1-已审核）", required = true, example = "1")
            @RequestParam Integer operation) {
        return transferService.batchAuditTransfer(ids, operation);
    }

    @PostMapping("/remove-transfer")
    @ApiOperation(value = "删除调拨单(支持批量)")
    @Override
    public JsonVO<String> removeTransfer(@RequestBody List<Integer> ids) {
        return transferService.deleteTransfer(ids);
    }

    @Resource
    ISwapService swapService;

    @Resource
    SwapInfoMapper swapInfoMapper;

    @Resource
    EasyExcelComponent excel;

    @Resource
    FastDfsClientComponent dfs;

    @Resource
    UserHolder userHolder;

    @Resource
    GoodsMapper goodsMapper;

    @SneakyThrows
    @PostMapping("/import")
    @ApiOperation(value = "导入数据")
    public JsonVO<String> importTransferList(@RequestPart("file") MultipartFile file) {
        if(file.isEmpty()) {
            return JsonVO.fail("文件为空");
        }

        ArrayList<SwapDO> swapList = new ArrayList<>();
        ArrayList<SwapInfoDO>  swapInfoList = new ArrayList<>();
        ArrayList<String> goodsNames = new ArrayList<>();

        try {
            EasyExcel.read(file.getInputStream(), new AnalysisEventListener<Map<Integer, String>>() {
                @Override
                public void invoke(Map<Integer, String> data, AnalysisContext context) {
                    int rowIndex = context.readRowHolder().getRowIndex();
                    if(rowIndex < 2) {
                        return;
                    }
                    boolean isEmpty = data.values().stream().allMatch(v -> v == null || v.trim().isEmpty());
                    if(isEmpty) {
                        return; // 空行直接跳过
                    }

                    if(rowIndex == 2) {
                        SwapDO swap = new SwapDO();
                        swap.setTime(new DateTime(data.get(0)));
                        swap.setNumber(data.get(1));
                        swap.setTotal(new BigDecimal(data.get(2) == null?"0":data.get(2)));
                        swap.setPeople(data.get(3));
                        swap.setLogistics(data.get(4));
                        swap.setData(data.get(5));
                        swapList.add(swap);
                    }
                    SwapInfoDO swapInfo = new SwapInfoDO();
                    goodsNames.add(data.get(6));
                    swapInfo.setAttr(data.get(7));
                    swapInfo.setUnit(data.get(8)== null?"":data.get(8));
                    swapInfo.setWarehouse(data.get(9));
                    swapInfo.setStorehouse(data.get(10));
                    swapInfo.setBatch(data.get(11)== null?"":data.get(11));
                    swapInfo.setMfd(new DateTime(data.get(12) == null?"":data.get(12)));
                    swapInfo.setPrice(new BigDecimal(data.get(13)== null?"0":data.get(13)));
                    swapInfo.setNums(new BigDecimal(data.get(14)== null?"0":data.get(14)));
                    swapInfo.setSerial(data.get(15)== null?"":data.get(15));
                    swapInfo.setTotal(new BigDecimal(data.get(16)== null?"0":data.get(16)));
                    swapInfo.setData(data.get(17));
                    swapInfoList.add(swapInfo);
                }

                @Override
                public void doAfterAllAnalysed(AnalysisContext context) {
                    System.out.println("主表数据：" + swapList);
                    System.out.println("商品名称：" + goodsNames);
                    System.out.println("明细数据：" + swapInfoList);
                }
            }).sheet().doRead();
        } catch (Exception e) {
            e.printStackTrace();
            return JsonVO.fail("fail");
        }
        UserDTO currentUser;
        try {
            currentUser = userHolder.getCurrentUser();
        } catch (Exception e) {
            // 如果解析token失败，就临时伪造一个用户
            currentUser = UserDTO.builder()
                    .id("1")
                    .username("系统导入")
                    .frameName("总部")
                    .build();
        }
        String id = IdUtil.getSnowflakeNextIdStr();
        swapList.get(0).setId(id);
        swapList.get(0).setFrame(currentUser.getFrameName());
        swapList.get(0).setCost(BigDecimal.ZERO);
        swapList.get(0).setUser(currentUser.getUsername());

        for(int i=0;i<swapInfoList.size();i++) {
            swapInfoList.get(i).setPid(swapList.get(0).getId());
            GoodsDO good = goodsMapper.selectOne(new QueryWrapper<GoodsDO>().eq("name", goodsNames.get(i)));
            swapInfoList.get(i).setGoods(good.getId());
            swapInfoMapper.insert(swapInfoList.get(i));
        }
        swapMapper.insert(swapList.get(0));
        System.out.println("主表数据：" + swapList);
        System.out.println("明细数据：" + swapInfoList);
        return new JsonVO<String>(200,"success",null);
    }

    @SneakyThrows
    @PostMapping("/export")
    @ApiOperation(value = "导出简单报表")
    public ResponseEntity<byte[]> exportTransferList(@RequestBody List<String> idList) {
        if(idList.isEmpty()) {
            return new ResponseEntity<>("列表为空".getBytes(),HttpStatus.BAD_REQUEST);
        }
        ArrayList<TransferListDTO> transferListDTOList = swapService.getTransferListDTOList(idList);
        if (transferListDTOList.isEmpty()) {
            return new ResponseEntity<>("无数据".getBytes(),HttpStatus.BAD_REQUEST);
        }
        ByteArrayOutputStream out = new ByteArrayOutputStream();

        excel.export("简单报表",out,TransferListDTO.class,transferListDTOList);
        out.flush();

        HttpHeaders headers = new HttpHeaders();
        String filename = DateTime.now().toString("yyyyMMddHHmmssS")+ ".xlsx";
        headers.setContentDispositionFormData("attachment", filename);
        headers.setContentType(MediaType.APPLICATION_OCTET_STREAM);
        ResponseEntity<byte[]> res = new ResponseEntity<>(out.toByteArray(),headers,HttpStatus.CREATED);
        out.close();
        return res;
    }

    @SneakyThrows
    @PostMapping("/exportDetail")
    @ApiOperation(value = "导出详细报表")
    public ResponseEntity<byte[]> exportTransferDetailList(@RequestBody List<String> idList) {
        if(idList.isEmpty()) {
            return new ResponseEntity<>("列表为空".getBytes(),HttpStatus.BAD_REQUEST);
        }
        ArrayList<ArrayList<TransferDetailListDTO>> transferDetailListDTOList = swapService.getTransferDetailListDTOList(idList);
        if (transferDetailListDTOList.isEmpty()) {
            return new ResponseEntity<>("无数据".getBytes(),HttpStatus.BAD_REQUEST);
        }
        ByteArrayOutputStream zip = new ByteArrayOutputStream();
        ZipOutputStream zipOutputStream = new ZipOutputStream(zip);
        for (ArrayList<TransferDetailListDTO> transferDetailListDTO : transferDetailListDTOList) {
            if(transferDetailListDTO.isEmpty()) {
                continue;
            }
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            excel.export("详细报表",out,TransferDetailListDTO.class,transferDetailListDTO);
            out.flush();
            zipOutputStream.putNextEntry(new ZipEntry("详细报表"+DateTime.now().toString("yyyyMMddHHmmssS")+".xlsx"));
            zipOutputStream.write(out.toByteArray());
            zipOutputStream.closeEntry();
            out.close();
        }
        zip.close();
        zipOutputStream.close();
        HttpHeaders headers = new HttpHeaders();
        headers.setContentDispositionFormData("attachment", "detail"+new DateTime().now().toString("yyyyMMddHHmmss")+".zip");
        headers.setContentType(MediaType.APPLICATION_OCTET_STREAM);
        ResponseEntity<byte[]> res = new ResponseEntity<>(zip.toByteArray(),headers,HttpStatus.CREATED);
        return res;
    }


}
