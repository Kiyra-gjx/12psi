package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.storemanagement.entity.RecordDO;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

@Mapper
public interface RecordMapper extends BaseMapper<RecordDO>  {

    @Insert("insert into record (id, type, source, time, user, info) VALUE (#{id},#{type},#{source},#{time},#{user},#{info})")
    int insert(RecordDO record);

    void insertBatch(List<RecordDO> recordList);
}
