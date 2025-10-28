package com.zeroone.star.storemanagement.service.impl;

import com.alibaba.cloud.commons.lang.StringUtils;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.dto.j2.store.CostDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListAddDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDetailDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListInfoDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.entity.CostDO;
import com.zeroone.star.storemanagement.entity.EntryDO;
import com.zeroone.star.storemanagement.entity.EntryInfoDO;
import com.zeroone.star.storemanagement.mapper.CostMapper;
import com.zeroone.star.storemanagement.mapper.OtherInInfoMapper;
import com.zeroone.star.storemanagement.mapper.OtherInMapper;
import com.zeroone.star.storemanagement.service.IOtherInService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

@Service
@Slf4j
public class OtherInServiceImpl extends ServiceImpl<OtherInMapper, EntryDO> implements IOtherInService {

    @Autowired
    OtherInMapper otherInMapper;

    @Autowired
    OtherInInfoMapper otherInInfoMapper;

    @Autowired
    CostMapper costMapper;

//    @Autowired
//    LogMapper logMapper;
//
//    @Autowired
//    RecordMapper recordMapper;
//
//    @Resource
//    UserHolder userHolder;

    @Autowired
    MsEntryMapper ms;

    @Override
    @Transactional
    public void updateOtherInList(OtherInListDetailDTO otherInListDetailDTO) {
        //判断入库单是否存在
        Integer examine = otherInMapper.getExamineById(otherInListDetailDTO.getId());
        if (examine == null) {
            throw new RuntimeException("入库单不存在");
        }
        if (examine == 1) {
            throw new RuntimeException("入库单已审核,无法修改");
        }
        //更新入库单
        EntryDO entry = new EntryDO();
        BeanUtils.copyProperties(otherInListDetailDTO, entry);
        otherInMapper.update(entry);


        //获取入库单详情列表
        List<OtherInListInfoDTO> otherInListInfoDTOList = otherInListDetailDTO.getOtherInListInfoDTOList();
        //判断是否为空
        if (otherInListInfoDTOList == null || otherInListInfoDTOList.isEmpty()) {
            throw new RuntimeException("入库单详情列表不能为空");
        }
        //删除原先的入库单详情数据
        otherInInfoMapper.deleteByPid(otherInListDetailDTO.getId());
        //插入新的入库单详情数据
        Integer maxId = costMapper.getMaxId();
        maxId = maxId == null ? 0 : maxId;
        List<EntryInfoDO> entryInfoList = new ArrayList<>();
        for (OtherInListInfoDTO otherInListInfoDTO : otherInListInfoDTOList) {
            EntryInfoDO entryInfo = new EntryInfoDO();
            BeanUtils.copyProperties(otherInListInfoDTO, entryInfo);
            entryInfo.setPid(otherInListDetailDTO.getId());
            entryInfo.setId((++maxId).toString());
            entryInfoList.add(entryInfo);
        }
        otherInInfoMapper.insertBatch(entryInfoList);


        //获取单据花费列表
        List<CostDTO> costDTOList = otherInListDetailDTO.getCostDTOList();
        //删除原先的单据花费数据
        costMapper.deleteBycls(otherInListDetailDTO.getId());
        //插入新的花费单据数据
        maxId = costMapper.getMaxId();
        maxId = maxId == null ? 0 : maxId;
        List<CostDO> costList = new ArrayList<>();
        for (CostDTO costDTO : costDTOList) {
            CostDO cost = new CostDO();
            BeanUtils.copyProperties(costDTO, cost);
            cost.setCls(otherInListDetailDTO.getId());
            cost.setType("entry");
            cost.setTime(entry.getTime());
            cost.setSettle(BigDecimal.valueOf(0.0000));
            cost.setState(0);
            cost.setId((++maxId).toString());
            costList.add(cost);
        }
        costMapper.insertBatch(costList);

//        //更新操作日志表和单据记录表
//        UserDTO user=null;
//        try {
//            user = userHolder.getCurrentUser();
//        } catch (Exception e) {
//            throw new RuntimeException(e);
//        }
//        LogDO log = new LogDO();
//        log.setUser(user.getUsername());
//        log.setTime(entry.getTime());
//        log.setInfo("更新其他入库单"+"["+otherInListDetailDTO.getNumber()+"]");
//        logMapper.insert(log);
//        RecordDO record = new RecordDO();
//        record.setUser(user.getUsername());
//        record.setType("entry");
//        record.setSource(otherInListDetailDTO.getId());
//        record.setTime(entry.getTime());
//        record.setInfo("更新单据");
//        recordMapper.insert(record);
    }

    @Override
    public void examine(List<Integer> ids) {
        //查询id在ids中的入库单总数
        List<Integer> exmineStatusList = otherInMapper.getExamineByIds(ids);
        //判断入库单总数是否等于ids的长度
        if (exmineStatusList.size() != ids.size()) {
            throw new RuntimeException("有入库单不存在");
        }
        int status = exmineStatusList.get(0);
        otherInMapper.updateExamine(ids, status ^ 1);
    }

    @Override
    public void check(List<Integer> ids) {
        List<Integer> checkStatusList = otherInMapper.getCheckByIds(ids);
        if (checkStatusList.size() != ids.size()) {
            throw new RuntimeException("有入库单不存在");
        }
        int status = checkStatusList.get(0);
        otherInMapper.updateCheck(ids, status ^ 1);
    }

    @Override
    @Transactional
    public OtherInListDetailDTO getOtherInListDetail(String id) {
        // TODO 单个查询操作
        // 1.检查用户权限 权限校验可以定义AOP切面实现
        if (!checkPermission()) {
            log.info("用户无操作权限");
        }
        // 2.判断入库单是否存在
        EntryDO exist = otherInMapper.selectById(id);
        if (exist == null) {
            log.info("入库单不存在");
        }
        // 3.查询入库单详细
        OtherInListDetailDTO dto = ms.entryToOtherInListDetailDTO(exist);
        // 4.记录操作日志
        logOperation(dto.getId(), "查询入库单详细");
        return dto;
    }

    @Override
    @Transactional
    public JsonVO<String> saveOtherInList(OtherInListAddDTO dto) {
        // TODO 新增操作
        // 1.参数校验
        if (validate(dto) == null) { // 没有返回错误信息即通过校验
            return JsonVO.fail("参数不合法");
        }
        // 2.检查用户权限
        if (!checkPermission()) {
            return JsonVO.fail("用户无操作权限");
        }
        // 3.新增入库单
        EntryDO entryDO = ms.addDtoToEntry(dto);
        otherInMapper.insert(entryDO);
        // 4.记录操作日志
        logOperation(String.valueOf(entryDO.getId()), "新增入库单");
        return JsonVO.success("新增入库单成功");
    }


    @Override
    @Transactional
    public List<String> removeOtherInList(List<Integer> ids) {
        // 用于记录成功删除的入库单编号
        List<String> deletedList = new ArrayList<>();

        // 1.判断入库单是否存在
        List<EntryDO> existingLists = otherInMapper.selectBatchIds(ids);
        if (existingLists.size() != ids.size()) {
            log.info("部分入库单不存在");
            return deletedList;
        }

        // 2.检查用户权限
        if (!checkPermission()) {
            log.info("用户无操作权限");
            return deletedList;
        }

        // 3.判断入库单是否审核并删除未审核的
        int count = 0;
        for (EntryDO entryDO : existingLists) {
            if (entryDO.getExamine() == 1) {
                log.info("入库单已审核，不能删除，单号: {}", entryDO.getNumber());
            } else {
                // 4.删除入库单
                otherInInfoMapper.deleteById(entryDO.getId());
                count++;
                // 记录成功删除的入库单编号
                deletedList.add(entryDO.getNumber());
            }
        }

        // 5.记录删除结果
        if (count != ids.size()) {
            log.info("删除入库单完成，预期删除{}条，实际删除{}条", ids.size(), count);
        } else {
            log.info("成功删除{}条入库单", count);
        }

        return deletedList;
    }

    /**
     * 数据合法性校验（带错误信息）
     */
    private String validate(OtherInListAddDTO dto) {
        if (dto == null) {
            return "参数不能为空";
        }

        // 必填字段校验
        if (dto.getTime() == null) {
            return "单据日期不能为空";
        }
        if (StringUtils.isBlank(dto.getNumber())) {
            return "单据编号不能为空";
        }
        if (dto.getType() == null) {
            return "单据类型不能为空";
        }
        if (dto.getTotal() == null) {
            return "单据成本不能为空";
        }
        if (dto.getCost() == null) {
            return "单据费用不能为空";
        }
        if (dto.getExamine() == null) {
            return "审核状态不能为空";
        }
        if (dto.getCse() == null) {
            return "费用状态不能为空";
        }
        if (dto.getCheck() == null) {
            return "核对状态不能为空";
        }
        if (dto.getUser() == null) {
            return "制单人不能为空";
        }

        // 数值范围校验
        if (dto.getTotal().compareTo(BigDecimal.ZERO) < 0) {
            return "单据成本不能为负数";
        }
        if (dto.getCost().compareTo(BigDecimal.ZERO) < 0) {
            return "单据费用不能为负数";
        }
        if (dto.getType() != 0 && dto.getType() != 1) {
            return "单据类型只能是0(其它入库单)或1(盘盈单)";
        }
        if (dto.getExamine() != 0 && dto.getExamine() != 1) {
            return "审核状态只能是0(未审核)或1(已审核)";
        }
        if (dto.getCse() < 0 || dto.getCse() > 3) {
            return "费用状态范围错误";
        }
        if (dto.getCheck() != 0 && dto.getCheck() != 1) {
            return "核对状态只能是0(未核对)或1(已核对)";
        }

        // 业务逻辑校验
        if (dto.getTime().isAfter(LocalDateTime.now())) {
            return "单据日期不能晚于当前时间";
        }

        OtherInListInfoDTO otherInListInfoDTO = (OtherInListInfoDTO) dto.getOtherInListInfoDTOList();
        // 关联数据校验
        if (validateOtherInListInfo(otherInListInfoDTO) == null) {
            return "入库单详细信息不能为空";
        }
        if (validateCost((CostDTO) dto.getCostDTOList()) == null) {
            return "单据费用列表不能为空";
        }

        return null; // 返回null表示校验通过
    }

    /**
     * 入库单详细信息校验（带错误信息）
     */
    private String validateOtherInListInfo(OtherInListInfoDTO info) {
        if (info == null) {
            return "入库单详细信息不能为空";
        }

        // 必填字段校验
//        if (StringUtils.isBlank(info.getName())) {
//            return "商品名称不能为空";
//        }
//        if (StringUtils.isBlank(info.getNumber())) {
//            return "商品编号不能为空";
//        }
        if (Integer.parseInt(info.getGoods()) <= 0) {
            return "所属商品ID无效";
        }

        if (StringUtils.isBlank(info.getUnit())) {
            return "单位不能为空";
        }
        if (Integer.parseInt(info.getWarehouse()) <= 0) {
            return "仓库ID无效";
        }

        // 数值范围校验
        if (info.getPrice().compareTo(BigDecimal.ZERO) < 0) {
            return "商品成本不能为负数";
        }
        if (info.getNums().compareTo(BigDecimal.ZERO) <= 0) {
            return "商品数量必须大于0";
        }
        if (info.getTotal().compareTo(BigDecimal.ZERO) < 0) {
            return "商品总成本不能为负数";
        }

        // 业务逻辑校验
        if (info.getMfd() != null && info.getMfd().isAfter(LocalDateTime.now())) {
            return "生产日期不能晚于当前时间";
        }

        // 计算一致性校验
        BigDecimal expectedTotal = info.getPrice().multiply(info.getNums());
        if (info.getTotal().subtract(expectedTotal).abs().compareTo(BigDecimal.valueOf(0.01)) > 0) {
            return String.format("商品总成本计算错误，应为%.4f", expectedTotal);
        }

        return null; // 返回null表示校验通过
    }

    /**
     * 费用信息校验
     */
    private String validateCost(CostDTO cost) {
        if (cost == null) {
            return "费用信息不能为空";
        }
        if (cost.getMoney().compareTo(BigDecimal.ZERO) < 0) {
            return "费用金额不能为负数";
        }
        return null;
    }

    private boolean checkPermission() {
        return true;
    }

    /**
     * 记录操作日志
     */
    private void logOperation(String transferId, String operation) {
        // TODO: 实现操作日志记录
        log.info("操作日志：入库单ID: {}, 操作: {}", transferId, operation);
    }
}
