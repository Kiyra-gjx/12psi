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
    private String shopName;
    @ApiModelProperty(value = "商品编号", example = "0003")
    private Integer shopNumber;
    @ApiModelProperty(value = "起始日期", example = "2025-10-18")
    private LocalDate StartDate;
    @ApiModelProperty(value = "截止日期", example = "2025-10-18")
    private LocalDate EndDate;
    @ApiModelProperty(value = "客户", example ="")
    private String Customer;
    @ApiModelProperty(value = "关联人员", example = "")
    private String RelatedPerson;
    @ApiModelProperty(value = "单据类型", example = "")
    private String DocumentType;
    @ApiModelProperty(value = "审核状态", example = "")
    private String AuditStatus;
    @ApiModelProperty(value = "费用状态", example = "")
    private String ExpenseStatus;
    @ApiModelProperty(value = "核对状态", example = "")
    private String CheckStatus;
    @ApiModelProperty(value = "制单人", example = "")
    private String Maker;
    @ApiModelProperty(value = "备注信息", example = "")
    private String Remark;
}
