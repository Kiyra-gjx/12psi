package com.zeroone.star.project.dto.j2.store;


import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.math.BigDecimal;
import java.util.List;

@Data
@ApiModel("商品属性库存对象")
public class AttrStockDTO {

    @ApiModelProperty(value = "商品属性ID（内部使用）", example = "1")
    private Integer id;

    @ApiModelProperty(value = "商品属性名称", example = "8G+128G")
    private String name;

    @ApiModelProperty(value = "商品属性编码", example = "45343453543")
    private String attrCode;

    @ApiModelProperty(value = "该商品属性的总库存(所有仓库库存的合计)", example = "200")
    private BigDecimal totalStock;

    @ApiModelProperty(value = "该属性的仓库库存明细")
    private List<WarehouseStockDTO> warehouses;
}
