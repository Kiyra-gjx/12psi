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
    @ApiModelProperty(value = "所属商品", example = "1")
    private int goods;

    @ApiModelProperty(value = "辅助属性", example = "1")
    private String attr;

    @ApiModelProperty(value = "单位", example = "个")
    private String unit;

    @ApiModelProperty(value = "仓库", example = "1")
    private int warehouse;

    @ApiModelProperty(value = "批次号", example = "898")
    private String batch;

    @ApiModelProperty(value = "生产日期", example = "1760457600")
    private int mfd;

    @ApiModelProperty(value = "成本", example = "1.0000")
    private float price;

    @ApiModelProperty(value = "数量", example = "1.0000")
    private float nums;

    @ApiModelProperty(value = "序列号", example = "1")
    private String serial;

    @ApiModelProperty(value = "总成本", example = "1.0000")
    private float total;

    @ApiModelProperty(value = "备注信息", example = "1")
    private String data;
}
