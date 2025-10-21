package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.util.List;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 22:36
 * @Description: 调拨单修改请求DTO
 * @Version: 1.0
 */
@Data
@ApiModel("调拨单修改请求数据")
public class ModifyTransferRequestDTO {

    @ApiModelProperty(value = "单据明细", required = true)
    private ClassInfo classInfo;

    @ApiModelProperty(value = "成本信息")
    private List<Object> cost;

    @ApiModelProperty(value = "商品明细", required = true)
    private Info info;

    @Data
    @ApiModel("分类信息")
    public static class ClassInfo {
        @ApiModelProperty(value = "成本", example = "0.00")
        private BigDecimal cost;

        @ApiModelProperty(value = "费用状态", example = "3", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private Integer cse;

        @ApiModelProperty(value = "备注信息")
        private String data;

        @ApiModelProperty(value = "审核状态", example = "0", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private Integer examine;

        @ApiModelProperty(value = "单据附件", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private List<Object> file;

        @ApiModelProperty(value = "所属组织", example = "0", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private Integer frame;

        @ApiModelProperty(value = "调拨单ID", required = true, example = "4")
        private Integer id;

        @ApiModelProperty(value = "物流信息", required = true)
        private List<Logistics> logistics;

        @ApiModelProperty(value = "扩展信息", example = "{}", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String more;

        @ApiModelProperty(value = "编号", example = "DBD2510191240397", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String number;

        @ApiModelProperty(value = "关联人员", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private Integer people;

        @ApiModelProperty(value = "时间", example = "2025-10-19", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String time;

        @ApiModelProperty(value = "总金额", example = "998.00", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private BigDecimal total;

        @ApiModelProperty(value = "制单人", example = "1", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private Integer user;
    }

    @Data
    @ApiModel("物流信息")
    public static class Logistics {
        @ApiModelProperty(value = "物流方式键", example = "auto", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String key;

        @ApiModelProperty(value = "物流方式名称", example = "自动识别", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String name;

        @ApiModelProperty(value = "物流单号", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String number;
    }

    @Data
    @ApiModel("商品信息")
    public static class Info {
        @ApiModelProperty(value = "辅助属性", example = "经典黑|S", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String attr;

        @ApiModelProperty(value = "批次号", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String batch;

        @ApiModelProperty(value = "备注信息", example = "紧急调拨")
        private String data;

        @ApiModelProperty(value = "所属商品", example = "1", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private Integer goods;

        @ApiModelProperty(value = "生产日期", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String mfd;

        @ApiModelProperty(value = "数量", example = "1")
        private BigDecimal nums;

        @ApiModelProperty(value = "成本", example = "998")
        private BigDecimal price;

        @ApiModelProperty(value = "序列号", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String serial;

        @ApiModelProperty(value = "调入仓库", example = "1")
        private Integer storehouse;

        @ApiModelProperty(value = "总成本", example = "998.00", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private BigDecimal total;

        @ApiModelProperty(value = "单位", example = "件", accessMode = ApiModelProperty.AccessMode.READ_ONLY)
        private String unit;

        @ApiModelProperty(value = "调出仓库", example = "2")
        private Integer warehouse;
    }
}
