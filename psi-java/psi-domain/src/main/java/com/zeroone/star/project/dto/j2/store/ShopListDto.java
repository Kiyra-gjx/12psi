package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
@ApiModel("商品列表")
public class ShopListDto {
    @ApiModelProperty(value = "商品名称", example = "刀具")
    private String shopName;
    @ApiModelProperty(value = "商品编号", example = "0003")
    private Integer shopNumber;
    @ApiModelProperty(value = "规格标号", example = "DJ-0001")
    private String Spec;
    @ApiModelProperty(value = "商品分类", example = "五金工具")
    private String shopClass;
    @ApiModelProperty(value = "商品品牌", example = "飞虎")
    private String shopBrand;
    @ApiModelProperty(value = "商品单位", example = "个")
    private String shopUnit;
    @ApiModelProperty(value = "采购价格", example = "2")
    private Double purchasePrice;
    @ApiModelProperty(value = "销售价格", example = "5")
    private Double salePrice;
    @ApiModelProperty(value = "商品条码", example = "")
    private String shopBarCode;
    @ApiModelProperty(value = "备注信息", example = "null")
    private String Remark;
}
