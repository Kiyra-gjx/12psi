package com.zeroone.star.storemanagement.mapper;

import com.zeroone.star.storemanagement.entity.ServeDO;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

@Mapper
public interface ServeMapper {
    @Select("select id,goods,attr,nums from serve where goods = #{goods}")
    ServeDO getByGoods(String goods);

    @Select("select max(id) from serve")
    Integer getMaxId();

    @Update("insert into serve values(#{id},#{goods},#{attr},#{nums})")
    void insert(ServeDO serveDO);

    void updateById(ServeDO serveDO);

    @Delete("delete from serve where id = #{id}")
    void deleteById(String id);

}
