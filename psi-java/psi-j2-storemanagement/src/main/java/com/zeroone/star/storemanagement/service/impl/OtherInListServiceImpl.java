package com.zeroone.star.storemanagement.service.impl;

import com.zeroone.star.project.dto.j2.store.CostDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDetailDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListInfoDTO;
import com.zeroone.star.storemanagement.entity.CostDO;
import com.zeroone.star.storemanagement.entity.EntryDO;
import com.zeroone.star.storemanagement.entity.EntryInfoDO;
import com.zeroone.star.storemanagement.mapper.CostMapper;
import com.zeroone.star.storemanagement.mapper.OtherInListInfoMapper;
import com.zeroone.star.storemanagement.mapper.OtherInListMapper;
import com.zeroone.star.storemanagement.service.IOtherInListService;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

@Service
public class OtherInListServiceImpl implements IOtherInListService {

    @Autowired
    OtherInListMapper otherInListMapper;

    @Autowired
    OtherInListInfoMapper otherInListInfoMapper;

    @Autowired
    CostMapper costMapper;

    @Override
    @Transactional
    public void updateOtherInList(OtherInListDetailDTO otherInListDetailDTO) {
        //判断入库单是否存在
        Integer examine = otherInListMapper.getExamineById(otherInListDetailDTO.getId());
        if(examine==null){
            throw new RuntimeException("入库单不存在");
        }
        if(examine==1){
            throw new RuntimeException("入库单已审核,无法修改");
        }
        //更新入库单
        EntryDO entry = new EntryDO();
        BeanUtils.copyProperties(otherInListDetailDTO,entry);
        otherInListMapper.update(entry);


        //获取入库单详情列表
        List<OtherInListInfoDTO> otherInListInfoDTOList = otherInListDetailDTO.getOtherInListInfoDTOList();
        //判断是否为空
        if(otherInListInfoDTOList==null||otherInListInfoDTOList.isEmpty()){
            throw new RuntimeException("入库单详情列表不能为空");
        }
        //删除原先的入库单详情数据
        otherInListInfoMapper.deleteByPid(otherInListDetailDTO.getId());
        //插入新的入库单详情数据
        Integer maxId = otherInListInfoMapper.getMaxId();
        if(maxId==null){
          maxId=0;
        }
        List<EntryInfoDO> entryInfoList = new ArrayList<>();
        for(OtherInListInfoDTO otherInListInfoDTO:otherInListInfoDTOList){
            EntryInfoDO entryInfo = new EntryInfoDO();
            BeanUtils.copyProperties(otherInListInfoDTO,entryInfo);
            entryInfo.setPid(otherInListDetailDTO.getId());
            entryInfo.setId(++maxId);
            entryInfoList.add(entryInfo);
        }
        otherInListInfoMapper.insertBatch(entryInfoList);


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
            cost.setIet(String.valueOf(costDTO.getIet()));
            cost.setMoney(BigDecimal.valueOf(costDTO.getMoney()));
            cost.setCls(otherInListDetailDTO.getId().toString());
            cost.setType("entry");
            cost.setTime(entry.getTime());
            cost.setSettle(BigDecimal.valueOf(0.0000));
            cost.setState(0);
            cost.setId(String.valueOf(++maxId));
            costList.add(cost);
        }
        costMapper.insertBatch(costList);
    }

    @Override
    public void examine(List<Integer> ids) {
        //查询id在ids中的入库单总数
        List<Integer> exmineStatusList = otherInListMapper.getExamineByIds(ids);
        //判断入库单总数是否等于ids的长度
        if(exmineStatusList.size()!=ids.size()){
            throw new RuntimeException("有入库单不存在");
        }
        int status = exmineStatusList.get(0);
        otherInListMapper.updateExamine(ids,status^1);
    }

    @Override
    public void check(List<Integer> ids) {
        List< Integer> checkStatusList = otherInListMapper.getCheckByIds(ids);
        if(checkStatusList.size()!=ids.size()){
            throw new RuntimeException("有入库单不存在");
        }
        int status = checkStatusList.get(0);
        otherInListMapper.updateCheck(ids,status^1);
    }
}
