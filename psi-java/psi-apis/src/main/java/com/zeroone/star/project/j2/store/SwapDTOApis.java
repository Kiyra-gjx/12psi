package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.j2.store.SwapListDTO;
import com.zeroone.star.project.query.j2.store.SwapQuery;
import com.zeroone.star.project.query.j2.store.SwapQueryCondition;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * 调拨单详细信息接口
 * 定义了与调拨单详细列表相关的API操作
 */
public interface SwapDTOApis {
    /**
     * 查看调拨单详细信息
     * @param swapListDTO 调拨单详细信息DTO
     * @return 包含调拨单详细信息的JsonVO对象
     */
    JsonVO<String> detailSwapList(List<SwapListDTO> swapListDTO);
    /*
    * 获取调拨单列表
    * @param swapQuery 调拨单列表
    * swapQueryCondition 调拨单列表查询参数
    * @return 包含调拨单列表信息的JsonVO对象
    */
    JsonVO<String> querySwapList(List<SwapQuery> swapQuery, SwapQueryCondition condition);
}
