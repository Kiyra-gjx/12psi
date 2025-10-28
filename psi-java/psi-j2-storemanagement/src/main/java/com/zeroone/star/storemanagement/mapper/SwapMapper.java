package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.storemanagement.entity.SwapInfoDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface SwapMapper extends BaseMapper<SwapInfoDO> {

    /**
     * 根据id查询调拨单状态
     */
    @Select("SELECT examine FROM swap WHERE id = #{id}")
    Integer getStatusById(@Param("id") String id);

    /**
     * 更新调拨单信息
     */
    int updateSwap(@Param("swap") SwapInfoDO swap);
}
