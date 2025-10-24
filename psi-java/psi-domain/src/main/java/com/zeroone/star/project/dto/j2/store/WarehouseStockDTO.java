package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

@Data
@ApiModel("存储信息对象")
public class WarehouseStockDTO {

    @ApiModelProperty(value = "所属存储ID", example = "1")
    private Integer storedRecordId;

    @ApiModelProperty(value = "所属仓库ID", example = "1")
    private Integer warehouseId;

    @ApiModelProperty(value = "所属仓库名称", example = "上海仓库")
    private String warehouseName;

    @ApiModelProperty(value = "所属商品ID（内部使用）", example = "1")
    private Integer goodsId;

    @ApiModelProperty(value = "商品辅助属性ID（内部使用）", example = "1")
    private Integer attrId;

    @ApiModelProperty(value = "库存数量", example = "100")
    private BigDecimal stockNum;

}
