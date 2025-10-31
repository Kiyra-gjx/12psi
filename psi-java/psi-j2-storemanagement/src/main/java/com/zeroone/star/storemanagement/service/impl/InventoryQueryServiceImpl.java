package com.zeroone.star.storemanagement.service.impl;


import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.AttrStockDTO;
import com.zeroone.star.project.dto.j2.store.InventoryDetailDTO;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
import com.zeroone.star.project.dto.j2.store.WarehouseStockDTO;
import com.zeroone.star.project.query.j2.store.InventoryDetailQuery;
import com.zeroone.star.project.query.j2.store.InventoryQuery;
import com.zeroone.star.storemanagement.mapper.AttrMapper;
import com.zeroone.star.storemanagement.mapper.InventoryDetailMapper;
import com.zeroone.star.storemanagement.mapper.InventoryMapper;
import com.zeroone.star.storemanagement.mapper.RoomMapper;
import com.zeroone.star.storemanagement.service.IInventoryQueryService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
@Service
@Slf4j
public class InventoryQueryServiceImpl  implements IInventoryQueryService {

    @Resource
    private InventoryMapper inventoryMapper;

    @Resource
    private AttrMapper attrMapper;

    @Resource
    private RoomMapper roomMapper;

    @Resource
    private InventoryDetailMapper inventoryDetailMapper;

    /**
     * 获取库存列表数据（分页）
     * @param query 查询条件对象，包含商品ID、仓库ID、辅助属性ID、时间范围、库存数量范围、库存状态等过滤条件以及分页参数
     * @return PageDTO<InventoryListDTO> 分页后的库存列表数据，每条记录包含商品ID、商品名称、仓库ID、仓库名称、辅助属性ID、辅助属性名称、库存数量、库存状态等字段
     */
    @Override
    public PageDTO<InventoryListDTO> getInventoryList(InventoryQuery query) {
            //1.xml联表查询基础数据
            Page<InventoryListDTO> page = new Page<>(query.getPageIndex(), query.getPageSize());
            Page<InventoryListDTO> resultPage = inventoryMapper.selectInventoryBaseList(page, query);

            //2.如果有数据，补充查询集合字段
            if (resultPage != null && !resultPage.getRecords().isEmpty()) {
                //提取商品id列表
                List<String> goodsIds = resultPage.getRecords().stream()
                        .map(InventoryListDTO::getId)
                        .collect(Collectors.toList());
                //批量查询辅助属性
                List<AttrStockDTO> attrStocks = attrMapper.selectAttrStockByGoodsIds(goodsIds);
                Map<String, List<AttrStockDTO>> attrStockMap = attrStocks.stream()
                        .collect(Collectors.groupingBy(AttrStockDTO::getPid));
                // 批量查询仓库明细
                List<WarehouseStockDTO> warehouseStocks = roomMapper.selectWarehouseStockByGoodsIds(goodsIds);
                // 直接按goodsId和attrId分组
                Map<String, Map<String, List<WarehouseStockDTO>>> warehouseGroupMap =
                        warehouseStocks.stream()
                                .collect(Collectors.groupingBy(
                                        WarehouseStockDTO::getGoodsId,
                                        Collectors.groupingBy(ws ->
                                                ws.getAttrId() == null ? "MAIN" : ws.getAttrId()
                                        )
                                ));

                // 组装数据
                resultPage.getRecords().forEach(item -> {
                    String goodsId = item.getId();//得到商品ID

                    // 获取该商品的所有仓库分组
                    Map<String, List<WarehouseStockDTO>> goodsWarehouseMap =
                            warehouseGroupMap.getOrDefault(goodsId, new HashMap<>());

                    // 设置主商品仓库库存（attrId为null的记录）
                    item.setWarehouses(goodsWarehouseMap.getOrDefault("MAIN", new ArrayList<>()));

                    // 设置辅助属性及对应的仓库库存
                    List<AttrStockDTO> attrs = attrStockMap.get(goodsId);
                    if (attrs != null) {
                        attrs.forEach(attr -> {
                            // 直接使用辅助属性ID从分组中获取对应的仓库库存
                            List<WarehouseStockDTO> attrWarehouses =
                                    goodsWarehouseMap.getOrDefault(attr.getAttrId(), new ArrayList<>());
                            attr.setWarehouses(attrWarehouses);
                        });
                        item.setAttrs(attrs);
                    } else {
                        item.setAttrs(new ArrayList<>());
                    }
                });
            }
            return PageDTO.create(resultPage);
    }


    /**
     * 获取库存详情数据（分页）
     * @param query 详情查询条件对象，包含商品ID、仓库ID、辅助属性ID、时间范围、库存数量范围、库存状态等过滤条件以及分页参数
     * @return PageDTO<InventoryDetailDTO> 分页后的库存详情数据，每条记录包含商品ID、商品名称、仓库ID、仓库名称、辅助属性ID、辅助属性名称、库存数量、库存状态等字段
     */
    @Override
    public PageDTO<InventoryDetailDTO> getInventoryDetail(InventoryDetailQuery query) {
        //TODO:后续可以使用校验注解优化
        if (query.getGoodsId() == null) {
            throw new IllegalArgumentException("商品ID不能为空");
        }

        Page<InventoryDetailDTO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        Page<InventoryDetailDTO> resultPage = inventoryDetailMapper.selectInventoryDetailList(page, query);

        return PageDTO.create(resultPage);

    }
}
