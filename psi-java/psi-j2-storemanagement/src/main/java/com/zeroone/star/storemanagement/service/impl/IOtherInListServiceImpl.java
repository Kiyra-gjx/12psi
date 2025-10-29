package com.zeroone.star.storemanagement.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDTO;
import com.zeroone.star.project.query.j2.store.OtherInQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.storemanagement.mapper.OtherInMapper;
import com.zeroone.star.storemanagement.service.IOtherInListService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

@Service
@Slf4j
public class IOtherInListServiceImpl implements IOtherInListService {

    @Resource
    private OtherInMapper otherInMapper;

    /**
     * 获取其他入库单列表（条件查询+分页）
     * @param query 查询参数对象
     * @return 包含分页数据的JsonVO对象
     */
    @Override
    public JsonVO<PageDTO<OtherInListDTO>> getOtherInList(OtherInQuery query) {
        // 创建分页对象
        Page<OtherInListDTO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        // 调用mapper进行分页查询
        Page<OtherInListDTO> result = otherInMapper.selectOtherInListPage(page, query);
        // 构建返回的分页数据对象
        PageDTO<OtherInListDTO> pageDTO = new PageDTO<>();
        pageDTO.setTotal(result.getTotal());
        pageDTO.setRows(result.getRecords());
        pageDTO.setPageSize(result.getSize());
        // 返回成功响应
        return JsonVO.success(pageDTO);
    }
}