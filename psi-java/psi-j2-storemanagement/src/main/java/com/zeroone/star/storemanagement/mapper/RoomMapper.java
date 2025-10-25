package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j2.store.WarehouseStockDTO;
import com.zeroone.star.storemanagement.entity.RoomDO;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface RoomMapper extends BaseMapper<RoomDO> {
    List<WarehouseStockDTO> selectWarehouseStockByGoodsIds(@Param("goodsIds") List<String> goodsIds);
}
