package com.zeroone.star.project.dto.j2.store;


import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

@Data
@ApiModel("单据信息")
public class CostDataDTO {

    @ApiModelProperty(value = "操作时间", example = "2025-10-15")
    private LocalDate time;

    @ApiModelProperty(value = "单据ID", example = "1")
    private String id;

    @ApiModelProperty(value = "单据编号", example = "ZCGD2510151056420")
    private String number;

    @ApiModelProperty(value = "组织信息")
    private FrameDataDTO frameData;

}
