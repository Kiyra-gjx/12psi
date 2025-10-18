package com.zeroone.star.project.query.j2.store;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.query.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 10:37
 * @Description: 批次查询参数对象
 * @Version: 1.0
 */
@Data
@ApiModel("批次查询参数")
public class BatchQuery extends PageQuery {
    @ApiModelProperty(value = "商品名称",example = "刀具")
    private String name;
}
