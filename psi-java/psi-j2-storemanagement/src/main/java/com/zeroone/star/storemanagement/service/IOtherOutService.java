package com.zeroone.star.storemanagement.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.OtherOutListDTO;
import com.zeroone.star.project.query.j2.store.OtherOutQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.entity.ExtryDO;

import java.io.InputStream;
import java.util.List;

public interface IOtherOutService extends IService<ExtryDO> {
    void examine(List<Integer> ids);

    void check(List<Integer> ids);

    byte[] exportOrderList(List<Integer> ids);

    byte[] exportOrderDetails(List<Integer> ids);

    void importOrders(InputStream inputStream) throws Exception;





    JsonVO<String> addOtherOutList(OtherOutListDTO otherOutListDTO);

    JsonVO<String> getOtherOutListInfo(String id);

    JsonVO<PageDTO<OtherOutListDTO>> listOtherOut(OtherOutQuery query);
}
