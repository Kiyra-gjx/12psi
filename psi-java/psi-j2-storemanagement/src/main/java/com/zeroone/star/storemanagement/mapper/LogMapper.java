package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.storemanagement.entity.LogDO;
import lombok.extern.slf4j.Slf4j;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface LogMapper  {

    @Select("select max(id) from log")
    Integer getMaxId();

    @Insert("insert into log (id, time, user, info) VALUE (#{id},#{time},#{user},#{info})")
    void insert(LogDO log);

    void insertBatch(List<LogDO> logList);
}
