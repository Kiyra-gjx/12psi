package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.math.BigDecimal;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 18:17
 * @Description: 挑拨单详情数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("挑拨单详情数据对象")
public class TransferDetailDTO {
    @ApiModelProperty(value = "调拨单ID", required = true, example = "1")
    private Integer id;

    @ApiModelProperty(value = "调出仓库", example = "1号仓库")
    private String warehouse;

    @ApiModelProperty(value = "调入仓库", example = "2号仓库")
    private String storehouse;

    @ApiModelProperty(value = "成本", example = "998.00")
    private BigDecimal cost;

    @ApiModelProperty(value = "数量", example = "1.00")
    private BigDecimal nums;

    @ApiModelProperty(value = "备注信息", example = "紧急调拨")
    private String remark;
}
