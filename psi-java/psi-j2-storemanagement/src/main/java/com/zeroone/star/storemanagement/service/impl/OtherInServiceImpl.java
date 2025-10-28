package com.zeroone.star.storemanagement.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.j2.store.CostDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDetailDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListInfoDTO;
import com.zeroone.star.storemanagement.entity.*;
import com.zeroone.star.storemanagement.mapper.*;
import com.zeroone.star.storemanagement.service.IOtherInService;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

@Service
public class OtherInServiceImpl  implements IOtherInService {

    @Autowired
    OtherInMapper otherInMapper;

    @Autowired
    OtherInInfoMapper otherInInfoMapper;

    @Autowired
    CostMapper costMapper;

    @Autowired
    LogMapper logMapper;

    @Autowired
    RecordMapper recordMapper;

    @Resource
    UserHolder userHolder;

    @Override
    @Transactional
    public void updateOtherInList(OtherInListDetailDTO otherInListDetailDTO) {
        //判断入库单是否存在
        Integer examine = otherInMapper.getExamineById(otherInListDetailDTO.getId());
        if(examine==null){
            throw new RuntimeException("入库单不存在");
        }
        if(examine==1){
            throw new RuntimeException("入库单已审核,无法修改");
        }
        //更新入库单
        EntryDO entry = new EntryDO();
        BeanUtils.copyProperties(otherInListDetailDTO,entry);
        otherInMapper.update(entry);


        //获取入库单详情列表
        List<OtherInListInfoDTO> otherInListInfoDTOList = otherInListDetailDTO.getOtherInListInfoDTOList();
        //判断是否为空
        if(otherInListInfoDTOList==null||otherInListInfoDTOList.isEmpty()){
            throw new RuntimeException("入库单详情列表不能为空");
        }
        //删除原先的入库单详情数据
        otherInInfoMapper.deleteByPid(otherInListDetailDTO.getId());
        //插入新的入库单详情数据
        Integer maxId = otherInInfoMapper.getMaxId();
        if(maxId==null){
          maxId=0;
        }
        List<EntryInfoDO> entryInfoList = new ArrayList<>();
        for(OtherInListInfoDTO otherInListInfoDTO:otherInListInfoDTOList){
            EntryInfoDO entryInfo = new EntryInfoDO();
            BeanUtils.copyProperties(otherInListInfoDTO,entryInfo);
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
        if(maxId==null){
            maxId=0;
        }
        List<CostDO> costList = new ArrayList<>();
        for(CostDTO costDTO:costDTOList){
            CostDO cost = new CostDO();
            BeanUtils.copyProperties(costDTO,cost);
            cost.setCls(otherInListDetailDTO.getId());
            cost.setType("entry");
            cost.setTime(entry.getTime());
            cost.setSettle(BigDecimal.valueOf(0.0000));
            cost.setState(0);
            cost.setId(String.valueOf(++maxId));
            costList.add(cost);
        }
        //使用mp批量插入costdo TODO
        //costMapper.insert(costList);

        //更新操作日志表和单据记录表
        UserDTO user=null;
        try {
            user = userHolder.getCurrentUser();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        LogDO log = new LogDO();
        log.setUser(user.getUsername());
        log.setTime(entry.getTime());
        log.setInfo("更新其他入库单"+"["+otherInListDetailDTO.getNumber()+"]");
        logMapper.insert(log);
        RecordDO record = new RecordDO();
        record.setUser(user.getUsername());
        record.setType("entry");
        record.setSource(otherInListDetailDTO.getId());
        record.setTime(entry.getTime());
        record.setInfo("更新单据");
        recordMapper.insert(record);
    }

    @Override
    public void examine(List<Integer> ids) {
        //查询id在ids中的入库单总数
        List<Integer> exmineStatusList = otherInMapper.getExamineByIds(ids);
        //判断入库单总数是否等于ids的长度
        if(exmineStatusList.size()!=ids.size()){
            throw new RuntimeException("有入库单不存在");
        }
        int status = exmineStatusList.get(0);
        otherInMapper.updateExamine(ids,status^1);
    }

    @Override
    public void check(List<Integer> ids) {
        List< Integer> checkStatusList = otherInMapper.getCheckByIds(ids);
        if(checkStatusList.size()!=ids.size()){
            throw new RuntimeException("有入库单不存在");
        }
        int status = checkStatusList.get(0);
        otherInMapper.updateCheck(ids,status^1);
    }
}
