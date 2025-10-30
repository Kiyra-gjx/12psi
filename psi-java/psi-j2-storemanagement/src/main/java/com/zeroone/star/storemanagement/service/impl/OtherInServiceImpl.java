package com.zeroone.star.storemanagement.service.impl;

import cn.hutool.Hutool;
import cn.hutool.core.lang.Snowflake;
import cn.hutool.core.util.IdUtil;
import com.alibaba.cloud.commons.lang.StringUtils;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.j2.store.CostDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListAddDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDetailDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListInfoDTO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.*;
import com.zeroone.star.project.query.j2.store.OtherInQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.entity.*;
import com.zeroone.star.storemanagement.mapper.*;
import com.zeroone.star.storemanagement.entity.CostDO;
import com.zeroone.star.storemanagement.entity.EntryDO;
import com.zeroone.star.storemanagement.entity.EntryInfoDO;
import com.zeroone.star.storemanagement.mapper.CostMapper;
import com.zeroone.star.storemanagement.mapper.OtherInInfoMapper;
import com.zeroone.star.storemanagement.mapper.OtherInListMapper;
import com.zeroone.star.storemanagement.mapper.OtherInMapper;
import com.zeroone.star.storemanagement.service.IOtherInService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import javax.annotation.Resource;

import javax.annotation.Resource;
import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

@Service
@Slf4j
public class OtherInServiceImpl extends ServiceImpl<OtherInMapper, EntryDO>  implements IOtherInService {

    @Resource
    OtherInMapper otherInMapper;

    @Resource
    OtherInInfoMapper otherInInfoMapper;

    @Resource
    CostMapper costMapper;

    @Resource
    LogMapper logMapper;

    @Resource
    RecordMapper recordMapper;

    @Resource
    RoomMapper roomMapper;

    @Resource
    RoomInfoMapper roomInfoMapper;

    @Resource
    SummaryMapper summaryMapper;

    @Resource
    ServeMapper serveMapper;

    @Resource
    ServeInfoMapper serveInfoMapper;
    
    @Resource
    OtherInListMapper otherInListMapper;

    @Resource
    MsEntryMapper ms;

    //雪花算法
    private final Snowflake snowflake = IdUtil.getSnowflake();

    @Override
    @Transactional
    public void updateOtherInList(OtherInListDetailDTO otherInListDetailDTO) {
        //1.判断入库单是否存在
        Integer examine = otherInMapper.getExamineById(otherInListDetailDTO.getId());
        if (examine == null) {
            throw new RuntimeException("入库单不存在");
        }
        if (examine == 1) {
            throw new RuntimeException("入库单已审核,无法修改");
        }
        //2.更新入库单
        EntryDO entry = new EntryDO();
        BeanUtils.copyProperties(otherInListDetailDTO, entry);
        otherInMapper.update(entry);


        //3.获取入库单详情列表
        List<OtherInListDetailInfoDTO> otherInListInfoDTOList = otherInListDetailDTO.getOtherInListInfoDTOList();
        //判断是否为空
        if (otherInListInfoDTOList == null || otherInListInfoDTOList.isEmpty()) {
            throw new RuntimeException("入库单详情列表不能为空");
        }
        //4.删除原先的入库单详情数据
        otherInInfoMapper.deleteByPid(otherInListDetailDTO.getId());
        //5.插入新的入库单详情数据
        List<EntryInfoDO> entryInfoList = new ArrayList<>();
        for (OtherInListDetailInfoDTO otherInListInfoDTO : otherInListInfoDTOList) {
            EntryInfoDO entryInfo = new EntryInfoDO();
            BeanUtils.copyProperties(otherInListInfoDTO, entryInfo);
            entryInfo.setPid(otherInListDetailDTO.getId());
            entryInfoList.add(entryInfo);
            entryInfo.setId(snowflake.nextIdStr());
        }
        otherInInfoMapper.insertBatch(entryInfoList);


        //6.获取单据花费列表
        List<CostDTO> costDTOList = otherInListDetailDTO.getCostDTOList();
        //7.删除原先的单据花费数据
        costMapper.deleteBycls(otherInListDetailDTO.getId());
        //8.插入新的花费单据数据
        List<CostDO> costList = new ArrayList<>();
        for (CostDTO costDTO : costDTOList) {
            CostDO cost = new CostDO();
            BeanUtils.copyProperties(costDTO, cost);
            cost.setCls(otherInListDetailDTO.getId());
            cost.setType("entry");
            cost.setTime(entry.getTime());
            cost.setSettle(BigDecimal.valueOf(0.0000));
            cost.setState(0);
            cost.setId(snowflake.nextIdStr());
            costList.add(cost);
        }
        costMapper.insertBatch(costList);

        //9.更新操作日志表和单据记录表
        LogDO log = new LogDO();
        log.setUser("admin");
        log.setTime(entry.getTime());
        log.setInfo("更新其他入库单"+"["+otherInListDetailDTO.getNumber()+"]");
        log.setId(snowflake.nextIdStr());
        logMapper.insert(log);
        RecordDO record = new RecordDO();
        record.setUser("admin");
        record.setType("entry");
        record.setSource(otherInListDetailDTO.getId());
        record.setTime(entry.getTime());
        record.setInfo("更新单据");
        record.setId(snowflake.nextIdStr());
        recordMapper.insert(record);
    }

    @Override
    @Transactional
    public void examine(List<Integer> ids) {
        //1.判断入库单是否存在
        //查询id在ids中的入库单总数
        List<Integer> exmineStatusList = otherInMapper.getExamineByIds(ids);
        //判断入库单总数是否等于ids的长度
        if (exmineStatusList.size() != ids.size()) {
            throw new RuntimeException("有入库单不存在");
        }
        int status = exmineStatusList.get(0)^1;
        //更新表：summary,serve,serve_info,room,room_info,log,record
        //查询表: entry,entry_info


        //获取所有id对应的entry表和entry_info表信息
        List<EntryDO> entryList = otherInMapper.getByIds(ids);
        Map<String, EntryDO> entryMap = entryList.stream()
                .collect(Collectors.toMap(EntryDO::getId, entryDO -> entryDO));
        List<EntryInfoDO> entryInfoList = otherInInfoMapper.getByPids(ids);
        //2.审核入库单
        if(status==1) {
            for (EntryInfoDO entryInfoDO : entryInfoList) {
                //3.审核服务
                if (entryInfoDO.getWarehouse().equals("0")) {
                    //4.获取服务，若服务不存在，则插入，否则更新
                    ServeDO serveDO = serveMapper.getByGoods(entryInfoDO.getGoods());
                    if (serveDO == null) {
                        serveDO = new ServeDO();
                        serveDO.setId(snowflake.nextIdStr());
                        serveDO.setGoods(entryInfoDO.getGoods());
                        serveDO.setAttr(entryInfoDO.getAttr());
                        serveDO.setNums(entryInfoDO.getNums());
                        serveMapper.insert(serveDO);
                    } else {
                        serveDO.setNums(serveDO.getNums().add(entryInfoDO.getNums()));
                        serveMapper.updateById(serveDO);
                    }
                    //5.插入服务详细信息
                    ServeInfoDO serveInfoDO = new ServeInfoDO();
                    serveInfoDO.setId(snowflake.nextIdStr());
                    serveInfoDO.setPid(serveDO.getId());
                    serveInfoDO.setType("entry");
                    serveInfoDO.setCls(entryInfoDO.getPid());
                    serveInfoDO.setInfo(entryInfoDO.getId());
                    serveInfoDO.setTime(entryMap.get(entryInfoDO.getPid()).getTime());
                    serveInfoDO.setPrice(entryInfoDO.getPrice());
                    serveInfoDO.setNums(entryInfoDO.getNums());
                    serveInfoMapper.insert(serveInfoDO);
                } else {//6.审核库存
                    //7.获取库存，若库存不存在，则插入，否则更新
                    RoomDO roomDO = roomMapper.getByGoods(entryInfoDO.getGoods());
                    if (roomDO == null) {
                        roomDO = new RoomDO();
                        roomDO.setId(snowflake.nextIdStr());
                        roomDO.setWarehouse(entryInfoDO.getWarehouse());
                        roomDO.setGoods(entryInfoDO.getGoods());
                        roomDO.setAttr(entryInfoDO.getAttr());
                        roomDO.setNums(entryInfoDO.getNums());
                        roomMapper.insert(roomDO);
                    } else {
                        roomDO.setNums(roomDO.getNums().add(entryInfoDO.getNums()));
                        roomMapper.updateById(roomDO);
                    }
                    //8.插入库存详细信息
                    RoomInfoDO roomInfoDO = new RoomInfoDO();
                    roomInfoDO.setId(snowflake.nextIdStr());
                    roomInfoDO.setPid(roomDO.getId());
                    roomInfoDO.setType("entry");
                    roomInfoDO.setCls(entryInfoDO.getPid());
                    roomInfoDO.setInfo(entryInfoDO.getId());
                    roomInfoDO.setTime(entryMap.get(entryInfoDO.getPid()).getTime());
                    roomInfoDO.setDirection(1);
                    roomInfoDO.setPrice(entryInfoDO.getPrice());
                    roomInfoDO.setNums(entryInfoDO.getNums());
                    roomInfoMapper.insert(roomInfoDO);
                    //9.插入收发统计信息
                    SummaryDO summaryDO = new SummaryDO();
                    BeanUtils.copyProperties(roomInfoDO, summaryDO);
                    summaryDO.setId(snowflake.nextIdStr());
                    summaryDO.setPid(summaryDO.getId());
                    summaryDO.setGoods(roomDO.getGoods());
                    summaryDO.setAttr(roomDO.getAttr());
                    summaryDO.setWarehouse(roomDO.getWarehouse());
                    summaryDO.setBatch(entryInfoDO.getBatch());
                    summaryDO.setMfd(entryInfoDO.getMfd());
                    summaryDO.setSerial(entryInfoDO.getSerial());
                    summaryDO.setUct(summaryDO.getPrice());
                    summaryDO.setBct(summaryDO.getPrice().multiply(summaryDO.getNums()));
                    summaryDO.setExist("[" + roomDO.getNums() +","+ roomDO.getNums() +","+ roomDO.getNums() +","+ roomDO.getNums() + "]");
                    int temp = roomDO.getNums().multiply(roomInfoDO.getPrice()).intValue();
                    summaryDO.setBalance("[" + temp+"," + temp +","+ temp +","+ temp + "]");
                    summaryDO.setHandle("0.0000");
                    summaryMapper.insert(summaryDO);
                }
            }
        }else{//10.反审核入库单
            for(EntryInfoDO entryInfoDO : entryInfoList){
                //11.获取服务并更新
                if(entryInfoDO.getWarehouse().equals("0")){
                    ServeDO serveDO = serveMapper.getByGoods(entryInfoDO.getGoods());
                    if(serveDO.getNums().equals(entryInfoDO.getNums())){
                        serveMapper.deleteById(serveDO.getId());
                    }else{
                        serveDO.setNums(serveDO.getNums().subtract(entryInfoDO.getNums()));
                        serveMapper.updateById(serveDO);
                    }
                    //12.删除服务详细信息
                    serveInfoMapper.deleteByInfo(entryInfoDO.getId());
                }else{
                    //13.获取库存并更新
                    RoomDO roomDO = roomMapper.getByGoods(entryInfoDO.getGoods());
                    if(roomDO.getNums().equals(entryInfoDO.getNums())){
                        roomMapper.deleteById(roomDO.getId());
                    }else{
                        roomDO.setNums(roomDO.getNums().subtract(entryInfoDO.getNums()));
                        roomMapper.updateById(roomDO);
                    }
                    //14.删除库存详细信息
                    roomInfoMapper.deleteByInfo(entryInfoDO.getId());
                    //15.删除收发统计信息
                    summaryMapper.deleteByInfo(entryInfoDO.getId());
                }
            }
        }
        //16.更新审核状态
        otherInMapper.updateExamine(ids,status);
        //17.更新日志表和单据记录表
        List<LogDO> logList = new ArrayList<>();
        for(EntryDO entry : entryList){
            LogDO log = new LogDO();
            log.setId(snowflake.nextIdStr());
            log.setUser("admin");
            log.setTime(entry.getTime());
            log.setInfo("审核其他入库单"+"["+entry.getNumber()+"]");
            logList.add(log);
        }
        logMapper.insertBatch(logList);
        List<RecordDO> recordList = new ArrayList<>();
        for(EntryDO entry : entryList){
            RecordDO record = new RecordDO();
            record.setId(snowflake.nextIdStr());
            record.setUser("admin");
            record.setType("entry");
            record.setSource(entry.getId());
            record.setTime(entry.getTime());
            record.setInfo("审核单据");
            recordList.add(record);
        }
        recordMapper.insertBatch(recordList);
    }

    @Override
    @Transactional
    public void check(List<Integer> ids) {
        //1.判断入库单是否存在并获取核对状态
        List<Integer> checkStatusList = otherInMapper.getCheckByIds(ids);
        if (checkStatusList.size() != ids.size()) {
            throw new RuntimeException("有入库单不存在");
        }
        int status = checkStatusList.get(0);
        //2.更新核对状态
        otherInMapper.updateCheck(ids, status ^ 1);

        //3.更新日志表和单据记录表
        List<EntryDO> entryList = otherInMapper.getByIds(ids);
        List<LogDO> logList = new ArrayList<>();
        for(EntryDO entry : entryList){
            LogDO log = new LogDO();
            log.setId(snowflake.nextIdStr());
            log.setUser("admin");
            log.setTime(entry.getTime());
            log.setInfo("核对其他入库单"+"["+entry.getNumber()+"]");
            logList.add(log);
        }
        logMapper.insertBatch(logList);
        List<RecordDO> recordList = new ArrayList<>();
        for(EntryDO entry : entryList){
            RecordDO record = new RecordDO();
            record.setId(snowflake.nextIdStr());
            record.setUser("admin");
            record.setType("entry");
            record.setSource(entry.getId());
            record.setTime(entry.getTime());
            record.setInfo("核对单据");
            recordList.add(record);
        }
        recordMapper.insertBatch(recordList);
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
        EntryDO exist =  otherInMapper.selectById(id);
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
     * 获取其他入库单列表（条件查询+分页）
     * @param query 查询参数对象
     * @return 包含分页数据的JsonVO对象
     */
    @Override
    public JsonVO<PageDTO<OtherInListDTO>> getOtherInList(OtherInQuery query) {
        // 创建分页对象
        Page<OtherInListDTO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        // 调用mapper进行分页查询
        Page<OtherInListDTO> result = otherInListMapper.selectOtherInListPage(page, query);
        // 构建返回的分页数据对象
        PageDTO<OtherInListDTO> pageDTO = new PageDTO<>();
        pageDTO.setTotal(result.getTotal());
        pageDTO.setRows(result.getRecords());
        pageDTO.setPageSize(result.getSize());
        // 返回成功响应
        return JsonVO.success(pageDTO);
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
