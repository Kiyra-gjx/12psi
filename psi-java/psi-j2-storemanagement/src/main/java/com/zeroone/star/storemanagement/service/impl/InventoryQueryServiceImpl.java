package com.zeroone.star.storemanagement.service.impl;


import cn.hutool.core.date.DateTime;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import java.math.BigDecimal;
import java.util.ArrayList;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsClientComponent;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.*;
import com.zeroone.star.project.query.j2.store.InventoryDetailQuery;
import com.zeroone.star.project.query.j2.store.InventoryQuery;
import com.zeroone.star.storemanagement.mapper.AttrMapper;
import com.zeroone.star.storemanagement.mapper.InventoryDetailMapper;
import com.zeroone.star.storemanagement.mapper.InventoryMapper;
import com.zeroone.star.storemanagement.mapper.RoomMapper;
import com.zeroone.star.storemanagement.service.IInventoryQueryService;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.util.*;
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

    @Resource
    private FastDfsClientComponent dfs;
    @Resource
    private EasyExcelComponent excel;
    @Resource
    UserHolder userHolder;

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

    /**
     * 导出库存列表数据Excel
     * @param query
     * @return
     */
    @SneakyThrows
    @Override
    public ResponseEntity<byte[]> getListExport(InventoryQuery query) {
        // 定义输出流
        ByteArrayOutputStream out = new ByteArrayOutputStream();

        // TODO 获取库存列表数据
//        List<InventoryListDTO> inventoryListDTOS = inventoryMapper.getInventroyList();
        List<InventoryListDTO> inventoryListDTOS = null;

        // 生成Excel
        excel.export("库存列表",out,InventoryListDTO.class,inventoryListDTOS);

        // 响应给前端
        HttpHeaders headers = new HttpHeaders();
        String filename = "库存列表" + DateTime.now().toString("yyyyMMddHHmmssS") + ".xlsx";
        headers.setContentDispositionFormData("attachment", filename);
        headers.setContentType(MediaType.APPLICATION_OCTET_STREAM);
        ResponseEntity<byte[]> res = new ResponseEntity<>(out.toByteArray(), headers, HttpStatus.CREATED);
        out.close();

        return res;
    }

    /**
     * 导出库存详情数据Excel
     * @param id
     * @return
     */
    @SneakyThrows
    @Override
    public ResponseEntity<byte[]> getDetailExport(String id) {
        // 定义输出流
        ByteArrayOutputStream out = new ByteArrayOutputStream();

        // 获取库存详情数据
        List<InventoryDetailExcelDTO> inventoryDetailDTOS = inventoryDetailMapper.getDetailList(id);
        
        // 处理数据并设置默认值
        if (inventoryDetailDTOS != null) {
            for (InventoryDetailExcelDTO dto : inventoryDetailDTOS) {
                // 设置所属组织
                dto.setName(userHolder != null && userHolder.getCurrentUser() != null && userHolder.getCurrentUser().getFrameName() != null ? userHolder.getCurrentUser().getFrameName() : "默认组织");
                // 确保其他必要字段不为空
                if (dto.getType() == null) {
                    dto.setType("");
                }
                if (dto.getNumber() == null) {
                    dto.setNumber("");
                }
                if (dto.getDirection() == null) {
                    dto.setDirection(String.valueOf(0));
                }
                if (dto.getNums() == null) {
                    dto.setNums(BigDecimal.ZERO);
                }
            }
        } else {
            // 如果没有数据，创建空列表避免NPE
            inventoryDetailDTOS = new ArrayList<>();
        }

        // 生成Excel
        excel.export("库存详情", out, InventoryDetailExcelDTO.class, inventoryDetailDTOS);

        // 响应给前端
        HttpHeaders headers = new HttpHeaders();
        String filename = "库存详情" + DateTime.now().toString("yyyyMMddHHmmssS") + ".xlsx";
        headers.setContentDispositionFormData("attachment", filename);
        headers.setContentType(MediaType.APPLICATION_OCTET_STREAM);
        ResponseEntity<byte[]> res = new ResponseEntity<>(out.toByteArray(), headers, HttpStatus.CREATED);
        out.close();
        return res;
    }
}
