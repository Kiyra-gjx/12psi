package com.zeroone.star.storemanagement.service.impl;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchDetailDTO;
import com.zeroone.star.project.query.j2.store.BatchDetailQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.mapper.BatchMapper;
import com.zeroone.star.storemanagement.service.IBatchService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.service.impl
 * @Author: 高
 * @CreateTime: 2025-10-24 20:16
 * @Description: TODO
 * @Version: 1.0
 */
@Service
public class BatchServiceImpl implements IBatchService {

    @Resource
    private BatchMapper batchMapper;

    /**
     * 获取指定批次详情数据
     * @param batchDetailQuery
     * @return
     */
    public PageDTO<BatchDetailDTO> getBatchDetail(BatchDetailQuery batchDetailQuery) {
        // 调用mapper层获取批次详情列表数据
        List<BatchDetailDTO> batchDetailList = batchMapper.getBatchDetail(batchDetailQuery);
        // 为每个批次详情设置所属组织
        // TODO: 后续可以通过其他方式获取实际的组织数据，目前使用默认值
        for (BatchDetailDTO dto : batchDetailList) {
            dto.setFrame("默认组织"); // 设置默认组织名称
        }
        // 获取符合条件的总数
        long total = batchMapper.getBatchDetailCount(batchDetailQuery);
        PageDTO<BatchDetailDTO> pageDTO = new PageDTO<>();
        // 设置数据列表
        pageDTO.setRows(batchDetailList);
        // 设置总数
        pageDTO.setTotal(total);
        // 计算总页数
        long pages = 0;
        if (batchDetailQuery.getPageSize() > 0) {
            pages = (total + batchDetailQuery.getPageSize() - 1) / batchDetailQuery.getPageSize();
        }
        // 设置分页信息
        pageDTO.setPages(pages);
        pageDTO.setPageIndex(batchDetailQuery.getPageIndex());
        pageDTO.setPageSize(batchDetailQuery.getPageSize());
        return pageDTO;
    }
}
