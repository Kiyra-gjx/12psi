package com.zeroone.star.storemanagement.service.impl;

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
import java.util.List;

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
    public JsonVO<String> deleteTransfer(List<Integer> ids) {
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
