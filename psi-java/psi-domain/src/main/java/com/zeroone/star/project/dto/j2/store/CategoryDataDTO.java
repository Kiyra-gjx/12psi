package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("商品类别对象")
public class CategoryDataDTO {

    @ApiModelProperty(value = "商品类别ID", example = "1")
    private Integer id;

    @ApiModelProperty(value = "所属类别ID", example = "0")
    private Integer parentId;

    @ApiModelProperty(value = "类别名称", example = "默认类别")
    private String name;

    @ApiModelProperty(value = "类别排序", example = "1")
    private Integer sort;

    @ApiModelProperty(value = "备注信息", example = "默认类别")
    private String data;
}
