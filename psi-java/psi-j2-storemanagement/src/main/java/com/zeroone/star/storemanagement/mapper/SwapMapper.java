package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j2.store.TransferListDTO;
import com.zeroone.star.storemanagement.entity.SwapDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface SwapMapper extends BaseMapper<SwapDO> {

    /**
     * 根据id查询调拨单状态
     */
    @Select("SELECT examine FROM swap WHERE id = #{id}")
    Integer getStatusById(@Param("id") String id);
    /**
     * 更新调拨单信息
     */
    int updateSwap(SwapDO swap);

    /**
     * 批量删除
     */
    int deleteBatchIds(@Param("ids") List<String> ids);

    /**
     * 获取调拨单列表
     */
    List<TransferListDTO> getTransferListDTOList(@Param("idList") List<String> idList);

    /**
     * 批量审核/反审核调拨单
     */
    int auditBatchStatus(@Param("pidList") List<String> validPidList, @Param("operation") Integer operation);
}
