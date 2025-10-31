package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.math.BigDecimal;
import java.util.List;

@Data
@ApiModel("批次号对象")
public class BatchNumberDTO {

    @ApiModelProperty(value = "批次号", example = "BATCH001")
    private String batchNumber;

    @ApiModelProperty(value = "库存数量", example = "300")
    private BigDecimal totalStock;

    @ApiModelProperty(value = "商品ID", example = "1")
    private String goodsId;

    @ApiModelProperty(value = "批次详细对象")
    List<BatchDocumentDTO> batchDocuments;

}
