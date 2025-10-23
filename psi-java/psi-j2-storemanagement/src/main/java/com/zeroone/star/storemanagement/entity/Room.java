package com.zeroone.star.storemanagement.entity;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

@Data
@ApiModel(description = "仓储信息")
public class Room {
    @ApiModelProperty(value = "id")
    private Integer id;
    @ApiModelProperty(value = "仓库id")
    private Integer warehouse;
    @ApiModelProperty(value = "所属商品id")
    private Integer goods;
    @ApiModelProperty(value = "辅助属性")
    private String attr;
    @ApiModelProperty(value = "库存数量")
    private BigDecimal nums;
}
