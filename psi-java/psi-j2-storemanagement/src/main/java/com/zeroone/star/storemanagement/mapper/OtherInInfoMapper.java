package com.zeroone.star.storemanagement.mapper;

import com.zeroone.star.storemanagement.entity.EntryInfoDO;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface OtherInInfoMapper {
    @Delete("delete from entry_info where pid = #{pid}")
    void deleteByPid(String pid);

    void insertBatch(List<EntryInfoDO> entryInfoList);

    @Select("select max(id) from entry_info")
    Integer getMaxId();

    void deleteById(Integer id);
}
