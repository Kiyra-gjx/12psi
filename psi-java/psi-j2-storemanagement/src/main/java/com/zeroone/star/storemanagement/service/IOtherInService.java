package com.zeroone.star.storemanagement.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListAddDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDetailDTO;
import com.zeroone.star.project.query.j2.store.OtherInQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

public interface IOtherInService {
    void updateOtherInList(OtherInListDetailDTO otherInListDetailDTO);

    void examine(List<Integer> ids);

    void check(List<Integer> ids);

    OtherInListDetailDTO getOtherInListDetail(String id);

    JsonVO<String> saveOtherInList(OtherInListAddDTO dto);

    List<String> removeOtherInList(List<String> ids);

    JsonVO<PageDTO<OtherInListDTO>> getOtherInList(OtherInQuery query);
}
