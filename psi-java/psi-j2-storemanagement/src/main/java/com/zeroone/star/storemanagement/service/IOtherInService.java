package com.zeroone.star.storemanagement.service;

import com.zeroone.star.project.dto.j2.store.OtherInListDetailDTO;

import java.util.List;

public interface IOtherInService {
    void updateOtherInList(OtherInListDetailDTO otherInListDetailDTO);

    void examine(List<Integer> ids);

    void check(List<Integer> ids);
}
