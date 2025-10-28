package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.ShopListDTO;
import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.dto.j2.store.TransferDetailListDTO;
import com.zeroone.star.project.dto.j2.store.TransferListDTO;
import com.zeroone.star.project.j2.store.TransferApis;
import com.zeroone.star.project.query.j2.store.TransferQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.entity.SwapDO;
import com.zeroone.star.storemanagement.entity.SwapInfoDO;
import com.zeroone.star.storemanagement.mapper.SwapInfoMapper;
import com.zeroone.star.storemanagement.mapper.SwapMapper;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.ResponseEntity;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.math.BigDecimal;
import java.util.List;

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
    private final SwapMapper swapMapper;
    private final SwapInfoMapper swapInfoMapper;

    public TransferController(SwapMapper swapMapper, SwapInfoMapper swapInfoMapper) {
        this.swapMapper = swapMapper;
        this.swapInfoMapper = swapInfoMapper;
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
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<String> modifyTransfer(@RequestBody TransferDetailDTO dto) {
        try {
            // // 1.权限校验
            // Authentication auth = SecurityContextHolder.getContext().getAuthentication();
            // if (auth == null || !auth.isAuthenticated()) {
            //     return JsonVO.fail("用户未登录");
            // }
            //
            // String username = auth.getName();
            // log.info("{} 正在修改调拨单 {}", username, dto.getInfo().getId());

            // 2.查询调拨单当前状态
            String pid = swapInfoMapper.getSwapById(dto.getInfo().getId());
            Integer currentStatus = swapMapper.getStatusById(pid);
            if (pid == null || currentStatus == null) {
                return JsonVO.fail("调拨单不存在");
            }

            // 3.检查状态是否为未审核
            if (currentStatus != 0) {
                return JsonVO.fail("只能修改草稿状态的调拨单");
            }

            // 4.数据合法性校验
            if (!validateData(dto)) {
                return JsonVO.fail("数据不合法");
            }

            // 5.更新调拨单信息
            SwapInfoDO swapInfoDO = new SwapInfoDO();

            if (dto.getInfo() != null) {
                TransferDetailDTO.Info info = dto.getInfo();

                // 设置 swapInfoDO
                swapInfoDO.setId(info.getId());
                if (info.getWarehouse() != null) {
                    swapInfoDO.setWarehouse(info.getWarehouse());
                }
                if (info.getStorehouse() != null) {
                    swapInfoDO.setStorehouse(info.getStorehouse());
                }
                swapInfoDO.setPrice(info.getPrice());
                swapInfoDO.setNums(info.getNums());
                swapInfoDO.setData(info.getData());
            }

            // 6.更新 swap 表
            SwapDO swapDO = new SwapDO();
            // 设置 ID
            swapDO.setId(pid);

            // 设置其他字段
            if (dto.getClassInfo() != null) {
                swapDO.setData(dto.getClassInfo().getData());
                swapDO.setLogistics(dto.getClassInfo().getLogistics());
                swapDO.setPeople(dto.getClassInfo().getPeople());
                swapDO.setFile(dto.getClassInfo().getFile());
            }

            int updateCount1 = swapMapper.updateSwap(swapDO);
            int updateCount2 = swapInfoMapper.updateSwap(swapInfoDO);
            int updateCount = Math.max(updateCount1, updateCount2);

            log.info("更新影响行数: swap={}, swap_info={}, final={}", updateCount1, updateCount2, updateCount);

            if (updateCount == 0) {
                return JsonVO.fail("更新调拨单失败");
            }

            return JsonVO.success("修改调拨单成功，ID: " + dto.getInfo().getId());

        } catch (Exception e) {
            log.error("修改调拨单失败", e);
            return JsonVO.fail("修改调拨单失败: " + e.getMessage());
        }
    }

    @PostMapping("/batch-audit-transfer")
    @ApiOperation(value = "审核/反审核(支持批量)")
    @Override
    public JsonVO<String> batchAuditTransfer(
            @ApiParam(value = "调拨单ID列表", required = true, example = "1,2,3")
            @RequestBody List<Integer> ids,
            @ApiParam(value = "操作类型（0-未审核，1-已审核）", required = true, example = "1")
            @RequestParam Integer operation) {
        String operationName = operation == 1 ? "审核" : "反审核";
        return JsonVO.success("批量" + operationName + "成功，操作 " + ids.size() + " 条单据");
    }

    @PostMapping("/remove-transfer")
    @ApiOperation(value = "删除调拨单(支持批量)")
    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<String> removeTransfer(@RequestBody List<Integer> ids) {
        try {
            if (ids == null || ids.isEmpty()) {
                return JsonVO.fail("请选择要删除的调拨单");
            }

            // 1.检查调拨单状态并收集需要删除的数据
            for (Integer id : ids) {
                String pid = swapInfoMapper.getSwapById(id.toString());
                if (pid == null) {
                    return JsonVO.fail("调拨单不存在，ID: " + id);
                }

                Integer status = swapMapper.getStatusById(pid);
                if (status == null || status != 0) {
                    return JsonVO.fail("只能删除草稿状态的调拨单，ID: " + id);
                }
            }

            // 2.获取对应的主表ID
            List<String> pidList = swapInfoMapper.getPidListByIds(ids);

            // 3.先删除 swap_info 表中的记录
            int deleteInfoCount = swapInfoMapper.deleteBatchIds(ids);

            // 4.再删除 swap 表中的记录
            int deleteMainCount = 0;
            if (pidList != null && !pidList.isEmpty()) {
                deleteMainCount = swapMapper.deleteBatchIds(pidList);
            }

            log.info("删除调拨单成功: 删除详情记录 {} 条, 删除主表记录 {} 条", deleteInfoCount, deleteMainCount);

            if (deleteInfoCount == 0) {
                return JsonVO.fail("删除调拨单失败");
            }

            return JsonVO.success("成功删除 " + deleteInfoCount + " 个调拨单");

        } catch (Exception e) {
            log.error("删除调拨单失败", e);
            return JsonVO.fail("删除调拨单失败: " + e.getMessage());
        }
    }

    @PostMapping("/import")
    @ApiOperation(value = "导入数据")
    public JsonVO<String> importTransferList(@RequestPart("file") MultipartFile file) {
        return null;
    }

    @PostMapping("/export")
    @ApiOperation(value = "导出简单报表")
    public ResponseEntity<byte[]> exportTransferList(@RequestBody List<String> idList) {
        return null;
    }

    @PostMapping("/exportDetail")
    @ApiOperation(value = "导出详细报表")
    public ResponseEntity<byte[]> exportTransferDetailList(@RequestBody List<String> idList) {
        return null;
    }

    /**
     * 数据合法性校验
     */
    private boolean validateData(TransferDetailDTO dto) {
        if (dto == null || dto.getInfo() == null) {
            return false;
        }
        if (dto.getInfo().getId() == null || dto.getInfo().getId().trim().isEmpty()) {
            return false;
        }
        if (dto.getInfo().getPrice() != null && dto.getInfo().getPrice().compareTo(BigDecimal.ZERO) < 0) {
            return false;
        }
        return dto.getInfo().getNums() == null || dto.getInfo().getNums().compareTo(BigDecimal.ZERO) >= 0;
    }
}
