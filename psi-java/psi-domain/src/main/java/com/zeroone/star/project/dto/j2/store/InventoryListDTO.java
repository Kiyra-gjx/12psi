package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 10:43
 * @Description: 库存查询数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("库存查询数据对象")
public class InventoryListDTO {
    @ApiModelProperty(value = "商品名称", example = "刀具")
    private String name;
    @ApiModelProperty(value = "库存数量", example = "1")
    private BigDecimal nums;
    @ApiModelProperty(value = "所属仓库", example = "1")
    private int warehouse;
    @ApiModelProperty(value = "预警阀值", example = "30")
    private Integer threshold;
    @ApiModelProperty(value = "商品编号", example = "0001")
    private String number;
    @ApiModelProperty(value = "规格型号", example = "DJ-001")
    private String spec;
    @ApiModelProperty(value = "商品类别", example = "1")
    private int category;
    @ApiModelProperty(value = "商品品牌", example = "飞虎")
    private String brand;
    @ApiModelProperty(value = "商品单位", example = "个")
    private String unit;
    @ApiModelProperty(value = "商品条码", example = "111222")
    private String code;
    @ApiModelProperty(value = "备注信息", example = "")
    private String data;
}
