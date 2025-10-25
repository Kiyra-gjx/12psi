package com.zeroone.star.storemanagement.entity;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

@Data
@ApiModel(description = "仓储详情")
public class RoomInfoDO {
    @ApiModelProperty(value = "id")
    private Integer id;
    @ApiModelProperty(value = "所属仓储id")
    private  Integer pid;
    @ApiModelProperty(value = "单据类型")
    private String type;
    @ApiModelProperty(value = "所属类")
    private Integer classify;
    @ApiModelProperty(value = "所属详情")
    private Integer info;
    @ApiModelProperty(value = "单据时间")
    private Integer time;
    @ApiModelProperty(value = "单据方向[0:出库,1:入库]")
    private  String direction;
    @ApiModelProperty(value = "基础单价")
    private BigDecimal price;
    @ApiModelProperty(value = "基础数量")
    private BigDecimal nums;
}
