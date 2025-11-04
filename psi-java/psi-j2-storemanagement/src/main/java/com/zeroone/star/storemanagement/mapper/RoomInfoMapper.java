package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.storemanagement.entity.RoomInfoDO;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface RoomInfoMapper extends BaseMapper<RoomInfoDO> {
    @Select("select max(id) from room_info")
    Integer getMaxId();

    @Insert("INSERT INTO room_info (id, pid, type, class, info, time, direction, price, nums) " +
            "VALUES (#{id}, #{pid}, #{type}, #{cls}, #{info}, #{time}, #{direction}, #{price}, #{nums})")
    int insert(RoomInfoDO roomInfoDO);

    @Delete("delete from room_info where info = #{info}")
    void deleteByInfo(String id);

    @Delete("delete from room_info where info = #{swapInfoId}")
    int deleteBySwapInfoId(String swapInfoId);
}
