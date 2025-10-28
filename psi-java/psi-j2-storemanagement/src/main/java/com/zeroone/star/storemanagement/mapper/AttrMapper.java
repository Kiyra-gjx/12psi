package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.j2.store.AttrStockDTO;
import com.zeroone.star.storemanagement.entity.AttrDO;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface AttrMapper extends BaseMapper<AttrDO> {

    List<AttrStockDTO> selectAttrStockByGoodsIds(@Param("goodsIds") List<String> goodsIds);
}