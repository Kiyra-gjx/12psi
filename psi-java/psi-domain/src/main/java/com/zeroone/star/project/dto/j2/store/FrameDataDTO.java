package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("组织信息")
public class FrameDataDTO {

    @ApiModelProperty(value = "组织ID", example = "1")
    private String id;

    @ApiModelProperty(value = "组织名称", example = "默认组织")
    private String name;
}
