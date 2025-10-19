package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

@Data
@ApiModel("仓库库存对象")
public class WarehouseStockDTO {

    @ApiModelProperty(value = "仓库ID", example = "1")
    private String warehouseId;

    @ApiModelProperty(value = "仓库名称", example = "上海仓库")
    private String warehouseName;

    @ApiModelProperty(value = "所属组织id", example = "1")
    private Integer frameId;

    @ApiModelProperty(value = "所属组织名称", example = "默认组织")
    private Integer frameName;

    @ApiModelProperty(value = "库存数量", example = "100")
    private BigDecimal stockNum;


}
