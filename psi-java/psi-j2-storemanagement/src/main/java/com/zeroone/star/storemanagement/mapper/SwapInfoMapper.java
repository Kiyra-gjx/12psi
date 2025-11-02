package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j2.store.TransferDetailListDTO;
import com.zeroone.star.storemanagement.entity.SwapInfoDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.lang.reflect.Array;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

@Mapper
public interface SwapInfoMapper extends BaseMapper<SwapInfoDO> {

    /**
     * 根据id查询到调拨单的id
     */
    @Select("SELECT pid FROM is_swap_info WHERE id = #{id}")
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

    /**
     * 根据调拨单的id查询库存是否充足
     */
    @Select("SELECT EXISTS(SELECT 1 FROM is_room WHERE goods = #{goods} AND warehouse = #{warehouse} AND nums >= #{nums})")
    boolean isNumsEnough(@Param("goods") String goods, @Param("warehouse") String warehouse, @Param("nums") BigDecimal nums);

    /**
     * 根据调拨单的id查询调拨单详情
     */
    @Select("SELECT * FROM is_swap_info WHERE id = #{id}")
    SwapInfoDO getTransferDetail(String id);

    /**
     * 根据id查询商品属性
     */
    @Select("SELECT attr FROM is_swap_info WHERE id = #{goodsId}")
    String getAttrById(String goodsId);
}
