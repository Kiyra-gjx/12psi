package com.zeroone.star.storemanagement.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchListDTO;
import com.zeroone.star.project.query.j2.store.BatchQuery;
import com.zeroone.star.project.vo.JsonVO;


public interface IBatchListService {

    /**
     * 查询批次列表
     */
    PageDTO<BatchListDTO> listBatch(BatchQuery query);
}
