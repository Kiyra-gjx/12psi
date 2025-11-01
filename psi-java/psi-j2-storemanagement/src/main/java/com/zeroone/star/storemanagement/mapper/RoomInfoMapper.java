package com.zeroone.star.storemanagement.mapper;

import com.zeroone.star.storemanagement.entity.RoomInfoDO;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface RoomInfoMapper {

    @Insert("insert into is_room_info (id, pid, type, class, info, time, direction, price, nums) VALUE (#{id},#{pid},#{type},#{cls},#{info},UNIX_TIMESTAMP(#{time}),#{direction},#{price},#{nums})")
    void insert(RoomInfoDO roomInfoDO);

    @Delete("delete from is_room_info where info = #{info}")
    void deleteByInfo(String id);
}
