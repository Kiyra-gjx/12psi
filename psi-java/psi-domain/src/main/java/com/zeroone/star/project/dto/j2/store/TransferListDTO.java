package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 18:17
 * @Description: 调拨单数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("调拨单数据对象（调拨单查询结果）")
/**除额外标注，其余字段都能在swap表里找到*/
public class TransferListDTO {
    @ApiModelProperty(value = "隐藏属性唯一id", required = true ,example = "1")
    private String id;
    @ApiModelProperty(value = "所属组织,frame表",required = true , example = "默认组织")
    private String name;
    @ApiModelProperty(value = "单据时间",required = true , example = "2025-10-18")
    private LocalDateTime time;
    @ApiModelProperty(value = "单据编号",required = true , example = "DJ20251018001")
    private String number;
    @ApiModelProperty(value = "单据成本",required = true , example = "12")
    private BigDecimal total;
    @ApiModelProperty(value = "单据费用",required = true , example = "0")
    private BigDecimal cost;
    @ApiModelProperty(value = "关联人员",required = true , example = "")
    private String people;
    @ApiModelProperty(value = "审核状态", example = "未审核")
    private int examine;
    @ApiModelProperty(value = "费用状态", example = "无需结算")
    private int cse;
    @ApiModelProperty(value = "制单人",required = true , example = "管理员")
    private String user;
    @ApiModelProperty(value = "备注信息", example = "")
    private String data;
}
