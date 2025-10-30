package com.zeroone.star.project.dto.j2.store;


import com.fasterxml.jackson.annotation.JsonIgnore;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

import java.time.LocalDateTime;
import java.util.List;

@Data
@ApiModel("批次号对象")
public class BatchNumberDTO {

    @ApiModelProperty(value = "批次号ID", example = "22")
    private String batchId;

    @ApiModelProperty(value = "所属仓储ID（内部使用）", example = "1")
    private String room;

    @ApiModelProperty(value = "所属商品ID（内部使用）", example = "1")
    private String goodsId;

    @ApiModelProperty(value = "批次号", example = "BATCH20241018001")
    private String batchNumber;

    @ApiModelProperty(value = "生产日期", example = "2025-10-12")
    private LocalDateTime createTime;

    @ApiModelProperty(value = "库存数量", example = "100")
    private BigDecimal nums;

    @JsonIgnore
    private WarehouseStockDTO warehouseStock; // 临时字段，用于XML映射

    @ApiModelProperty(value = "批次在各个仓库的库存分布")
    private List<WarehouseStockDTO> warehouses;

    @ApiModelProperty(value = "批次单据子项列表")
    private List<BatchDocumentDTO> batchDocuments;
}
