package com.zeroone.star.storemanagement.entity;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

@Data
public class RoomDO {

    private String id;

    private String warehouse;

    private String goods;

    private String attr;

    private BigDecimal nums;
}
