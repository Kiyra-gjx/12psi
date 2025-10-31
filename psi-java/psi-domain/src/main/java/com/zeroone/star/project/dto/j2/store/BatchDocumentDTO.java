package com.zeroone.star.project.dto.j2.store;


import com.fasterxml.jackson.annotation.JsonBackReference;
import com.fasterxml.jackson.annotation.JsonIgnore;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;

@Data
@ApiModel("批次详细对象")
public class BatchDocumentDTO {
    @ApiModelProperty(value = "批次号ID", example = "22")
    private String batchId;

    @ApiModelProperty(value = "所属仓储ID（", example = "1")
    private String room;

    @ApiModelProperty(value = "所属仓库ID", example = "1")
    private String warehouse;

    @ApiModelProperty(value = "所属仓库名称", example = "主仓库")
    private String warehouseName;

    @ApiModelProperty(value = "所属商品ID", example = "1")
    private String goodsId;

    @ApiModelProperty(value = "批次号", example = "BATCH20241018001")
    private String batchNumber;

    @ApiModelProperty(value = "生产日期", example = "2025-10-12")
    private LocalDateTime productDate;

    @ApiModelProperty(value = "库存数量", example = "100")
    private BigDecimal nums;

}
