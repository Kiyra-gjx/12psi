package com.zeroone.star.storemanagement.service.impl;

import com.alibaba.excel.EasyExcel;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.storemanagement.entity.EntryDO;
import com.zeroone.star.storemanagement.entity.ExtryDO;
import com.zeroone.star.storemanagement.entity.ExtryInfoDO;
import com.zeroone.star.storemanagement.mapper.OtherOutListInfoMapper;
import com.zeroone.star.storemanagement.mapper.OtherOutListMapper;
import com.zeroone.star.storemanagement.service.IOtherOutListService;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;

/**
 * 功能：
 * <p>
 * ——————————————————————————————
 * version   变更日期    修改人
 * ------------------------------
 * v1.0.0    2025/10/26    shark
 * ——————————————————————————————
 * 修改说明：
 *
 * @author: shark
 */

@Service
public class OtherOutListServiceImpl extends ServiceImpl<OtherOutListMapper, ExtryDO> implements IOtherOutListService {

    @Resource
    private OtherOutListMapper otherOutListMapper;
    @Resource
    private OtherOutListInfoMapper otherOutListInfoMapper;

    @Override
    public void examine(List<Integer> ids) {
        //TODO : 待实现关联表的审核逻辑
        ExtryDO extryDO = otherOutListMapper.selectById(ids.get(0));
        if(extryDO != null) {
            update().set("examine", extryDO.getExamine() == 1 ? 0 : 1).eq("id", ids.get(0)).update();
        }
    }

    @Override
    public void check(List<Integer> ids) {
        //TODO : 待实现关联表的核对逻辑
        ExtryDO extryDO = otherOutListMapper.selectById(ids.get(0));
        if(extryDO != null) {
            update().set("`check`", extryDO.getCheck() == 1 ? 0 : 1).eq("id", ids.get(0)).update();
        }
    }

    @Override
    public byte[] exportOrderList(List<Integer> ids) {
        List<ExtryDO> dataList = otherOutListMapper.selectBatchIds(ids);

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
        List<ExtryInfoDO> detailList = otherOutListInfoMapper.selectByMainIds(ids);

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
            otherOutListMapper.insert(entity);
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



