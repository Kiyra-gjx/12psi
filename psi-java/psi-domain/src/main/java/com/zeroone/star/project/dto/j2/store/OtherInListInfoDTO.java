package com.zeroone.star.project.dto.j2.store;

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
@ApiModel("")
public class OtherInListInfoDTO {
    @ApiModelProperty(value = "id", example = "1")
    int id;
    @ApiModelProperty(value = "所属入库单号", example = "1")
    int pid;
    @ApiModelProperty(value = "所属商品", example = "1")
    int goods;
    @ApiModelProperty(value = "辅助属性", example = "1")
    String attr;
    @ApiModelProperty(value = "单位", example = "个")
    String unit;
    @ApiModelProperty(value = "仓库", example = "1")
    int warehouse;
    @ApiModelProperty(value = "批次号", example = "898")
    String batch;
    @ApiModelProperty(value = "生产日期", example = "1760457600")
    int mfd;
    @ApiModelProperty(value = "成本", example = "1.0000")
    float price;
    @ApiModelProperty(value = "数量", example = "1.0000")
    float nums;
    @ApiModelProperty(value = "序列号", example = "1")
    String serial;
    @ApiModelProperty(value = "总成本", example = "1.0000")
    float total;
    @ApiModelProperty(value = "备注信息", example = "1")
    String data;
}
