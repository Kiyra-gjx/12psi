package com.zeroone.star.project.dto.j2.store;


import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.util.List;


@Data
@ApiModel("批次信息详细对象")
public class BatchStockDetailDTO {

    @ApiModelProperty(value = "批次id", example = "1")
    private Integer batchId;

    @ApiModelProperty(value = "批次名称", example = "-")
    private String name;

    @ApiModelProperty(value = "所属仓储id", example = "1")
    private Integer roomId;

    @ApiModelProperty(value = "所属仓库id", example = "1")
    private Integer warehouseId;

    @ApiModelProperty(value = "所属商品id", example = "1")
    private Integer goodsId;

    @ApiModelProperty(value = "批次号", example = "76e8040f0bdfd03f")
    private String batchKey;

    @ApiModelProperty(value = "保质期", example = "365")
    private Integer protect;

    @ApiModelProperty(value = "生产日期", example = "2025-10-01")
    private String productDate;

    @ApiModelProperty(value = "过期日期", example = "2026-10-01")
    private String expiryDate;

    @ApiModelProperty(value = "批次详情总库存", example = "300")
    private BigDecimal totalStock;

    @ApiModelProperty(value = "仓库库存明细")
    private List<WarehouseStockDTO> warehouses;


}
