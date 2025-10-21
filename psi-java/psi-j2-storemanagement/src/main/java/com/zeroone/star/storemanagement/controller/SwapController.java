package com.zeroone.star.storemanagement.controller;

import com.zeroone.star.project.dto.j2.store.ShopListDto;
import com.zeroone.star.project.dto.j2.store.SwapListDTO;
import com.zeroone.star.project.j2.store.SwapDTOApis;
import com.zeroone.star.project.query.j2.store.SwapQuery;
import com.zeroone.star.project.query.j2.store.SwapQueryCondition;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@RequestMapping("/transfer")
@Api(tags = "调拨单")
public class SwapController implements SwapDTOApis {
    @PostMapping("/detail-swapInfo")
    @ApiOperation(value = "获取指定调拨单详细信息")
    @Override
    public JsonVO<String> detailSwapList(
            /*如果传入的调拨单详细信息为空，那就啥数据也没即可*/
            @ApiParam(value = "调拨单详细", required = false, example = "")
            @RequestBody List<SwapListDTO> swapListDTO) {
        return null;
    }

    @PostMapping("/query-swapList")
    @ApiOperation(value = "获取调拨单列表（条件+分页）")
    @Override
    public JsonVO<String> querySwapList(
            @ApiParam(value = "调拨单列表", required = true)
                    @RequestBody
            List<SwapQuery> swapQuery,
            @ApiParam(value = "调拨单查询条件", required = true)
                    @RequestBody
            SwapQueryCondition condition) {
        return null;
    }

    @PostMapping("/add-swapList")
    @ApiOperation(value = "新增调拨单")
    @Override
    public JsonVO<String> addSwapList(
            /*根据商品列表新增调拨单，可以批量*/
            @ApiParam(value = "商品列表", required = false)
            @RequestBody
            List<ShopListDto> shopListDto) {
        return null;
    }
}
