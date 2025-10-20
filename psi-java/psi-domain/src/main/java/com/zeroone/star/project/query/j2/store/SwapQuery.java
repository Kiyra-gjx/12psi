package com.zeroone.star.project.query.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;

@Data
@ApiModel("调拨单查询结果")
public class SwapQuery {
    @ApiModelProperty(value = "所属组织", example = "默认组织")
    private String organization;
    @ApiModelProperty(value = "单据时间", example = "2025-10-18")
    private LocalDate ProductDate;
    @ApiModelProperty(value = "单据编号", example = "DJ20251018001")
    private String number;
    @ApiModelProperty(value = "单据成本", example = "12")
    private Double Cost;
    @ApiModelProperty(value = "单据费用", example = "0")
    private Double Expense;
    @ApiModelProperty(value = "关联人员", example = "")
    private String RelatedPerson;
    @ApiModelProperty(value = "审核状态", example = "未审核")
    private String AuditStatus;
    @ApiModelProperty(value = "费用状态", example = "无需结算")
    private String ExpenseStatus;
    @ApiModelProperty(value = "制单人", example = "管理员")
    private String Maker;
    @ApiModelProperty(value = "备注信息", example = "")
    private String Remark;


}
