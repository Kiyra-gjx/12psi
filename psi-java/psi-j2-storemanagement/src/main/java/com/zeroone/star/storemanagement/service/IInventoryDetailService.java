package com.zeroone.star.storemanagement.service;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.InventoryDetailDTO;
import com.zeroone.star.project.query.j2.store.InventoryDetailQuery;
import com.zeroone.star.project.vo.JsonVO;
import org.apache.ibatis.annotations.Param;

public interface IInventoryDetailService {
    JsonVO<PageDTO<InventoryDetailDTO>> getInventoryDetail(InventoryDetailQuery query);
}
