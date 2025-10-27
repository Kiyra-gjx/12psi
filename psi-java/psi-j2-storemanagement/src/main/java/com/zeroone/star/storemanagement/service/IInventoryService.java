package com.zeroone.star.storemanagement.service;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
import com.zeroone.star.project.query.j2.store.InventoryQuery;
import com.zeroone.star.project.vo.JsonVO;

public interface IInventoryService  {

    /**
     * 获取库存列表（条件+分页）
     * @param query 查询条件
     * @return 库存列表分页数据
     */
    PageDTO<InventoryListDTO> getInventoryList(InventoryQuery query);
}
