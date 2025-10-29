package com.zeroone.star.storemanagement.service;

import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

public interface ITransferService {

    /*
    * 修改调拨单
    */
    JsonVO<String> modifyTransfer(TransferDetailDTO dto);

    /*
    * 删除调拨单
    */
    JsonVO<String> deleteTransfer(List<Integer> ids);
}
