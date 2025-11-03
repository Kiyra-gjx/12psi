package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j2.store.TransferDetailListDTO;
import com.zeroone.star.storemanagement.entity.SwapInfoDO;
import org.apache.ibatis.annotations.MapKey;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

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

    // /**
    //  * 根据调拨单的id查询调拨单详情
    //  */
    // // @Select("SELECT * FROM is_swap_info WHERE id = #{id}")
    // @Select("SELECT id, pid, goods, attr, unit, warehouse, storehouse, batch, " +
    //         "FROM_UNIXTIME(mfd) as mfd, price, nums, serial, total, data " +
    //         "FROM is_swap_info WHERE id = #{id}")
    // SwapInfoDO getTransferDetail(String id);

    /**
     * 根据id查询商品属性
     */
    @Select("SELECT attr FROM is_swap_info WHERE id = #{goodsId}")
    String getAttrById(String goodsId);

    /**
     * 批量删除调拨单详情
     */
    int deleteByIdList(@Param("ids") List<Integer> ids);

    /**
     * 批量查询调拨单状态和主表信息
     */
    @MapKey("id")
    List<Map<String, Object>> getBatchTransferStatus(@Param("ids") List<String> ids);

    /**
     * 批量查询调拨单详情
     */
    List<SwapInfoDO> getBatchTransferDetail(@Param("ids") List<String> ids);

    /**
     * 批量获取调拨单对应的主表ID
     */
    List<String> getSwapByIds(@Param("ids") List<String> ids);

    /**
     * 批量检查调拨单是否存在
     */
    int getExistsCountByIds(@Param("ids") List<String> ids);
}
