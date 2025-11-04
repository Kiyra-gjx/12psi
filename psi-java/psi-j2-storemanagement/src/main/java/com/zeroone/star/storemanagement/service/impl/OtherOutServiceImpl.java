package com.zeroone.star.storemanagement.service.impl;

import com.alibaba.excel.EasyExcel;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.*;
import com.zeroone.star.project.query.j2.store.OtherOutQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.entity.*;
import com.zeroone.star.storemanagement.mapper.*;
import com.zeroone.star.storemanagement.service.IOtherOutService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.util.*;
import java.util.stream.Collectors;

@Slf4j
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
    private CostMapper costMapper;
    @Resource
    private BatchMapper batchMapper;
    @Autowired
    MsEntryMapper ms;
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

    @Override
    public JsonVO<String> addOtherOutList(OtherOutListDTO otherOutListDTO) {

        // 更新出库单
        ExtryDO extry = new ExtryDO();
        BeanUtils.copyProperties(otherOutListDTO, extry);
        extry.setTime(LocalDateTime.now());

        otherOutMapper.insertBatch(extry);
        // 获取出库单详情列表
        List<OtherOutListInfoDTO> otherOutListInfoDTOList = otherOutListDTO.getOtherOutListInfoDTOList();
        //判断是否为空
        if (otherOutListInfoDTOList == null || otherOutListInfoDTOList.isEmpty()) {
            throw new RuntimeException("出库单详情列表不能为空");
        }
        //插入新的入库单详情数据
        Integer maxId = costMapper.getMaxId();
        maxId = maxId == null ? 0 : maxId;
        List<ExtryInfoDO> extryInfoList = new ArrayList<>();
        for (OtherOutListInfoDTO otherOutListInfoDTO : otherOutListInfoDTOList) {
            ExtryInfoDO extryInfo = new ExtryInfoDO();
            BeanUtils.copyProperties(otherOutListInfoDTO, extryInfo);
            extryInfo.setPid(otherOutListDTO.getId());
            extryInfo.setId((++maxId).toString());
            extryInfoList.add(extryInfo);
        }
        otherOutInfoMapper.insertBatch(extryInfoList);


        List<CostDTO>costDTOList = otherOutListDTO.getCostDTOList();
        //插入新的花费单据数据
        maxId = costMapper.getMaxId();
        maxId = maxId == null ? 0 : maxId;
        List<CostDO> costList = new ArrayList<>();
        for (CostDTO costDTO : costDTOList) {
            CostDO cost = new CostDO();
            BeanUtils.copyProperties(costDTO, cost);
            cost.setCls(otherOutListDTO.getId());
            cost.setType("extry");
            // cost.setTime(extry.getTime());
            cost.setSettle(BigDecimal.valueOf(0.0000));
            cost.setState(0);
            cost.setId((++maxId).toString());
            costList.add(cost);
        }
            costMapper.insertBatch(costList);

        return JsonVO.success("添加成功");
    }

    @Override
    public JsonVO<OtherOutListInfoDTO> getOtherOutListInfo(String id) {
        // 1.检查用户权限 权限校验可以定义AOP切面实现
        if (!checkPermission()) {
            log.info("用户无操作权限");
        }
        // 2.判断入库单是否存在
        ExtryDO exist = otherOutMapper.selectById(id);
        if (exist == null) {
            log.info("出库单不存在");
        }
        ExtryInfoDO extryInfoDO = otherOutInfoMapper.selectById(id);
        // 3.查询入库单详细
        OtherOutListInfoDTO dto = ms.extryInfoToOtherOutListInfoDTO(extryInfoDO);
        // 4.记录操作日志
        logOperation(dto.getId(), "查询出库单详细");
        return JsonVO.success(dto);
    }

    @Override
    public JsonVO<PageDTO<OtherOutListDTO>> listOtherOut(OtherOutQuery query) {
        // 1. 计算分页参数
        // 2. 执行查询
        // 2. 创建MyBatis-Plus分页对象（pageIndex从1开始）
        Page<OtherOutListDTO> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 3. 执行分页查询
        Page<OtherOutListDTO> result = otherOutMapper.selectOtherOutListPage(page, query);


        PageDTO<OtherOutListDTO> pageDTO = new PageDTO<>();
        pageDTO.setPageSize(result.getSize());
        pageDTO.setTotal(result.getTotal());
        pageDTO.setPages(result.getPages());
        return JsonVO.success(pageDTO);
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
    private boolean checkPermission() {
        return true;
    }
    /**
     * 记录操作日志
     */
    private void logOperation(String transferId, String operation) {
        // TODO: 实现操作日志记录
        log.info("操作日志：入库单ID: {}, 操作: {}", transferId, operation);
    }


}



