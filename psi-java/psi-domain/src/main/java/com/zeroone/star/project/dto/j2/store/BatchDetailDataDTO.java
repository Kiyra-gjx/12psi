package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import sun.util.resources.LocaleData;

import java.math.BigDecimal;
import java.util.List;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-21 21:25
 * @Description: TODO
 * @Version: 1.0
 */
@Data
@ApiModel("批次查询详情数据数据对象")
public class BatchDetailDataDTO {
    @ApiModelProperty(value = "id", example = "1")
    private int id;

    @ApiModelProperty(value = "核对状态", example = "[0:未核对|1:已核对]")
    private int check;

    @ApiModelProperty(value = "单据费用", example = "0")
    private int cost;

    @ApiModelProperty(value = "费用状态",example = "[0:未结算|1:部分结算|2:已结算|3:无需结算]")
    private int cse;

    @ApiModelProperty(value = "备注信息", example = "")
    private String data;

    @ApiModelProperty(value = "审核状态", example = "[0:未审核|1:已审核]")
    private int examine;

    @ApiModelProperty(value = "单据附件")
    private List<String> file;

    @ApiModelProperty(value = "所属组织", example = "0")
    private int frame;

    @ApiModelProperty(value = "组织信息")
    private List<FrameDataDTO> frameData;

    @ApiModelProperty(value = "物流信息")
    private List<String> logistics;

    @ApiModelProperty(value = "扩展信息")
    private List<String> more;

    @ApiModelProperty(value = "单据编号", example = "QTRKD2510181347194")
    private String number;

    @ApiModelProperty(value = "关联人员", example = "0")
    private String people;

    @ApiModelProperty(value = "供应商", example = "0")
    private int supplier;

    @ApiModelProperty(value = "单据时间", example = "2025-10-18")
    private LocaleData time;

    @ApiModelProperty(value = "单据成本", example = "12")
    private BigDecimal total;

    @ApiModelProperty(value = "单据类型", example = "[0:其它入库单|1:盘盈单]")
    private int type;

    @ApiModelProperty(value = "制单人", example = "1")
    private int user;
}
