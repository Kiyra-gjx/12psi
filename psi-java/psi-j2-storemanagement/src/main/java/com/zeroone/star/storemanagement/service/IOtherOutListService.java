package com.zeroone.star.storemanagement.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.OtherOutListDTO;
import com.zeroone.star.project.query.j2.store.OtherOutQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.entity.ExtryDO;
import java.util.List;

public interface IOtherOutListService extends IService<ExtryDO> {
    void examine(List<Integer> ids);

    void check(List<Integer> ids);


    JsonVO<String> addOtherOutList(OtherOutListDTO otherOutListDTO);

    JsonVO<String> getOtherOutListInfo(String id);

    JsonVO<PageDTO<OtherOutListDTO>> listOtherOut(OtherOutQuery query);
}
