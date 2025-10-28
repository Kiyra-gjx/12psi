package com.zeroone.star.storemanagement.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.InventoryDetailDTO;
import com.zeroone.star.project.query.j2.store.InventoryDetailQuery;


public interface IInventoryDetailService {
    PageDTO<InventoryDetailDTO> getInventoryDetail(InventoryDetailQuery query);
}
