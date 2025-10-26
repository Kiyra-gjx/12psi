package com.zeroone.star.storemanagement.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.InventoryDetailDTO;
import com.zeroone.star.project.query.j2.store.InventoryDetailQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.mapper.InventoryDetailMapper;
import com.zeroone.star.storemanagement.service.IInventoryDetailService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
@Service
@Slf4j
public class IInventoryDetailServiceImpl implements IInventoryDetailService {
    @Resource
    private InventoryDetailMapper inventoryDetailMapper;

    @Override
    public JsonVO<PageDTO<InventoryDetailDTO>> getInventoryDetail(InventoryDetailQuery query) {
        try {
            if (query.getGoodsId() == null) {
                log.info("商品id不能为null");
                return JsonVO.fail(null);
            }

            Page<InventoryDetailDTO> page = new Page<>(query.getPageIndex(), query.getPageSize());
            Page<InventoryDetailDTO> resultPage = inventoryDetailMapper.selectInventoryDetailList(page, query);

            return JsonVO.success(PageDTO.create(resultPage));
        } catch (Exception e) {
            log.error("获取库存详情失败", e);
            return JsonVO.fail(null);
        }
    }
}
