package com.zeroone.star.storemanagement.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.InventoryDetailDTO;
import com.zeroone.star.project.query.j2.store.InventoryDetailQuery;
import com.zeroone.star.storemanagement.mapper.InventoryDetailMapper;
import com.zeroone.star.storemanagement.service.IInventoryDetailService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

/**
 * （已弃用）
 */
@Service
@Slf4j
public class InventoryDetailServiceImpl implements IInventoryDetailService {
    @Resource
    private InventoryDetailMapper inventoryDetailMapper;

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
