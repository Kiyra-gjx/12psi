package com.zeroone.star.storemanagement.service.impl;

import com.alibaba.fastjson.JSON;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.CostDTO;
import com.zeroone.star.project.dto.j2.store.OtherOutListDTO;
import com.zeroone.star.project.dto.j2.store.OtherOutListInfoDTO;
import com.zeroone.star.project.query.j2.store.OtherOutQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.entity.CostDO;
import com.zeroone.star.storemanagement.entity.ExtryDO;
import com.zeroone.star.storemanagement.entity.ExtryInfoDO;
import com.zeroone.star.storemanagement.mapper.CostMapper;
import com.zeroone.star.storemanagement.mapper.OtherInListInfoMapper;
import com.zeroone.star.storemanagement.mapper.OtherOutListInfoMapper;
import com.zeroone.star.storemanagement.mapper.OtherOutListMapper;
import com.zeroone.star.storemanagement.service.IOtherOutListService;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;
import java.util.stream.Collectors;

/**
 * 功能：
 * <p>
 * ——————————————————————————————
 * version   变更日期    修改人
 * ------------------------------
 * v1.0.0    2025/10/26    shark
 * ——————————————————————————————
 * 修改说明：
 *
 * @author: shark
 */

@Service
public class OtherOutListServiceImpl extends ServiceImpl<OtherOutListMapper, ExtryDO> implements IOtherOutListService {

    @Resource
    private OtherOutListMapper otherOutListMapper;
    @Autowired
    private OtherOutListInfoMapper otherOutListInfoMapper;

    @Autowired
    private CostMapper costMapper;
    @Override
    public JsonVO<PageDTO<OtherOutListDTO>> listOtherOut(OtherOutQuery query) {
        // 1. 计算分页参数
        // 2. 执行查询
        // 2. 创建MyBatis-Plus分页对象（pageIndex从1开始）
        Page<OtherOutListDTO> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 3. 执行分页查询
        Page<OtherOutListDTO> resultPage = otherOutListMapper.selectByPage(page, query);

        // 4. 转换DO列表为DTO列表（使用BeanUtils复制属性）
        List<OtherOutListDTO> dtoList = resultPage.getRecords().stream()
                .map(doObj -> {
                    OtherOutListDTO dto = new OtherOutListDTO();
                    BeanUtils.copyProperties(doObj, dto);
                    return dto;
                })
                .collect(Collectors.toList());

        // 5. 构建PageDTO对象
        PageDTO<OtherOutListDTO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(query.getPageIndex());
        pageDTO.setPageSize(query.getPageSize());
        pageDTO.setTotal(resultPage.getTotal());
        pageDTO.setPages(resultPage.getPages());
        pageDTO.setRows(dtoList);

        // 6. 返回成功结果
        return JsonVO.success(pageDTO);
    }

    @Override
    public JsonVO<String> getOtherOutListInfo(String id) {
        // 1. 查询主表信息
        ExtryDO extryDO = otherOutListMapper.selectById(id);
        if (extryDO == null) {
            return JsonVO.fail("出库单不存在");
        }

        // 2. 查询详情列表
        List<ExtryInfoDO> infoDOList = otherOutListInfoMapper.selectByPid(id);
        List<OtherOutListInfoDTO> infoDTOList = infoDOList.stream().map(infoDO -> {
            OtherOutListInfoDTO dto = new OtherOutListInfoDTO();
            BeanUtils.copyProperties(infoDO, dto);
            return dto;
        }).collect(Collectors.toList());

        // 3. 查询费用列表
        List<CostDO> costDOList = costMapper.selectByCls(id.toString());
        List<CostDTO> costDTOList = costDOList.stream().map(costDO -> {
            CostDTO dto = new CostDTO();
            BeanUtils.copyProperties(costDO, dto);
            return dto;
        }).collect(Collectors.toList());

        // 4. 组装完整DTO
        OtherOutListDTO resultDTO = new OtherOutListDTO();
        BeanUtils.copyProperties(extryDO, resultDTO);
        resultDTO.setOtherOutListInfoDTOList(infoDTOList);
        resultDTO.setCostDTOList(costDTOList);

        return JsonVO.success(JSON.toJSONString(resultDTO));
    }

    @Transactional
    @Override
    public JsonVO<String> addOtherOutList(OtherOutListDTO otherOutListDTO) {
// 1. 参数验证
        if (otherOutListDTO.getNumber() == null || otherOutListDTO.getNumber().isEmpty()) {
            return JsonVO.fail("单据编号不能为空");
        }
        if (otherOutListDTO.getOtherOutListInfoDTOList() == null || otherOutListDTO.getOtherOutListInfoDTOList().isEmpty()) {
            return JsonVO.fail("出库单详情不能为空");
        }

        // 2. 生成主键ID
        String id = UUID.randomUUID().toString().replace("-", "");

        // 3. 保存主表信息
        ExtryDO extryDO = new ExtryDO();
        BeanUtils.copyProperties(otherOutListDTO, extryDO);
        extryDO.setId(id);
        extryDO.setTime(LocalDateTime.ofEpochSecond(otherOutListDTO.getTime(), 0, ZoneOffset.ofHours(8)));
        otherOutListMapper.insert(extryDO);

        // 4. 保存详情列表
        List<OtherOutListInfoDTO> infoList = otherOutListDTO.getOtherOutListInfoDTOList();
        List<ExtryInfoDO> extryInfoList = new ArrayList<>();

        for (OtherOutListInfoDTO infoDTO : infoList) {
            ExtryInfoDO extryInfo = new ExtryInfoDO();
            BeanUtils.copyProperties(infoDTO, extryInfo);
            extryInfo.setPid(id);
            extryInfo.setId(UUID.randomUUID().toString().replace("-", ""));
            extryInfoList.add(extryInfo);
        }
        otherOutListInfoMapper.insertBatch(extryInfoList);

        // 5. 保存费用列表
        if (otherOutListDTO.getCostDTOList() != null && !otherOutListDTO.getCostDTOList().isEmpty()) {
            List<CostDO> costList = new ArrayList<>();
            for (CostDTO costDTO : otherOutListDTO.getCostDTOList()) {
                CostDO cost = new CostDO();
                BeanUtils.copyProperties(costDTO, cost);
                cost.setId(UUID.randomUUID().toString().replace("-", ""));
                cost.setCls(id);
                cost.setType("extry"); // 标识为出库单费用
                costList.add(cost);
            }
            costMapper.insertBatch(costList);
        }

        return JsonVO.success("添加成功");
    }
    @Override
    public void examine(List<Integer> ids) {
        //TODO : 待实现关联表的审核逻辑
        ExtryDO extryDO = otherOutListMapper.selectById(ids.get(0));
        if(extryDO != null) {
            update().set("examine", extryDO.getExamine() == 1 ? 0 : 1).eq("id", ids.get(0)).update();
        }
    }

    @Override
    public void check(List<Integer> ids) {
        //TODO : 待实现关联表的核对逻辑
        ExtryDO extryDO = otherOutListMapper.selectById(ids.get(0));
        if(extryDO != null) {
            update().set("`check`", extryDO.getCheck() == 1 ? 0 : 1).eq("id", ids.get(0)).update();
        }
    }
}
