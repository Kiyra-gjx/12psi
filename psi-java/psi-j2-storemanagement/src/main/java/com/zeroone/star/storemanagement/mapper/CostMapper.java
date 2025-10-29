package com.zeroone.star.storemanagement.mapper;


import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.storemanagement.entity.CostDO;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface CostMapper extends BaseMapper<CostDO> {

    @Select("select max(id) from cost")
    Integer getMaxId();

    @Delete("delete from cost where class = #{id}")
    void deleteBycls(String id);

    void insertBatch(List<CostDO> costList);
}
