package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 18:15
 * @Description: 库存盘点数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("库存盘点数据对象")
public class InventoryVerifyListDTO {

    @ApiModelProperty(value = "商品名称", example = "刀具")
    private String name;
    @ApiModelProperty(value = "库存数量", example = "122")
    private String totalStock;
    @ApiModelProperty(value = "所在仓库库存数",example = "1号仓库：111,2号仓库：10...")
    private AttrStockDTO attr;
    @ApiModelProperty(value="商品编号",example = "0003")
    private String number;
    @ApiModelProperty(value = "规格型号", example = "DJ-111")
    private String spec;
    @ApiModelProperty(value = "商品分类", example = "五金工具")
    private String category;
    @ApiModelProperty(value = "商品品牌", example = "飞虎")
    private String brand;
    @ApiModelProperty(value = "商品单位", example = "个")
    private String unit;
    @ApiModelProperty(value = "商品条码", example = "1")
    private String code;
    @ApiModelProperty(value = "商品备注", example = "随便")
    private String data;
}
