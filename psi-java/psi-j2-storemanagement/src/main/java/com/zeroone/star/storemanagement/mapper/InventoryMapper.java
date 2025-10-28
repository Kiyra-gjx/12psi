package com.zeroone.star.storemanagement.mapper;


import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
import com.zeroone.star.project.query.j2.store.InventoryQuery;
import com.zeroone.star.storemanagement.entity.GoodsDO;
import org.apache.ibatis.annotations.Param;


public interface InventoryMapper extends BaseMapper<GoodsDO> {
    Page<InventoryListDTO> selectInventoryBaseList(Page<InventoryListDTO> page, @Param("query")InventoryQuery query);
}
