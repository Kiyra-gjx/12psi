package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("商品类别")
public class CategoryDataDTO {

    @ApiModelProperty(value = "商品类别id", example = "1")
    private String id;

    @ApiModelProperty(value = "类别名称", example = "默认类别")
    private String name;

}
