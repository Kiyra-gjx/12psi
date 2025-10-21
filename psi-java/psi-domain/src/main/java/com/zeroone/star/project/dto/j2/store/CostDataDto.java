package com.zeroone.star.project.dto.j2.store;


import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import io.swagger.models.auth.In;
import lombok.Data;

@Data
@ApiModel("单据信息")
public class CostDataDto{

    @ApiModelProperty(value = "单据ID", example = "1")
    private Integer id;

    @ApiModelProperty(value = "所属组织id（内部使用）", example = "1")
    private Integer frameId;

    @ApiModelProperty(value = "单据类型", example = "采购单")
    private String type;

    @ApiModelProperty(value = "单据时间", example = "2025-10-15")
    private String time;

    @ApiModelProperty(value = "单据编号", example = "ZCGD2510151056420")
    private String number;

    @ApiModelProperty(value = "组织信息")
    private FrameDataDto frameData;

}
