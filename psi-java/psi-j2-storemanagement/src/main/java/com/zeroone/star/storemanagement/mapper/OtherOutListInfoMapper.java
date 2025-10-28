package com.zeroone.star.storemanagement.mapper;
import com.zeroone.star.project.dto.j2.store.OtherOutListInfoDTO;
import com.zeroone.star.storemanagement.entity.EntryInfoDO;
import com.zeroone.star.storemanagement.entity.ExtryInfoDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

@Mapper
public interface OtherOutListInfoMapper{

    /**
     * 批量插入出库单明细
     * @param list 明细列表
     * @return 影响行数
     */
    int insertBatch(@Param("list") List<ExtryInfoDO> list);

    /**
     * 根据主表ID查询明细列表
     * @param pid 主表ID
     * @return 明细列表
     */
    List<ExtryInfoDO> selectByPid(String pid);
}