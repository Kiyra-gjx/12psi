package com.zeroone.star.project.dto.j2.store;


import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.util.List;

@Data
@ApiModel("批次号对象")
public class BatchNumberDTO {

    @ApiModelProperty(value = "批次号ID", example = "1")
    private Integer id;

    @ApiModelProperty(value = "批次号", example = "123445")
    private Integer batch;

    @ApiModelProperty(value = "总库存", example = "300")
    private BigDecimal totalStock;

    @ApiModelProperty(value = "批次信息")
    private List<BatchDocumentDTO> batchDocuments;

    @ApiModelProperty(value = "库存详情")
    private List<WarehouseStockDTO> warehouses;
}
