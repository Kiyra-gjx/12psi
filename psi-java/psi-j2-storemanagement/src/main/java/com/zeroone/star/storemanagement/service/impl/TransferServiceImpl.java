package com.zeroone.star.storemanagement.service.impl;

import com.zeroone.star.project.dto.j2.store.BatchAuditTransferDTO;
import com.zeroone.star.project.dto.j2.store.RemoveTransferDTO;
import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.entity.*;
import com.zeroone.star.storemanagement.mapper.*;
import com.zeroone.star.storemanagement.service.ITransferService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;

@Service
@Slf4j
public class TransferServiceImpl implements ITransferService {
    private final SwapMapper swapMapper;
    private final SwapInfoMapper swapInfoMapper;
    private final RoomMapper roomMapper;
    private final RoomInfoMapper roomInfoMapper;
    private final BatchMapper batchMapper;
    private final BatchInfoMapper batchInfoMapper;
    private final CostMapper costMapper;

    public TransferServiceImpl(SwapMapper swapMapper, SwapInfoMapper swapInfoMapper,
                               RoomMapper roomMapper, RoomInfoMapper roomInfoMapper,
                               BatchMapper batchMapper, BatchInfoMapper batchInfoMapper, CostMapper costMapper) {
        this.swapMapper = swapMapper;
        this.swapInfoMapper = swapInfoMapper;
        this.roomMapper = roomMapper;
        this.roomInfoMapper = roomInfoMapper;
        this.batchMapper = batchMapper;
        this.batchInfoMapper = batchInfoMapper;
        this.costMapper = costMapper;
    }

    private static String classId = "0";

    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<String> modifyTransfer(TransferDetailDTO dto) {
        try {
            // 1.查询调拨单当前状态
            String pid = swapInfoMapper.getSwapById(dto.getInfo().getId());
            Integer currentStatus = swapMapper.getStatusById(pid);
            if (pid == null || currentStatus == null) {
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

            // 4 检查调出仓库和调入仓库是否相同
            if (dto.getInfo().getWarehouse().equals(dto.getInfo().getStorehouse())) {
                return JsonVO.fail("调出仓库和调入仓库不能相同");
            }

            // 5.计算单据费用总和
            BigDecimal totalCost = BigDecimal.ZERO;
            if (dto.getCost() != null) {
                for (TransferDetailDTO.costInfo costInfo : dto.getCost()) {
                    if (costInfo.getMoney() != null) {
                        totalCost = totalCost.add(costInfo.getMoney());
                    }
                }
            }

            // 6.更新调拨单信息
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
                swapInfoDO.setBatch(info.getBatch());
                swapInfoDO.setMfd(info.getMfd());
                swapInfoDO.setPrice(info.getPrice());
                swapInfoDO.setNums(info.getNums());
                swapInfoDO.setTotal(info.getPrice().multiply(info.getNums()));
                swapInfoDO.setData(info.getData());
            }

            // 7.更新 swap 表
            SwapDO swapDO = new SwapDO();
            // 设置 ID
            swapDO.setId(pid);

            // 设置其他字段
            if (dto.getClassInfo() != null) {
                swapDO.setTime(dto.getClassInfo().getTime());
                swapDO.setNumber(dto.getClassInfo().getNumber());
                swapDO.setTotal(swapInfoDO.getTotal());
                swapDO.setCost(totalCost); // 设置计算出的费用总和
                swapDO.setPeople(dto.getClassInfo().getPeople());
                swapDO.setLogistics(dto.getClassInfo().getLogistics());
                swapDO.setFile(dto.getClassInfo().getFile());
                swapDO.setData(dto.getClassInfo().getData());
            }

            // 处理单据费用
            if (dto.getClassInfo() == null) {
                return JsonVO.fail("单据信息不能为空");
            }
            if (dto.getCost() != null) {
                handleTransferCosts(pid, dto.getCost(), dto.getClassInfo().getTime());
            }

            int updateCount1 = swapMapper.updateSwap(swapDO, dto.getInfo().getPrice().multiply(dto.getInfo().getNums()));
            int updateCount2 = swapInfoMapper.updateSwap(swapInfoDO);
            int updateCount = Math.max(updateCount1, updateCount2);

            log.info("更新影响行数: swap={}, swap_info={}, final={}", updateCount1, updateCount2, updateCount);

            if (updateCount == 0) {
                return JsonVO.fail("更新调拨单失败");
            }

            return JsonVO.success(dto.getInfo().getId());

        } catch (Exception e) {
            log.error("修改调拨单失败", e);
            return JsonVO.fail("修改调拨单失败: " + e.getMessage());
        }
    }

    /**
     * 处理单据费用
     */
    private void handleTransferCosts(String transferId, List<TransferDetailDTO.costInfo> costInfos, LocalDate transferTime) {
        // 1. 获取现有的费用列表
        List<CostDO> existingCosts = costMapper.findByTransferId(transferId);

        // 2. 构建新费用ID集合
        Set<String> newCostIds = costInfos.stream()
                .map(TransferDetailDTO.costInfo::getId)
                .filter(Objects::nonNull)
                .collect(Collectors.toSet());

        // 3. 删除不在新列表中的费用
        for (CostDO existing : existingCosts) {
            if (!newCostIds.contains(existing.getId())) {
                costMapper.deleteById(existing.getId());
                log.info("删除费用记录: id={}", existing.getId());
            }
        }

        // // 4. 将 LocalDate 转换为时间戳
        // Integer timestamp = null;
        // if (transferTime != null) {
        //     timestamp = (int) (transferTime.atStartOfDay(ZoneId.systemDefault()).toInstant().toEpochMilli() / 1000);
        // }

        // 4. 新增或更新费用
        for (TransferDetailDTO.costInfo costInfo : costInfos) {
            CostDO costDO = new CostDO();
            costDO.setId(costInfo.getId());
            costDO.setType("swap");  // 类型为调拨单
            costDO.setCls(transferId);   // 关联调拨单ID
            costDO.setTime(transferTime);
            costDO.setIet(costInfo.getIet());  // 支出类别
            costDO.setMoney(costInfo.getMoney());  // 金额
            costDO.setData(costInfo.getData());    // 备注
            costDO.setSettle(BigDecimal.ZERO);     // 结算金额，默认0
            costDO.setState(0);                    // 状态，默认0

            if (!costMapper.isExist(costDO.getId())) {
                costMapper.insert(costDO);
                log.info("新增费用记录: iet={}, money={}", costInfo.getIet(), costInfo.getMoney());
            } else {
                // 更新
                costDO.setId(costInfo.getId());
                costMapper.updateById(costDO);
                log.info("更新费用记录: id={}", costInfo.getId());
            }
        }
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<String> batchAuditTransfer(BatchAuditTransferDTO dto) {
        try {
            List<String> ids = dto.getIds();
            Integer operation = dto.getOperation();
            if (operation != 0 && operation != 1) {
                return JsonVO.fail("操作参数错误，0-反审核，1-审核");
            } else if (ids == null || ids.isEmpty()) {
                return JsonVO.fail("请选择要" + (operation == 1 ? "审核" : "反审核") + "的调拨单");
            }

            // 1.检查调拨单状态并收集需要审核/反审核的数据
            List<SwapInfoDO> transferList = new ArrayList<>();
            String operationName = operation == 1 ? "审核" : "反审核";

            for (String id : ids) {
                // 1.1 获取对应的主表ID
                String pid = swapInfoMapper.getSwapById(id);
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

                SwapInfoDO swapInfoDO = swapInfoMapper.getTransferDetail(id);
                if (swapInfoDO == null) {
                    return JsonVO.fail("调拨单详情不存在，ID: " + id);
                }

                // 1.4 检查调出仓库和调入仓库是否相同
                if (swapInfoDO.getWarehouse().equals(swapInfoDO.getStorehouse())) {
                    return JsonVO.fail("调出仓库和调入仓库不能相同，ID: " + id);
                }

                // 1.5 检查调拨单的批次号是否存在
                if (!batchMapper.isBatchExist(swapInfoDO.getBatch())) {
                    return JsonVO.fail("调拨单批次号不存在，ID: " + id);
                }

                // 1.6 检查库存是否充足（审核时检查）
                if (operation == 1) {
                    // 检查批次库存
                    BigDecimal batchStock = batchMapper.getBatchStock(swapInfoDO.getBatch(),
                            swapInfoDO.getGoods(), swapInfoDO.getWarehouse());
                    if (batchStock == null || batchStock.compareTo(swapInfoDO.getNums()) < 0) {
                        return JsonVO.fail("调拨单批次库存不足，ID: " + id + "，需要: " + swapInfoDO.getNums() + "，实际: " + batchStock);
                    }

                    // 检查仓库总库存
                    if (!roomMapper.isNumsEnough(swapInfoDO.getGoods(),
                            swapInfoDO.getWarehouse(), swapInfoDO.getNums())) {
                        return JsonVO.fail("调拨单仓库库存不足，ID: " + id);
                    }
                }

                transferList.add(swapInfoDO);
            }

            // 2.执行批量审核/反审核操作
            int successCount = 0;
            for (SwapInfoDO transfer : transferList) {
                try {
                    if (operation == 1) {
                        // 审核操作：调拨库存
                        boolean auditSuccess = processTransferAudit(transfer);
                        if (auditSuccess) {
                            successCount++;
                        }
                    } else {
                        // 反审核操作：还原库存
                        boolean unAuditSuccess = processTransferUnaudit(transfer);
                        if (unAuditSuccess) {
                            successCount++;
                        }
                    }
                } catch (Exception e) {
                    log.error("处理调拨单失败，ID: {}", transfer.getId(), e);
                    throw new RuntimeException("处理调拨单失败，ID: " + transfer.getId() + "，错误: " + e.getMessage());
                }
            }

            // 3.更新调拨单状态
            List<String> validPidList = new ArrayList<>();
            for (SwapInfoDO transfer : transferList) {
                String pid = swapInfoMapper.getSwapById(transfer.getId());
                if (pid != null) {
                    validPidList.add(pid);
                }
            }

            if (!validPidList.isEmpty()) {
                int statusUpdateCount = swapMapper.auditBatchStatus(validPidList, operation);
                log.info("更新调拨单状态，操作: {}，更新数量: {}", operationName, statusUpdateCount);
            }

            if (successCount == 0) {
                return JsonVO.fail(operationName + "调拨单失败，未找到符合条件的记录");
            }

            // 4.记录操作日志
            log.info("批量{}调拨单成功，操作数量：{}，ID列表：{}", operationName, successCount, ids);

            return JsonVO.success(ids.toString());

        } catch (Exception e) {
            log.error("批量审核调拨单失败", e);
            return JsonVO.fail("批量审核调拨单失败: " + e.getMessage());
        }
    }

    /**
     * 处理调拨单审核（库存调拨）
     */
    private boolean processTransferAudit(SwapInfoDO transfer) {
        String batchNo = transfer.getBatch();
        String goodsId = transfer.getGoods();
        String fromWarehouse = transfer.getWarehouse();  // 调出仓库
        String toWarehouse = transfer.getStorehouse();   // 调入仓库
        BigDecimal nums = transfer.getNums();
        BigDecimal price = transfer.getPrice() != null ? transfer.getPrice() : BigDecimal.ZERO;
        String swapInfoId = transfer.getId();

        try {
            // 1.处理批次库存调拨
            boolean batchSuccess = processBatchTransfer(batchNo, goodsId, fromWarehouse, toWarehouse, nums, swapInfoId);
            if (!batchSuccess) {
                return false;
            }

            // 2.处理仓库总库存调拨
            boolean roomSuccess = processRoomTransfer(goodsId, fromWarehouse, toWarehouse, nums, swapInfoId, price);
            if (!roomSuccess) {
                // 回滚批次库存
                processBatchTransfer(batchNo, goodsId, toWarehouse, fromWarehouse, nums, swapInfoId);
                return false;
            }

            log.info("调拨单审核成功，批次: {}，商品: {}，从仓库{}调拨到仓库{}，数量: {}",
                    batchNo, goodsId, fromWarehouse, toWarehouse, nums);
            return true;

        } catch (Exception e) {
            log.error("调拨单审核处理异常", e);
            return false;
        }
    }

    /**
     * 处理批次库存调拨
     */
    private boolean processBatchTransfer(String batchNo, String goodsId, String fromWarehouse,
                                         String toWarehouse, BigDecimal nums, String swapInfoId) {
        // 1.减少源仓库的批次库存
        int updateSource = batchMapper.updateBatchStock(batchNo, goodsId, fromWarehouse, nums.negate());
        if (updateSource <= 0) {
            log.error("减少源仓库批次库存失败，批次: {}，商品: {}，仓库: {}", batchNo, goodsId, fromWarehouse);
            return false;
        }

        // 2.记录批次出库流水
        String fromBatchId = batchMapper.getBatchId(batchNo, goodsId, fromWarehouse);
        // 修改 classId 为自增（参考数据库）
        classId = String.valueOf(Integer.parseInt(classId) + 1);
        String uniqueId = String.valueOf((System.currentTimeMillis() % 1000000000L) + (long)(Math.random() * 10000L));
        BatchInfoDO batchInfoOut = createBatchInfo(uniqueId, fromBatchId, "swapOut", classId,
                swapInfoId, 0, nums);
        if (fromBatchId != null) {
            batchInfoMapper.insert(batchInfoOut);
        }

        // 3.检查目标仓库是否已存在该批次
        BigDecimal targetStock = batchMapper.getBatchStock(batchNo, goodsId, toWarehouse);
        if (targetStock != null) {
            // 目标仓库已存在该批次，增加库存
            int updateTarget = batchMapper.updateBatchStock(batchNo, goodsId, toWarehouse, nums);
            if (updateTarget <= 0) {
                log.error("增加目标仓库批次库存失败，批次: {}，商品: {}，仓库: {}", batchNo, goodsId, toWarehouse);
                // 回滚源仓库的库存减少
                batchMapper.updateBatchStock(batchNo, goodsId, fromWarehouse, nums);
                // 回滚批次出库流水
                batchInfoMapper.deleteById(batchInfoOut.getId());
                // 回滚所属类 classId
                classId = String.valueOf(Integer.parseInt(classId) - 1);
                return false;
            }
        } else {
            // 目标仓库不存在该批次，创建新的批次记录
            LocalDate time = batchMapper.getTimeByBatchNo(batchNo);
            String roomId = roomMapper.getRoomId(goodsId, toWarehouse);
            uniqueId = String.valueOf((System.currentTimeMillis() % 1000000000L) + (long)(Math.random() * 10000L));
            boolean createSuccess = batchMapper.createBatchInTargetWarehouse(uniqueId, roomId, toWarehouse, goodsId, batchNo, time, nums) > 0;
            if (!createSuccess) {
                log.error("在目标仓库创建批次失败，批次: {}，商品: {}，仓库: {}", batchNo, goodsId, toWarehouse);
                // 回滚源仓库的库存减少
                batchMapper.updateBatchStock(batchNo, goodsId, fromWarehouse, nums);
                // 回滚批次出库流水
                batchInfoMapper.deleteById(batchInfoOut.getId());
                // 回滚所属类 classId
                classId = String.valueOf(Integer.parseInt(classId) - 1);
                return false;
            }
        }

        // 4.记录批次入库流水
        String toBatchId = batchMapper.getBatchId(batchNo, goodsId, toWarehouse);
        // 修改 classId 为自增（参考数据库）
        classId = String.valueOf(Integer.parseInt(classId) + 1);
        uniqueId = String.valueOf((System.currentTimeMillis() % 1000000000L) + (long)(Math.random() * 10000L));
        BatchInfoDO batchInfoIn = createBatchInfo(uniqueId, toBatchId, "swapEnter", classId,
                swapInfoId, 1, nums);
        if (toBatchId != null) {

            batchInfoMapper.insert(batchInfoIn);
        }

        return true;
    }

    /**
     * 处理仓库总库存调拨
     */
    private boolean processRoomTransfer(String goodsId, String fromWarehouse, String toWarehouse,
                                        BigDecimal nums, String swapInfoId, BigDecimal price) {
        // 1.减少源仓库总库存
        int updateSourceRoom = roomMapper.updateRoomStock(goodsId, fromWarehouse, nums.negate());
        if (updateSourceRoom <= 0) {
            log.error("减少源仓库总库存失败，商品: {}，仓库: {}", goodsId, fromWarehouse);
            return false;
        }

        // 2.记录仓库出库流水
        String fromRoomId = roomMapper.getRoomId(goodsId, fromWarehouse);
        // 修改 classId 为自增（参考数据库，且非全局）
        classId = String.valueOf(Integer.parseInt(classId) + 1);
        String uniqueId = String.valueOf((System.currentTimeMillis() % 1000000000L) + (long)(Math.random() * 10000L));
        RoomInfoDO roomInfoOut = createRoomInfo(uniqueId, fromRoomId, "swapOut", classId,
                swapInfoId, LocalDateTime.now(), 0, price, nums);
        if (fromRoomId != null) {
            roomInfoMapper.insert(roomInfoOut);
        }

        // 3.检查目标仓库是否已存在该商品
        RoomDO targetRoom = roomMapper.getRoomByGoodsAndWarehouse(goodsId, toWarehouse);
        if (targetRoom != null) {
            // 目标仓库已存在该商品，增加库存
            int updateTargetRoom = roomMapper.updateRoomStock(goodsId, toWarehouse, nums);
            if (updateTargetRoom <= 0) {
                log.error("增加目标仓库总库存失败，商品: {}，仓库: {}", goodsId, toWarehouse);
                // 回滚源仓库的库存减少
                roomMapper.updateRoomStock(goodsId, fromWarehouse, nums);
                // 回滚仓库出库流水
                roomInfoMapper.deleteById(roomInfoOut.getId());
                // 回滚所属类 classId
                classId = String.valueOf(Integer.parseInt(classId) - 1);
                return false;
            }
        } else {
            // 目标仓库不存在该商品，创建新的库存记录
            uniqueId = String.valueOf((System.currentTimeMillis() % 1000000000L) + (long)(Math.random() * 10000L));
            String attr = swapInfoMapper.getAttrById(swapInfoId);
            boolean createRoomSuccess = roomMapper.createRoomInTargetWarehouse(uniqueId, goodsId, toWarehouse, attr, nums) > 0;
            if (!createRoomSuccess) {
                log.error("在目标仓库创建库存记录失败，商品: {}，仓库: {}", goodsId, toWarehouse);
                // 回滚源仓库的库存减少
                roomMapper.updateRoomStock(goodsId, fromWarehouse, nums);
                return false;
            }
        }

        // 4.记录仓库入库流水
        String toRoomId = roomMapper.getRoomId(goodsId, toWarehouse);
        uniqueId = String.valueOf((System.currentTimeMillis() % 1000000000L) + (long)(Math.random() * 10000L));
        // 修改 classId 为自增（参考数据库，且非全局）
        RoomInfoDO roomInfoIn = createRoomInfo(uniqueId, toRoomId, "swapEnter", "1",
                swapInfoId, LocalDateTime.now(), 1, price, nums);
        if (toRoomId != null) {
            roomInfoMapper.insert(roomInfoIn);
        }

        return true;
    }

    /**
     * 处理调拨单反审核（库存还原）
     */
    private boolean processTransferUnaudit(SwapInfoDO transfer) {
        String batchNo = transfer.getBatch();
        String goodsId = transfer.getGoods();
        String fromWarehouse = transfer.getWarehouse();  // 原调出仓库（现在要加回去）
        String toWarehouse = transfer.getStorehouse();   // 原调入仓库（现在要减回去）
        BigDecimal nums = transfer.getNums();
        BigDecimal price = transfer.getPrice() != null ? transfer.getPrice() : BigDecimal.ZERO;
        String swapInfoId = transfer.getId();

        try {
            // 1.处理批次库存还原（反向调拨）
            boolean batchSuccess = processBatchTransfer(batchNo, goodsId, toWarehouse, fromWarehouse, nums, swapInfoId);
            if (!batchSuccess) {
                return false;
            }

            // 2.处理仓库总库存还原（反向调拨）
            boolean roomSuccess = processRoomTransfer(goodsId, toWarehouse, fromWarehouse, nums, swapInfoId, price);
            if (!roomSuccess) {
                // 回滚批次库存
                processBatchTransfer(batchNo, goodsId, fromWarehouse, toWarehouse, nums, swapInfoId);
                return false;
            }

            log.info("调拨单反审核成功，批次: {}，商品: {}，从仓库{}还原到仓库{}，数量: {}",
                    batchNo, goodsId, toWarehouse, fromWarehouse, nums);
            return true;

        } catch (Exception e) {
            log.error("调拨单反审核处理异常", e);
            return false;
        }
    }

    /**
     * 创建批次流水记录
     */
    private BatchInfoDO createBatchInfo(String id, String pid, String type, String classId,
                                        String info, Integer direction, BigDecimal nums) {
        BatchInfoDO batchInfo = new BatchInfoDO();
        batchInfo.setId(id);
        batchInfo.setPid(pid);
        batchInfo.setType(type);
        batchInfo.setCls(classId);
        batchInfo.setInfo(info);
        batchInfo.setDirection(direction);
        batchInfo.setNums(nums);
        return batchInfo;
    }

    /**
     * 创建仓库流水记录
     */
    private RoomInfoDO createRoomInfo(String id, String pid, String type, String classId,
                                      String info, LocalDateTime time, Integer direction, BigDecimal price, BigDecimal nums) {
        RoomInfoDO roomInfo = new RoomInfoDO();
        roomInfo.setId(id);
        roomInfo.setPid(pid);
        roomInfo.setType(type);
        roomInfo.setCls(classId);
        roomInfo.setInfo(info);
        roomInfo.setTime(time);
        roomInfo.setDirection(direction);
        roomInfo.setPrice(price);
        roomInfo.setNums(nums);
        return roomInfo;
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
            List<String> cannotDeleteIds = new ArrayList<>();
            List<String> validPidList = new ArrayList<>();

            for (Integer id : ids) {
                String pid = swapInfoMapper.getSwapById(id.toString());
                if (pid == null) {
                    return JsonVO.fail("调拨单不存在，ID: " + id);
                }

                Integer status = swapMapper.getStatusById(pid);
                if (status == null) {
                    return JsonVO.fail("调拨单状态异常，ID: " + id);
                }

                if (status != 0) {
                    cannotDeleteIds.add(id.toString());
                } else {
                    validPidList.add(pid);
                }
            }

            // 2.如果有已审核的调拨单，返回错误
            if (!cannotDeleteIds.isEmpty()) {
                return JsonVO.fail("只能删除草稿状态的调拨单，以下调拨单已审核不可删除: " + String.join(", ", cannotDeleteIds));
            }

            // 3.如果没有可删除的调拨单，直接返回

            // 4.先删除对应的单据费用 (is_cost表)
            int deleteCostCount = 0;
            for (String pid : validPidList) {
                int count = costMapper.deleteByTransferId(pid);
                deleteCostCount += count;
                log.info("删除调拨单 {} 对应的费用记录 {} 条", pid, count);
            }

            // 5.删除 swap_info 表中的记录
            int deleteInfoCount = swapInfoMapper.deleteBatchIds(ids);

            // 6.删除 swap 表中的记录
            int deleteMainCount = swapMapper.deleteBatchIds(validPidList);

            log.info("删除调拨单成功: 删除详情记录 {} 条, 删除主表记录 {} 条, 删除费用记录 {} 条",
                    deleteInfoCount, deleteMainCount, deleteCostCount);

            if (deleteInfoCount == 0) {
                return JsonVO.fail("删除调拨单失败");
            }

            return JsonVO.success("成功删除 " + deleteInfoCount + " 条调拨单记录");

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
