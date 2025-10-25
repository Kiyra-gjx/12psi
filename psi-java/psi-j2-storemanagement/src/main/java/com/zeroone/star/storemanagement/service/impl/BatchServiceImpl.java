package com.zeroone.star.storemanagement.service.impl;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchDetailDTO;
import com.zeroone.star.project.query.j2.store.BatchDetailQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.mapper.BatchMapper;
import com.zeroone.star.storemanagement.service.IBatchService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

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
    @Override
    public JsonVO<PageDTO<BatchDetailDTO>> getBatchDetail(BatchDetailQuery batchDetailQuery) {
        PageDTO<BatchDetailDTO> batchDetailDTOPageDTO = batchMapper.getBatchDetail(batchDetailQuery);
        return JsonVO.success(batchDetailDTOPageDTO);
    }
}
