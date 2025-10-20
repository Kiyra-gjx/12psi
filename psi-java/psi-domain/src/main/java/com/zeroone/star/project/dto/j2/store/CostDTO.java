package com.zeroone.star.project.dto.j2.store;

import com.fasterxml.jackson.annotation.JsonProperty;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 13:52
 * @Description: TODO
 * @Version: 1.0
 */
@Data
@ApiModel("")
public class CostDTO {
    @ApiModelProperty(value = "id", example = "1")
    int id;
    @ApiModelProperty(value = "单据类型", example = "entry")
    String type;
    @ApiModelProperty(value = "所属入库单号", example = "1")
    @JsonProperty("class")
    int clazz;
    @ApiModelProperty(value = "单据时间", example = "1760457600")
    int time;
    @ApiModelProperty(value = "所属收支", example = "5")
    int iet;
    @ApiModelProperty(value = "金额", example = "11.0000")
    float money;
    @ApiModelProperty(value = "备注", example = "1")
    String data;
    @ApiModelProperty(value = "结算金额", example = "0.0000")
    float settle;
    @ApiModelProperty(value = "结算状态", example = "1")
    int state;

}
