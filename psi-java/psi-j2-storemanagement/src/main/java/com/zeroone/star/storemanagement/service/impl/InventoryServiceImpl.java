package com.zeroone.star.storemanagement.service.impl;


import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.AttrStockDTO;
import com.zeroone.star.project.dto.j2.store.InventoryListDTO;
import com.zeroone.star.project.dto.j2.store.WarehouseStockDTO;
import com.zeroone.star.project.query.j2.store.InventoryQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.mapper.AttrMapper;
import com.zeroone.star.storemanagement.mapper.InventoryMapper;
import com.zeroone.star.storemanagement.mapper.RoomMapper;
import com.zeroone.star.storemanagement.service.IInventoryService;
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
public class InventoryServiceImpl  implements IInventoryService {

    @Resource
    private InventoryMapper inventoryMapper;

    @Resource
    private AttrMapper attrMapper;

    @Resource
    private RoomMapper roomMapper;

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
}
