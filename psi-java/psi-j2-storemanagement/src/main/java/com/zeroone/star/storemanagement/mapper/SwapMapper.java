package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j2.store.TransferListDTO;
import com.zeroone.star.storemanagement.entity.SwapDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

@Mapper
public interface SwapMapper extends BaseMapper<SwapDO> {
    List<TransferListDTO> getTransferListDTOList(@Param("idList") List<String> idList);

}
