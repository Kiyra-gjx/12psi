package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 18:13
 * @Description: 批次查询详情数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("批次查询详情数据对象")
public class BatchDetailDTO {
    @ApiModelProperty(value = "所属组织", example = "默认组织")
    private String name;
    @ApiModelProperty(value = "操作时间", example = "2025-10-18")
    private int time;
    @ApiModelProperty(value = "单据类型", example = "其他入库单")
    private String type;
    @ApiModelProperty(value = "单据编号", example = "QTRKD2510181347194")
    private String number;
    @ApiModelProperty(value = "操作类型", example = "增加")
    private String operation;
    @ApiModelProperty(value = "操作数量", example = "1")
    private int nums;
}
