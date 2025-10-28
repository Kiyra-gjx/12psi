package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.storemanagement.entity.ExtryDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

@Mapper
public interface OtherOutMapper extends BaseMapper<ExtryDO> {

    void examine(List<Integer> ids);

    List<ExtryDO> selectBatchIds(@Param("ids") List<Integer> ids);

}
