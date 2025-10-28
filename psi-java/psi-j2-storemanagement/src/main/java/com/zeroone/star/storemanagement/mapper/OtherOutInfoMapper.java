package com.zeroone.star.storemanagement.mapper;

import com.zeroone.star.storemanagement.entity.ExtryInfoDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

@Mapper
public interface OtherOutInfoMapper {

    List<ExtryInfoDO > selectByMainIds(@Param("mainIds") List<Integer> mainIds);

}
