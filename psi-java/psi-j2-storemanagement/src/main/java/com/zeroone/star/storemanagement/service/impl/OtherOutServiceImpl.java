package com.zeroone.star.storemanagement.service.impl;

import com.alibaba.excel.EasyExcel;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.storemanagement.entity.*;
import com.zeroone.star.storemanagement.mapper.*;
import com.zeroone.star.storemanagement.service.IOtherOutService;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.math.BigDecimal;
import java.util.List;
import java.util.Objects;


@Service
public class OtherOutServiceImpl extends ServiceImpl<OtherOutMapper, ExtryDO> implements IOtherOutService {

    @Resource
    private OtherOutMapper otherOutMapper;
    @Resource
    private OtherOutInfoMapper otherOutInfoMapper;
    @Resource
    private GoodsMapper goodsMapper;
    @Resource
    private RoomMapper roomMapper;
    @Resource
    private BatchMapper batchMapper;

    @Override
    public void examine(List<Integer> ids) {
        //取出出库单ID
        Integer extryId = ids.get(0);
        //1.根据Id查询该出库单每一个商品的类型，常规商品需要查询库存
        QueryWrapper<ExtryInfoDO> extryInfoDOQueryWrapper = new QueryWrapper<>();
        extryInfoDOQueryWrapper.eq("pid", extryId);
        List<ExtryInfoDO> extryInfoDOList = otherOutInfoMapper.selectList(extryInfoDOQueryWrapper);
        if(extryInfoDOList == null || extryInfoDOList.isEmpty()) {
            throw new RuntimeException("出库单信息有误!");
        }
        for (ExtryInfoDO extryInfoDO : extryInfoDOList) {
            String goodsId = extryInfoDO.getGoods();
            QueryWrapper<GoodsDO> goodsQueryWrapper = new QueryWrapper<>();
            goodsQueryWrapper.select("type").eq("id", goodsId);
            GoodsDO goodsDO = goodsMapper.selectOne(goodsQueryWrapper);
            if(goodsDO.getType() == 0) {
                //常规商品查询库存
                String warehouse = extryInfoDO.getWarehouse();
                QueryWrapper<RoomDO> roomDOQueryWrapper = new QueryWrapper<>();
                List<RoomDO> roomDOS = roomMapper.selectList(
                        roomDOQueryWrapper
                                .select("goods", "nums")
                                .eq("warehouse", warehouse)
                                .eq("goods", goodsId)
                );
                if(roomDOS == null){
                    throw new RuntimeException("仓储信息不存在!");
                }
                //初始化库存
                BigDecimal stock = BigDecimal.ZERO;
                //获取该仓库中所有该类型商品的库存
                for (RoomDO roomDO : roomDOS) {
                    stock = stock.add(roomDO.getNums());
                }
                if(stock.compareTo(extryInfoDO.getNums()) < 0) {
                    throw new RuntimeException("库存不足!");
                }
                //2.检查该出库单商品是否满足批次要求，如满足批次要求，则继续审核批次
                if(extryInfoDO.getBatch() != null && !extryInfoDO.getBatch().isEmpty()){
                    QueryWrapper<BatchDO> batchDOQueryWrapper = new QueryWrapper<>();
                    batchDOQueryWrapper.eq("warehouse", extryInfoDO.getWarehouse()).eq("number", extryInfoDO.getBatch());
                    BatchDO batchDO = batchMapper.selectOne(batchDOQueryWrapper);
                    if(batchDO == null) {
                        throw new RuntimeException("批次信息有误!");
                    }
                    boolean batchMatch = extryInfoDO.getBatch().equals(batchDO.getNumber()) &&
                            Objects.equals(extryInfoDO.getMfd(), batchDO.getTime()) &&
                            batchDO.getWarehouse().equals(extryInfoDO.getWarehouse()) &&
                            Objects.equals(extryInfoDO.getNums(), batchDO.getNums());

                    if (!batchMatch) {
                        throw new RuntimeException("批次信息不匹配!");
                    }
                }
            }
        }
        ExtryDO extryDO = otherOutMapper.selectById(extryId);
        update().set("examine", extryDO.getExamine() == 1 ? 0 : 1).eq("id", ids.get(0)).update();
    }

    @Override
    public void check(List<Integer> ids) {
        ExtryDO extryDO = otherOutMapper.selectById(ids.get(0));
        if(extryDO != null) {
            update().set("`check`", extryDO.getCheck() == 1 ? 0 : 1).eq("id", ids.get(0)).update();
        }
    }

    @Override
    public byte[] exportOrderList(List<Integer> ids) {
        List<ExtryDO> dataList = otherOutMapper.selectBatchIds(ids);

        ByteArrayOutputStream outputStream = null;
        try {
            outputStream = new ByteArrayOutputStream();
            EasyExcel.write(outputStream, ExtryDO.class)
                    .sheet("其他出库单")
                    .doWrite(dataList);
            return outputStream.toByteArray();
        } finally {
            if (outputStream != null) {
                try {
                    outputStream.close();
                } catch (IOException e) {
                    // 记录日志但不中断操作
                    log.warn("Failed to close ByteArrayOutputStream");
                }
            }
        }
    }

    @Override
    public byte[] exportOrderDetails(List<Integer> ids) {
        List<ExtryInfoDO> detailList = otherOutInfoMapper.selectByMainIds(ids);

        try (ByteArrayOutputStream outputStream = new ByteArrayOutputStream()) {
            EasyExcel.write(outputStream, ExtryInfoDO.class)
                    .sheet("其他出库单明细")
                    .doWrite(detailList);
            return outputStream.toByteArray();
        } catch (IOException e) {
            throw new RuntimeException("导出Excel失败", e);
        }
    }

    @Override
    @Transactional
    public void importOrders(InputStream inputStream) throws Exception {
        List<ExtryDO> dataList = EasyExcel.read(inputStream)
                .head(ExtryDO.class)
                .sheet()
                .doReadSync();

        for (ExtryDO dto : dataList) {
            // 转换并保存入库
            ExtryDO entity = convertToEntity(dto);
            otherOutMapper.insert(entity);
        }
    }

    private ExtryDO convertToEntity(ExtryDO dto) {
        ExtryDO entity = new ExtryDO();
        entity.setId(dto.getId());
        entity.setCustomer(dto.getCustomer());
        entity.setFrame(dto.getFrame());
        entity.setTime(dto.getTime());
        entity.setNumber(dto.getNumber());
        entity.setType(dto.getType());
        entity.setTotal(dto.getTotal());
        entity.setCost(dto.getCost());
        entity.setPeople(dto.getPeople());
        entity.setLogistics(dto.getLogistics());
        entity.setFile(dto.getFile());
        entity.setData(dto.getData());
        entity.setMore(dto.getMore());
        entity.setExamine(dto.getExamine());
        entity.setCse(dto.getCse());
        entity.setCheck(dto.getCheck());
        entity.setUser(dto.getUser());
        return entity;
    }


}



