package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

@Data
@ApiModel(description = "仓储信息")
@TableName("room")
public class RoomDO {
    @ApiModelProperty(value = "id")
    private String id;
    @ApiModelProperty(value = "仓库id")
    private String warehouse;
    @ApiModelProperty(value = "所属商品id")
    private String goods;
    @ApiModelProperty(value = "辅助属性")
    private String attr;
    @ApiModelProperty(value = "库存数量")
    private BigDecimal nums;
}
