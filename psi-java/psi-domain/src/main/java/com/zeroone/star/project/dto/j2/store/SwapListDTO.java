package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

@Data
@ApiModel("调拨单详细")
public class SwapListDTO {
    @ApiModelProperty(value = "查询后数据的id", example = "1")
    private Integer id;
    @ApiModelProperty(value = "商品名称", example = "刀具")
    private String shopName;
    @ApiModelProperty(value = "商品编号", example = "0003")
    private Integer shopNumber;
    @ApiModelProperty(value = "规格标号", example = "DJ-0001")
    private String Spec;
    @ApiModelProperty(value = "辅助属性", example = "null")
    private String Attr;
    @ApiModelProperty(value = "单位", example = "null")
    private String Unit;
    @ApiModelProperty(value = "调出仓库", example = "null")
    private String OutWarehouse;
    @ApiModelProperty(value = "调入仓库", example = "null")
    private String InWarehouse;
    @ApiModelProperty(value = "批次号", example = "1")
    private Integer Batch;
    @ApiModelProperty(value = "生产日期", example = "2025-10-18")
    private LocalDate ProductDate;
    @ApiModelProperty(value = "成本", example = "2")
    private Double Cost;
    @ApiModelProperty(value = "数量", example = "1")
    private Integer Number;
    @ApiModelProperty(value = "总成本", example = "2")
    private Double TotalCost;
    @ApiModelProperty(value = "备注信息", example = "null")
    private String Remark;

}
