package com.zeroone.star.project.dto.j2.store;

import com.alibaba.excel.annotation.ExcelProperty;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDateTime;

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
    @ApiModelProperty(value = "商品名称", example = "牛奶")
    private String name;

    @ApiModelProperty(value = "商品编号", example = "0001")
    private String number;

    @ApiModelProperty(value = "规格型号", example = "500ml")
    private String spec;

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

    @ApiModelProperty(value = "生产日期", example = "2023-10-18 18:18:00")
    private LocalDateTime mfd;

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
