package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.storemanagement.entity.LogDO;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface LogMapper extends BaseMapper<LogDO>  {

    @Select("select max(id) from is_log")
    Integer getMaxId();

    @Insert("insert into is_log (id, time, user, info) VALUE (#{id},UNIX_TIMESTAMP(#{time}),#{user},#{info})")
    int insert(LogDO log);

    void insertBatch(List<LogDO> logList);
}
