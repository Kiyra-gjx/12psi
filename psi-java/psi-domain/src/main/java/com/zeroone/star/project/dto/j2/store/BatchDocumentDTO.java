package com.zeroone.star.project.dto.j2.store;


import com.fasterxml.jackson.annotation.JsonBackReference;
import com.fasterxml.jackson.annotation.JsonIgnore;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.util.List;

@Data
@ApiModel("批次单据信息")
public class BatchDocumentDTO {

    @ApiModelProperty(value = "批次ID", example = "22")
    private Integer id;

    @ApiModelProperty(value = "名称")
    private String name;

    @ApiModelProperty(value = "保质期", example = "365")
    private Integer protect;

    @ApiModelProperty(value = "生产日期", example = "2025-10-12")
    private String produceDate;

    @ApiModelProperty(value = "到期日期", example = "2026-10-12")
    private String expireDate;

    @ApiModelProperty(value = "总库存数量", example = "200")
    private BigDecimal totalStock;


    @ApiModelProperty(value = "仓库库存明细")
    private List<WarehouseStockDTO> warehouses;
}
