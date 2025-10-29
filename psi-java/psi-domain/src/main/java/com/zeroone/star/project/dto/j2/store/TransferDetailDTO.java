package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;
import java.math.BigDecimal;
import java.time.LocalDate;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 18:17
 * @Description: 调拨单详情数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("调拨单详情数据对象")
public class TransferDetailDTO {
    @ApiModelProperty(value = "单据时间", example = "2025-10-19")
    private LocalDate time;

    @ApiModelProperty(value = "单据编号", example = "DBD2510191240397")
    private String number;

    @ApiModelProperty(value = "商品明细", required = true)
    private Info info;

    @ApiModelProperty(value = "单据明细", required = true)
    private ClassInfo classInfo;

    @Data
    @ApiModel("分类信息")
    public static class ClassInfo {
        @ApiModelProperty(value = "单据成本", example = "998.00", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private BigDecimal total;

        @ApiModelProperty(value = "单据费用", example = "0.00")
        private BigDecimal cost;

        @ApiModelProperty(value = "关联人员", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String people;

        @ApiModelProperty(value = "物流信息")
        private String logistics;

        @ApiModelProperty(value = "单据附件", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String file;

        @ApiModelProperty(value = "备注信息", example = "test")
        private String data;
    }

    @Data
    @ApiModel("商品信息")
    public static class Info {
        @ApiModelProperty(value = "调拨单详情ID", example = "17")
        private String id;

        @ApiModelProperty(value = "商品名称", example = "男士纯棉圆领T恤", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String name;

        @ApiModelProperty(value = "商品编号", example = "0001", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String number;

        @ApiModelProperty(value = "规格型号", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String spec;

        @ApiModelProperty(value = "辅助属性", example = "经典黑|S", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String attr;

        @ApiModelProperty(value = "单位", example = "件", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String unit;

        @ApiModelProperty(value = "调出仓库", example = "2")
        private String warehouse;

        @ApiModelProperty(value = "调入仓库", example = "1")
        private String storehouse;

        @ApiModelProperty(value = "成本", example = "998")
        private BigDecimal price;

        @ApiModelProperty(value = "数量", example = "1")
        private BigDecimal nums;

        @ApiModelProperty(value = "总成本", example = "998.00", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private BigDecimal total;

        @ApiModelProperty(value = "备注信息", example = "紧急调拨")
        private String data;

    }
}
