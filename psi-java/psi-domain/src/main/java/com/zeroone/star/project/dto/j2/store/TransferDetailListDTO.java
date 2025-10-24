package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.math.BigDecimal;

@Data
@ApiModel("调拨单详细")
/*除额外标注，其余字段都能在swap_info表里找到*/
public class TransferDetailListDTO {
    @ApiModelProperty(value = "隐藏属性唯一id",required = true , example = "1")
    private String id;
    @ApiModelProperty(value = "商品名称，goods表里",required = true, example = "刀具")
    private String name;
    @ApiModelProperty(value = "商品编号，goods表里",required = true, example = "0003")
    private String number;
    @ApiModelProperty(value = "规格型号，goods表里",required = true, example = "DJ-0001")
    private String spec;
    @ApiModelProperty(value = "辅助属性",required = true, example = "null")
    private String attr;
    @ApiModelProperty(value = "单位", required = true , example = "null")
    private String unit;
    @ApiModelProperty(value = "调出仓库",required = true, example = "null")
    private String warehouse;
    @ApiModelProperty(value = "调入仓库",required = true, example = "null")
    private String storehouse;
    @ApiModelProperty(value = "成本",required = true,example = "2")
    private BigDecimal price;
    @ApiModelProperty(value = "数量",required = true, example = "1")
    private BigDecimal nums;
    @ApiModelProperty(value = "总成本",required = true, example = "2")
    private BigDecimal total;
    @ApiModelProperty(value = "备注信息", example = "null")
    private String data;

}
