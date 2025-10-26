package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j2.store.InventoryDetailDTO;
import com.zeroone.star.project.query.j2.store.InventoryDetailQuery;
import com.zeroone.star.storemanagement.entity.RoomInfoDO;
import org.apache.ibatis.annotations.Param;

public interface InventoryDetailMapper extends BaseMapper<RoomInfoDO> {
    Page<InventoryDetailDTO> selectInventoryDetailList(Page<InventoryDetailDTO> page, @Param("query")InventoryDetailQuery query);
}
