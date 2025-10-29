package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.storemanagement.entity.ExtryDO;
import com.zeroone.star.storemanagement.entity.ExtryInfoDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

@Mapper
public interface OtherOutInfoMapper extends BaseMapper<ExtryInfoDO> {

    List<ExtryInfoDO > selectByMainIds(@Param("mainIds") List<Integer> mainIds);
    void insertBatch(List<ExtryInfoDO> extryInfoList);

}
