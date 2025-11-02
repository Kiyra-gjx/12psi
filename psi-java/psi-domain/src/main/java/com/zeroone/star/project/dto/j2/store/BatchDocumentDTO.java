package com.zeroone.star.project.dto.j2.store;


import com.fasterxml.jackson.annotation.JsonBackReference;
import com.fasterxml.jackson.annotation.JsonIgnore;
import io.swagger.annotations.Api;
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
    @ApiModelProperty(value = "批次ID")
    private String batchId;

    @ApiModelProperty(value = "仓库名称")
    private String warehouseName;

    @ApiModelProperty(value = "生产日期")
    private LocalDate productDate;

    @ApiModelProperty(value = "过期日期")
    private LocalDate expireDate;

    @ApiModelProperty(value = "库存数量")
    private BigDecimal nums;

    @ApiModelProperty(value = "是否预警")
    @JsonIgnore
    private Boolean isWarning;

    @ApiModelProperty(value = "商品ID",hidden = true)
    @JsonIgnore
    private String goodsId;

    @ApiModelProperty(value = "属性名称", hidden = true)
    @JsonIgnore
    private String attrName;

    @ApiModelProperty(value = "批次号",hidden = true)
    @JsonIgnore
    private String batchNumber;


}
