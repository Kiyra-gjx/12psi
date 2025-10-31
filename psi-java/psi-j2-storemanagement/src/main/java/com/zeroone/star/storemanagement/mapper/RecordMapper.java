package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.storemanagement.entity.RecordDO;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.util.List;

@Mapper
public interface RecordMapper  {

    @Insert("insert into record (id, type, source, time, user, info) VALUE (#{id},#{type},#{source},#{time},#{user},#{info})")
    void insert(RecordDO record);

    void insertBatch(List<RecordDO> recordList);
}
