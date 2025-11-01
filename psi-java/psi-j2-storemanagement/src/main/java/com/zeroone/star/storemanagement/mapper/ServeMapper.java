package com.zeroone.star.storemanagement.mapper;

import com.zeroone.star.storemanagement.entity.ServeDO;
import org.apache.ibatis.annotations.*;

@Mapper
public interface ServeMapper {
    @Select("select id,goods,attr,nums from serve where goods = #{goods}")
    ServeDO getByGoods(String goods);

    @Insert("insert into serve (id, goods, attr, nums) values(#{id},#{goods},#{attr},#{nums})")
    void insert(ServeDO serveDO);

    void updateById(ServeDO serveDO);

    @Delete("delete from serve where id = #{id}")
    void deleteById(String id);

}
