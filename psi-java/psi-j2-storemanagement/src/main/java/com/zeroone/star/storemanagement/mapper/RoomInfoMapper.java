package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.storemanagement.entity.RoomInfoDO;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;

@Mapper
public interface RoomInfoMapper extends BaseMapper<RoomInfoDO>{

    @Insert("insert into is_room_info (id, pid, type, class, info, time, direction, price, nums) VALUE (#{id},#{pid},#{type},#{cls},#{info},UNIX_TIMESTAMP(#{time}),#{direction},#{price},#{nums})")
    int insert(RoomInfoDO roomInfoDO);

    @Delete("delete from is_room_info where info = #{info}")
    void deleteByInfo(String id);
}
