package com.zeroone.star.storemanagement.mapper;

import com.zeroone.star.storemanagement.entity.SummaryDO;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface SummaryMapper {
    @Select("select max(id) from is_summary")
    Integer getMaxId();

    void insert(SummaryDO summaryDO);

    @Delete("delete from is_summary where info=#{info}")
    void deleteByInfo(String id);
}
