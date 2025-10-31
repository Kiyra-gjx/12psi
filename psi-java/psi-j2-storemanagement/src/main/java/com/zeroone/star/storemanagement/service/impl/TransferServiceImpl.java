package com.zeroone.star.storemanagement.service.impl;

import com.zeroone.star.project.dto.j2.store.BatchAuditTransferDTO;
import com.zeroone.star.project.dto.j2.store.RemoveTransferDTO;
import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.entity.SwapDO;
import com.zeroone.star.storemanagement.entity.SwapInfoDO;
import com.zeroone.star.storemanagement.mapper.SwapInfoMapper;
import com.zeroone.star.storemanagement.mapper.SwapMapper;
import com.zeroone.star.storemanagement.service.ITransferService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

@Service
@Slf4j
public class TransferServiceImpl implements ITransferService {
    private final SwapMapper swapMapper;
    private final SwapInfoMapper swapInfoMapper;

    public TransferServiceImpl(SwapMapper swapMapper, SwapInfoMapper swapInfoMapper) {
        this.swapMapper = swapMapper;
        this.swapInfoMapper = swapInfoMapper;
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<String> modifyTransfer(TransferDetailDTO dto) {
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

    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<String> batchAuditTransfer(BatchAuditTransferDTO dto) {
        try {
            List<Integer> ids = dto.getIds();
            Integer operation = dto.getOperation();
            if (operation != 0 && operation != 1) {
                return JsonVO.fail("操作参数错误，0-反审核，1-审核");
            } else if (ids == null || ids.isEmpty()) {
                return JsonVO.fail("请选择要" + (operation == 1 ? "审核" : "反审核") + "的调拨单");
            }

            // 1.检查调拨单状态并收集需要审核/反审核的数据
            List<String> validPidList = new ArrayList<>();
            String operationName = operation == 1 ? "审核" : "反审核";

            for (Integer id : ids) {
                // 1.1 获取对应的主表ID
                String pid = swapInfoMapper.getSwapById(id.toString());
                if (pid == null) {
                    return JsonVO.fail("调拨单不存在，ID: " + id);
                }

                // 1.2 获取当前状态
                Integer status = swapMapper.getStatusById(pid);
                if (status == null) {
                    return JsonVO.fail("调拨单状态异常，ID: " + id);
                }

                // 1.3 验证状态转换的合法性
                if ((status ^ operation) != 1) {
                    return JsonVO.fail("调拨单状态转换异常，ID: " + id + " 当前状态: " + (status == 0 ? "未审核" : "已审核"));
                }

                validPidList.add(pid);
            }

            // 2.执行批量审核/反审核操作
            int auditCount = swapMapper.auditBatchStatus(validPidList, operation);

            if (auditCount == 0) {
                return JsonVO.fail(operationName + "调拨单失败，未找到符合条件的记录");
            }

            // 3.记录操作日志
            log.info("批量{}调拨单成功，操作数量：{}，ID列表：{}", operationName, auditCount, ids);

            return JsonVO.success("成功" + operationName + " " + auditCount + " 个调拨单");

        } catch (Exception e) {
            log.error("批量审核调拨单失败", e);
            return JsonVO.fail("批量审核调拨单失败: " + e.getMessage());
        }
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<String> deleteTransfer(RemoveTransferDTO dto) {
        try {
            List<Integer> ids = dto.getIds();
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
        if (Objects.equals(dto.getInfo().getStorehouse(), dto.getInfo().getWarehouse())) {
            return false;
        }
        return dto.getInfo().getNums() == null || dto.getInfo().getNums().compareTo(BigDecimal.ZERO) >= 0;
    }
}
