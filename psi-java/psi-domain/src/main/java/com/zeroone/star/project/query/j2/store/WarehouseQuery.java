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
 * @Description: TODO
 * @Version: 1.0
 */
@Data
@ApiModel("仓库查询参数")
public class WarehouseQuery extends PageQuery {
    @ApiModelProperty(value = "仓库名称",example = "1号仓库")
    private String name;
}
