package com.zeroone.star.project.dto.j2.store;


import com.fasterxml.jackson.annotation.JsonBackReference;
import com.fasterxml.jackson.annotation.JsonIgnore;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.List;

@Data
@ApiModel("批次单据信息")
public class BatchDocumentDTO {

    @ApiModelProperty(value = "单据详情ID", example = "1")
    private String id;

    @ApiModelProperty(value = "所属批次ID", example = "1")
    private String pid;

    @ApiModelProperty(value = "所属商品ID（内部使用）", example = "1")
    private String goodsId;

    @ApiModelProperty(value = "保质期（天）", example = "365")
    private Integer protectDays;

    @ApiModelProperty(value = "生产日期", example = "2025-10-12")
    private LocalDate produceDate;

    @ApiModelProperty(value = "到期日期", example = "2026-10-12")
    private LocalDate  expireDate;

    @ApiModelProperty(value = "数量", example = "200")
    private BigDecimal nums;

    @JsonIgnore
    private WarehouseStockDTO warehouseStock; // 临时字段，用于XML映射

    @ApiModelProperty(value = "仓库库存明细")
    private List<WarehouseStockDTO> warehouses;
}
