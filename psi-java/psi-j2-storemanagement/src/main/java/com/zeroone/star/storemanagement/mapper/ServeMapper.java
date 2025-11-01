package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.storemanagement.entity.ServeDO;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface ServeMapper extends BaseMapper<ServeDO> {
    @Select("select id,goods,attr,nums from is_serve where goods = #{goods}")
    ServeDO getByGoods(String goods);

    @Insert("insert into is_serve (id, goods, attr, nums) values(#{id},#{goods},#{attr},#{nums})")
    int insert(ServeDO serveDO);

    int updateById(ServeDO serveDO);

    @Delete("delete from is_serve where id = #{id}")
    void deleteById(String id);

}
