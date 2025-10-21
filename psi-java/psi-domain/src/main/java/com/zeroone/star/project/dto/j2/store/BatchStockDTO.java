package com.zeroone.star.project.dto.j2.store;


import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.List;

@Data
@ApiModel("商品批次库存对象")
public class BatchStockDTO {

    @ApiModelProperty(value = "商品批次id（内部使用）", example = "1")
    private Integer batchId;

    @ApiModelProperty(value = "所属仓储id", example = "1")
    private Integer roomId;

    @ApiModelProperty(value = "所属仓库id", example = "1")
    private Integer warehouseId;

    @ApiModelProperty(value = "所属商品id", example = "1")
    private Integer goodsId;

    @ApiModelProperty(value = "批次号", example = "20251001")
    private String batchName;

    @ApiModelProperty(value = "生产日期", example = "2025-10-01")
    private LocalDate productDate;

    @ApiModelProperty(value = "过期日期（生产日期+保质期）", example = "2026-10-01")
    private Integer expiryDate;

    @ApiModelProperty(value = "批次总库存数量（所有仓库的合计）", example = "200")
    private BigDecimal totalStock;

    @ApiModelProperty(value = "该批次的仓库库存明细")
    private List<WarehouseStockDTO> warehouses;
}
