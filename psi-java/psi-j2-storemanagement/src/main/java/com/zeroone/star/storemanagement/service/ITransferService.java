package com.zeroone.star.storemanagement.service;

import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.vo.JsonVO;

public interface ITransferService {

    /*
    * 修改调拨单
    */
    JsonVO<String> modifyTransfer(TransferDetailDTO dto);
}
