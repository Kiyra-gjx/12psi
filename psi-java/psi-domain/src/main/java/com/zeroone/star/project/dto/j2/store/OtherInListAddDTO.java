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
 * @CreateTime: 2025-10-18 18:18
 * @Description: 其他入库单数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("其他入库单数据对象")
public class OtherInListAddDTO {
    @ApiModelProperty(value = "供应商",required = false, example = "0")
    private Integer supplier;

    @ApiModelProperty(value = "单据时间",required = true, example = "2023-10-18 18:18:00")
    private LocalDateTime time;

    @ApiModelProperty(value = "单据编号",required = true, example = "QTRKD2510151628275")
    private String number;

    @ApiModelProperty(value = "单据类型[0:其它入库单|1:盘盈单]",required = true, example = "0")
    private Integer type;

    @ApiModelProperty(value = "单据成本/商品总成本",required = true, example = "1000.0000")
    private BigDecimal total;

    @ApiModelProperty(value = "单据费用",required = true, example = "50.0000")
    private BigDecimal cost;

    @ApiModelProperty(value = "关联人员",required = false, example = "0")
    private Integer people;

    @ApiModelProperty(value = "物流信息",required = false, example = "{\"key\":\"auto\",\"name\":\"自动识别\",\"number\":\"\"}")
    private String logistics;

    @ApiModelProperty(value = "单据附件", required = false, example = "")
    private String file;

    @ApiModelProperty(value = "单据备注信息", required = false,example = "紧急订单，请优先处理")
    private String data;

    @ApiModelProperty(value = "审核状态[0:未审核|1:已审核]",required = true, example = "0")
    private Integer examine;

    @ApiModelProperty(value = "费用状态[0:未结算|1:部分结算|2:已结算|3:无需结算]",required = true, example = "3")
    private Integer cse;

    @ApiModelProperty(value = "核对状态[0:未核对|1:已核对]",required = true, example = "0")
    private Integer check;

    @ApiModelProperty(value = "制单人",required = true, example = "1")
    private Integer user;

    @ApiModelProperty(value = "ID", required = true, example = "1")
    private Integer id;

    @ApiModelProperty(value = "所属ID", required = true, example = "1")
    private Integer pid;

    @ApiModelProperty(value = "所属商品", required = true, example = "1")
    private Integer goods;

    @ApiModelProperty(value = "辅助属性", required = true, example = "红色")
    private String attr;

    @ApiModelProperty(value = "单位", required = true, example = "个")
    private String unit;

    @ApiModelProperty(value = "仓库", required = false, example = "1")
    private Integer warehouse;

    @ApiModelProperty(value = "批次号", required = true, example = "BATCH20231018")
    private String batch;

    @ApiModelProperty(value = "生产日期", required = false, example = "1697644800")
    private Integer mfd;

    @ApiModelProperty(value = "成本", required = true, example = "100.0000")
    private BigDecimal price;

    @ApiModelProperty(value = "数量", required = true, example = "10.0000")
    private BigDecimal nums;

    @ApiModelProperty(value = "序列号", required = true, example = "SN123456789")
    private String serial;

    @ApiModelProperty(value = "商品备注信息", required = true, example = "紧急订单，请优先处理")
    private String GoodsData;
}
