package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 10:43
 * @Description: 商品列表数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("商品列表数据对象")
public class GoodsListDTO {
    @ApiModelProperty(value = "商品名称", example = "刀具")
    private String name;
    @ApiModelProperty(value = "商品编号", example = "0001")
    private String number;
    @ApiModelProperty(value = "商品类别", example = "1")
    private int category;
    @ApiModelProperty(value = "商品品牌", example = "飞虎")
    private String brand;
    @ApiModelProperty(value = "商品条码", example = "111222")
    private String code;
}
