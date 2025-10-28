package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j2.store.TransferListDTO;
import com.zeroone.star.storemanagement.entity.Swap;
import org.apache.ibatis.annotations.Mapper;

@Mapper
public interface SwapMapper extends BaseMapper<Swap> {
    TransferListDTO getTransferListDTO(String id);
}
