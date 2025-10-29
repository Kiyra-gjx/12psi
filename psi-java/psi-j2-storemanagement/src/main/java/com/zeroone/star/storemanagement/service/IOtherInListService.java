package com.zeroone.star.storemanagement.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDTO;
import com.zeroone.star.project.query.j2.store.OtherInQuery;
import com.zeroone.star.project.vo.JsonVO;

public interface IOtherInListService {
    JsonVO<PageDTO<OtherInListDTO>> getOtherInList(OtherInQuery query);
}