package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j2.store.TransferDetailListDTO;
import com.zeroone.star.storemanagement.entity.SwapInfoDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

@Mapper
public interface SwapInfoMapper extends BaseMapper<SwapInfoDO> {

    /**
     * 根据id查询到调拨单的id
     */
    @Select("SELECT pid FROM swap_info WHERE id = #{id}")
    String getSwapById(@Param("id") String id);

    /**
     * 更新调拨单详情信息
     */
    int updateSwap(SwapInfoDO swapInfo);

    /**
     * 根据ID列表查询对应的pid列表
     */
    List<String> getPidListByIds(@Param("ids") List<Integer> ids);

    ArrayList<TransferDetailListDTO> getTransferDetailListDTO(@Param("id") String id);
}
