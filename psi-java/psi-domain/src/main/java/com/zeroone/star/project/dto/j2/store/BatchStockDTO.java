package com.zeroone.star.project.dto.j2.store;


import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.util.List;

@Data
@ApiModel("批次信息对象")
public class BatchStockDTO {

    @ApiModelProperty(value = "所属商品id", example = "1")
    private Integer goodsId;

    @ApiModelProperty(value = "商品名称")
    private String name;

    @ApiModelProperty(value = "批次信息详情")
    private List<BatchStockDetailDTO> batchStockDetail;

    @ApiModelProperty(value = "批次总库存数量（所有仓库的合计）", example = "200")
    private BigDecimal totalStock;

    @ApiModelProperty(value = "该批次的仓库库存明细")
    private List<WarehouseStockDTO> warehouses;
}
