package com.zeroone.star.storemanagement.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j2.store.BatchDetailDTO;
import com.zeroone.star.project.query.j2.store.BatchDetailQuery;
import com.zeroone.star.storemanagement.entity.BatchDO;
import com.zeroone.star.storemanagement.entity.BatchInfoDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.storemanagement.mapper
 * @Author: 高
 * @CreateTime: 2025-10-24 20:18
 * @Description: 批次查询数据访问层
 * @Version: 1.0
 */
@Mapper
public interface BatchMapper extends BaseMapper<BatchDO> {


}
