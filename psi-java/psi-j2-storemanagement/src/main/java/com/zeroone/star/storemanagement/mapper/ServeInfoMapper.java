package com.zeroone.star.storemanagement.mapper;

import com.zeroone.star.storemanagement.entity.ServeInfoDO;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface ServeInfoMapper {
    @Select("select max(id) from serve_info")
    Integer getMaxId();

    @Insert("insert into serve_info (id,pid,type,class,info,time,price,nums) VALUES (#{id},#{pid},#{type},#{cls},#{info},#{time},#{price},#{nums})")
    void insert(ServeInfoDO serveInfoDO);

    @Delete("delete from serve_info where info=#{info}")
    void deleteByInfo(String id);
}
