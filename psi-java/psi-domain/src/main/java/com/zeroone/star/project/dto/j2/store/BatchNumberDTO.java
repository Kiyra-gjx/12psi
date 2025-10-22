package com.zeroone.star.project.dto.j2.store;


import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonManagedReference;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.util.List;

@Data
@ApiModel("批次号对象")
public class BatchNumberDTO {

    @ApiModelProperty(value = "批次号ID", example = "22")
    private Integer id;

    @ApiModelProperty(value = "批次号", example = "BATCH20241018001")
    private String batchNumber;

    @ApiModelProperty(value = "总库存", example = "300")
    private BigDecimal totalStock;

    @ApiModelProperty(value = "批次单据信息列表")
    private List<BatchDocumentDTO> batchDocuments;

    @ApiModelProperty(value = "仓库库存明细")
    private List<WarehouseStockDTO> warehouses;
}
