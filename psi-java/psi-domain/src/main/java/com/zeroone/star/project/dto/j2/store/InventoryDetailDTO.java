package com.zeroone.star.project.dto.j2.store;

import com.alibaba.excel.annotation.ExcelProperty;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 10:46
 * @Description: 商品库存详情数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("商品库存详情数据对象")
public class InventoryDetailDTO {

    @ExcelProperty(value = "所属组织", index = 0)
    @ApiModelProperty(value = "所属组织名称", example = "默认组织")
    private String frameName;

    @ExcelProperty(value = "操作时间", index = 1)
    @ApiModelProperty(value = "操作时间戳",example = "1690000000000")
    private Long time;

    @ExcelProperty(value = "单据类型", index = 2)
    @ApiModelProperty(value = "单据类型", example = "采购单")
    private String type;

    @ExcelProperty(value = "单据编号", index = 3)
    @ApiModelProperty(value = "单据编号", example = "PUR-20231001")
    private String number;

    @ExcelProperty(value = "操作类型", index = 4)
    @ApiModelProperty(
            value = "操作类型[0:出库|1:入库]",
            example = "1")
    private Integer direction;

    @ExcelProperty(value = "操作数量", index = 5)
    @ApiModelProperty(value = "操作数量", example = "10")
    private BigDecimal nums;
}
