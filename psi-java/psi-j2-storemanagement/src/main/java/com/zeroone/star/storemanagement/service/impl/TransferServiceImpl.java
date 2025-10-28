package com.zeroone.star.storemanagement.service.impl;

import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.entity.SwapInfoDO;
import com.zeroone.star.storemanagement.mapper.SwapMapper;
import com.zeroone.star.storemanagement.service.ITransferService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;

@Service
@Slf4j
public class TransferServiceImpl implements ITransferService {

    @Autowired
    private SwapMapper swapMapper;

    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<String> modifyTransfer(TransferDetailDTO dto) {
        try {

            // 1.查询调拨单当前状态
            Integer currentStatus = swapMapper.getStatusById(dto.getInfo().getId());
            if (currentStatus == null) {
                return JsonVO.fail("调拨单不存在");
            }

            // 2.检查状态是否为未审核
            if (currentStatus != 0) {
                return JsonVO.fail("只能修改草稿状态的调拨单");
            }

            // 3.数据合法性校验
            if (!validateData(dto)) {
                return JsonVO.fail("数据不合法");
            }

            // 4.更新调拨单信息
            SwapInfoDO swapDO = new SwapInfoDO();
            BeanUtils.copyProperties(dto, swapDO);
            swapDO.setData(dto.getClassInfo().getData());

            int updateCount = swapMapper.updateSwap(swapDO);
            if (updateCount == 0) {
                return JsonVO.fail("更新调拨单失败");
            }

            // 5.记录操作日志（需要实现日志服务）
            logOperation(dto.getInfo().getId(), "修改调拨单");

            return JsonVO.success("修改调拨单成功，ID: " + dto.getInfo().getId());

        } catch (Exception e) {
            log.error("修改调拨单失败", e);
            return JsonVO.fail("修改调拨单失败: " + e.getMessage());
        }
    }

    /**
     * 用户权限校验
     */
    private boolean checkUserPermission() {
        // TODO: 实现具体的权限校验逻辑
        // 从安全上下文获取当前用户信息并校验权限
        return true; // 暂时返回true
    }

    /**
     * 数据合法性校验
     */
    private boolean validateData(TransferDetailDTO dto) {
        if (dto.getInfo().getId() == null || dto.getInfo().getId().trim().isEmpty()) {
            return false;
        }
        if (dto.getInfo().getPrice() != null && dto.getInfo().getPrice().compareTo(BigDecimal.ZERO) < 0) {
            return false;
        }
        if (dto.getInfo().getNums() != null && dto.getInfo().getNums().compareTo(BigDecimal.ZERO) < 0) {
            return false;
        }
        return true;
    }

    /**
     * 记录操作日志
     */
    private void logOperation(String transferId, String operation) {
        // TODO: 实现操作日志记录
        log.info("操作日志 - 调拨单ID: {}, 操作: {}", transferId, operation);
    }
}
