package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 19:04
 * @Description: TODO
 * @Version: 1.0
 */
@Data
@ApiModel("其他出库单数据信息对象")
public class OtherOutListInfoDTO {
    @ApiModelProperty(value = "id", example = "1")
    private String id;
    @ApiModelProperty(value = "所属出库单ID", example = "1")
    private String pid;
    @ApiModelProperty(value = "所属商品", example = "1")
    private String goods;
    @ApiModelProperty(value = "辅助属性", example = "红色,L码")
    private String attr;
    @ApiModelProperty(value = "单位", example = "个")
    private String unit;
    @ApiModelProperty(value = "仓库", example = "1")
    private String warehouse;
    @ApiModelProperty(value = "批次号", example = "B20231019001")
    private String batch;
    @ApiModelProperty(value = "生产日期", example = "2023-10-18T18:18:00")
    private long mfd;
    @ApiModelProperty(value = "成本", example = "10.00")
    private BigDecimal price;
    @ApiModelProperty(value = "数量", example = "100")
    private BigDecimal nums;
    @ApiModelProperty(value = "序列号", example = "SN001,SN002")
    private String serial;
    @ApiModelProperty(value = "总成本", example = "1000.00")
    private BigDecimal total;
    @ApiModelProperty(value = "备注信息", example = "备注")
    private String data;
}
