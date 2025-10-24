package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("商品类别")
public class CategoryDataDTO {

    @ApiModelProperty(value = "商品类别id", example = "1")
    private Integer id;

    @ApiModelProperty(value = "所属类别", example = "0")
    private Integer pid;

    @ApiModelProperty(value = "类别名称", example = "默认类别")
    private String name;

    @ApiModelProperty(value = "类别排序", example = "1")
    private Integer sort;

    @ApiModelProperty(value = "备注信息", example = "")
    private String data;
}
