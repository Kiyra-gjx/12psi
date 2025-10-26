package com.zeroone.star.storemanagement.mapper;


import com.zeroone.star.storemanagement.entity.CostDO;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface CostMapper {

    @Select("select max(id) from cost")
    Integer getMaxId();

    @Delete("delete from cost where class = #{id}")
    void deleteBycls(Integer id);

    void insertBatch(List<CostDO> costList);
}
