package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j2.store.WarehouseStockDTO;
import com.zeroone.star.storemanagement.entity.RoomDO;
import org.apache.ibatis.annotations.*;

import java.util.List;

public interface RoomMapper extends BaseMapper<RoomDO> {


    List<WarehouseStockDTO> selectWarehouseStockByGoodsIds(@Param("goodsIds") List<String> goodsIds);

    @Select("select id, warehouse, goods, attr, nums from room where goods = #{goods}")
    RoomDO getByGoods(String goods);

    @Insert("insert into room(id,warehouse, goods, attr, nums) values(#{id},#{warehouse}, #{goods}, #{attr}, #{nums})")
    int insert(RoomDO roomDO);

    @Update("update room set warehouse = #{warehouse}, goods = #{goods}, attr = #{attr}, nums = #{nums} where id = #{id}")
    int updateById(RoomDO roomDO);

    @Delete("delete from room where id = #{id}")
    void deleteById(String id);
}
