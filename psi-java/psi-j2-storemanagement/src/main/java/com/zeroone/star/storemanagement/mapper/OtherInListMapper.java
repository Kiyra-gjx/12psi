package com.zeroone.star.storemanagement.mapper;

import com.zeroone.star.storemanagement.entity.EntryDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.util.List;

@Mapper
public interface OtherInListMapper {

    void update(EntryDO entry);

    void updateExamine(List<Integer> ids, int status);

    List<Integer> getExamineByIds(List<Integer> ids);

    List<Integer> getCheckByIds(List<Integer> ids);

    void updateCheck(List<Integer> ids, int status);

    @Select("select examine from entry where id = #{id}")
    Integer getExamineById(Integer id);
}
