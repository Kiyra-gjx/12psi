package com.zeroone.star.storemanagement.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.storemanagement.entity.*;
import com.zeroone.star.storemanagement.mapper.*;
import com.zeroone.star.storemanagement.service.IOtherOutListService;
import org.springframework.stereotype.Service;
import javax.annotation.Resource;
import java.math.BigDecimal;
import java.util.List;
import java.util.Objects;

@Service
public class OtherOutListServiceImpl extends ServiceImpl<OtherOutListMapper, ExtryDO> implements IOtherOutListService {

    @Resource
    private OtherOutListMapper otherOutListMapper;
    @Resource
    private OtherOutListInfoMapper otherOutListInfoMapper;
    @Resource
    private GoodsMapper goodsMapper;
    @Resource
    private RoomMapper roomMapper;
    @Resource
    private BatchDOMapper batchDOMapper;

    public void examine(List<Integer> ids) {
        //取出出库单ID
        Integer extryId = ids.get(0);
        //1.根据Id查询该出库单每一个商品的类型，常规商品需要查询库存
        QueryWrapper<ExtryInfoDO>extryInfoDOQueryWrapper = new QueryWrapper<>();
        extryInfoDOQueryWrapper.eq("pid", extryId);
        List<ExtryInfoDO> extryInfoDOList = otherOutListInfoMapper.selectList(extryInfoDOQueryWrapper);
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
                    BatchDO batchDO = batchDOMapper.selectOne(batchDOQueryWrapper);
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
        ExtryDO extryDO = otherOutListMapper.selectById(extryId);
        update().set("examine", extryDO.getExamine() == 1 ? 0 : 1).eq("id", ids.get(0)).update();
    }

    @Override
    public void check(List<Integer> ids) {
        ExtryDO extryDO = otherOutListMapper.selectById(ids.get(0));
        if(extryDO != null) {
            update().set("`check`", extryDO.getCheck() == 1 ? 0 : 1).eq("id", ids.get(0)).update();
        }
    }
}
