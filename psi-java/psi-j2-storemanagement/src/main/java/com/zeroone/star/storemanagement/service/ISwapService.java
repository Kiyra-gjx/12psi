package com.zeroone.star.storemanagement.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.j2.store.TransferListDTO;
import com.zeroone.star.storemanagement.entity.Swap;

import java.util.ArrayList;
import java.util.List;

public interface ISwapService extends IService<Swap> {

    ArrayList<TransferListDTO> getTransferListDTOList(List<String> idList);
}
