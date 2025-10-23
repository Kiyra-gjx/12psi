package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
/*此dto的所有字段都可以在is_goods表中找到*/
@Data
@ApiModel("商品列表")
public class ShopListDTO {
    @ApiModelProperty(value = "隐藏属性唯一id",required = true , example = "1")
    private int id;
    @ApiModelProperty(value = "商品名称",required = true, example = "刀具")
    private String name;
    @ApiModelProperty(value = "商品编号",required = true, example = "0003")
    private String number;
    @ApiModelProperty(value = "规格标号",required = true, example = "DJ-0001")
    private String spec;
    @ApiModelProperty(value = "商品分类",required = true, example = "五金工具")
    private int category;
    @ApiModelProperty(value = "商品品牌",required = true, example = "飞虎")
    private String brand;
    @ApiModelProperty(value = "商品单位",required = true, example = "个")
    private String unit;
    @ApiModelProperty(value = "采购价格",required = true, example = "2")
    private Double buy;
    @ApiModelProperty(value = "销售价格",required = true, example = "5")
    private Double sell;
    @ApiModelProperty(value = "商品条码",required = true, example = "")
    private String code;
    @ApiModelProperty(value = "备注信息",required = true, example = "null")
    private String data;
}
