package com.zeroone.star.project.dto.j2.store;

import com.alibaba.excel.annotation.ExcelProperty;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 13:53
 * @Description: TODO
 * @Version: 1.0
 */
@Data
@ApiModel("其他入库单数据信息对象")
public class OtherInListInfoDTO {
    @ApiModelProperty(value = "id", example = "1")
    int id;

    @ApiModelProperty(value = "所属入库单号", example = "1")
    int pid;

    @ExcelProperty(value = "商品名称", index = 0)
    @ApiModelProperty(value = "所属商品", example = "1")
    int goods;

    @ExcelProperty(value = "辅助属性", index = 2)
    @ApiModelProperty(value = "辅助属性", example = "1")
    String attr;

    @ExcelProperty(value = "单位", index = 3)
    @ApiModelProperty(value = "单位", example = "个")
    String unit;

    @ExcelProperty(value = "仓库", index = 4)
    @ApiModelProperty(value = "仓库", example = "1")
    int warehouse;

    @ApiModelProperty(value = "批次号", example = "898")
    String batch;

    @ApiModelProperty(value = "生产日期", example = "1760457600")
    int mfd;

    @ExcelProperty(value = "成本", index = 5)
    @ApiModelProperty(value = "成本", example = "1.0000")
    float price;

    @ExcelProperty(value = "数量", index = 6)
    @ApiModelProperty(value = "数量", example = "1.0000")
    float nums;

    @ExcelProperty(value = "规格型号", index = 1)
    @ApiModelProperty(value = "序列号", example = "1")
    String serial;

    @ExcelProperty(value = "总成本", index = 7)
    @ApiModelProperty(value = "总成本", example = "1.0000")
    float total;

    @ExcelProperty(value = "备注信息", index = 8)
    @ApiModelProperty(value = "备注信息", example = "1")
    String data;
}
