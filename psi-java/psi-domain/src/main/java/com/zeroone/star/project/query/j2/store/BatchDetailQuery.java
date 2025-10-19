package com.zeroone.star.project.query.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.query.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 10:41
 * @Description: 批次查询详情参数对象
 * @Version: 1.0
 */
@Data
@ApiModel("批次查询详情参数")
public class BatchDetailQuery {
    @ApiModelProperty(value = "单据编号", example = "QTRKD2510181347194")
    private String number;
    @ApiModelProperty(value = "单据类型", example = "采购单")
    private String type;
    @ApiModelProperty(value = "开始日期", example = "")
    private String startDate;
    @ApiModelProperty(value = "结束日期", example = "")
    private String endDate;
}
