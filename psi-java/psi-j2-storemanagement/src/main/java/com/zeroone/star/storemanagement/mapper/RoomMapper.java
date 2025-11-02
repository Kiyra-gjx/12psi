package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j2.store.WarehouseStockDTO;
import com.zeroone.star.storemanagement.entity.RoomDO;
import org.apache.ibatis.annotations.*;

import java.math.BigDecimal;
import java.util.List;

public interface RoomMapper extends BaseMapper<RoomDO> {


    List<WarehouseStockDTO> selectWarehouseStockByGoodsIds(@Param("goodsIds") List<String> goodsIds);

    @Select("select max(id) from room")
    Integer getMaxId();

    @Select("select id, warehouse, goods, attr, nums from is_room where goods = #{goods}")
    RoomDO getByGoods(String goods);

    @Insert("insert into room(id,warehouse, goods, attr, nums) values(#{id},#{warehouse}, #{goods}, #{attr}, #{nums})")
    int insert(RoomDO roomDO);

    @Update("update room set warehouse = #{warehouse}, goods = #{goods}, attr = #{attr}, nums = #{nums} where id = #{id}")
    int updateById(RoomDO roomDO);

    @Delete("delete from room where id = #{id}")
    void deleteById(String id);

    @Select("SELECT EXISTS(SELECT 1 FROM is_room WHERE goods = #{goods} AND warehouse = #{warehouse} AND nums >= #{nums})")
    boolean isNumsEnough(@Param("goods") String goods, @Param("warehouse") String warehouse,
                         @Param("nums") BigDecimal nums);

    @Select("SELECT * FROM is_room WHERE goods = #{goodsId} AND warehouse = #{warehouseId}")
    RoomDO getRoomByGoodsAndWarehouse(@Param("goodsId") String goodsId, @Param("warehouseId") String warehouseId);

    @Update("UPDATE is_room SET nums = nums + #{nums} WHERE goods = #{goodsId} AND warehouse = #{warehouseId}")
    int updateRoomStock(@Param("goodsId") String goodsId, @Param("warehouseId") String warehouseId,
                        @Param("nums") BigDecimal nums);

    @Update("INSERT INTO is_room (id, goods, warehouse, attr, nums) VALUES (#{id}, #{goodsId}, #{warehouseId}, #{attr}, #{nums})")
    int createRoomInTargetWarehouse(@Param("id") String id, @Param("goodsId") String goodsId, @Param("warehouseId") String warehouseId,
                                    @Param("attr") String attr, @Param("nums") BigDecimal nums);

    @Select("SELECT id FROM is_room WHERE goods = #{goodsId} AND warehouse = #{warehouseId}")
    String getRoomId(@Param("goodsId") String goodsId, @Param("warehouseId") String warehouseId);
}
