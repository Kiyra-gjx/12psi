package com.zeroone.star.project.query.j2.store;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.query.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 18:10
 * @Description: 调拨单查询参数对象
 * @Version: 1.0
 */
@Data
@ApiModel("调拨单查询参数对象(查询调拨单的参数)")
public class TransferQuery extends PageQuery {
    @ApiModelProperty(value = "商品名称", example = "刀具")
    private String name;
    @ApiModelProperty(value = "商品编号",example = "0003")
    private String number;
    @ApiModelProperty(value = "起始日期",required = true, example = "2025-10-18")
    private int startTime;
    @ApiModelProperty(value = "截止日期",required = true, example = "2025-10-18")
    private int endTime;
    @ApiModelProperty(value = "客户,需要关联映射", example ="")
    private String customerName;
    @ApiModelProperty(value = "关联人员", example = "")
    private int people;
    @ApiModelProperty(value = "单据类型", example = "")
    private String type;
    @ApiModelProperty(value = "审核状态", example = "未审核")
    private int examine;
    @ApiModelProperty(value = "费用状态", example = "无需结算")
    private int cse;
    @ApiModelProperty(value = "核对状态[0:未核对|1:已核对]", example = "0")
    private Integer check;
    @ApiModelProperty(value = "制单人", example = "")
    private int user;
    @ApiModelProperty(value = "备注信息", example = "")
    private String data;
}
