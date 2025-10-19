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
 * @CreateTime: 2025-10-18 18:13
 * @Description: 批次查询数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("批次列表数据对象")
public class BatchListDTO {
    // ================= 商品基础信息 =================
    @ApiModelProperty(value = "商品ID（内部使用）", example = "1")
    private Integer id;

    @ApiModelProperty(value = "商品名称", example = "牛奶")
    private String name;

    @ApiModelProperty(value = "商品总库存（所有属性库存的合计）", example = "300")
    private BigDecimal totalStock;

    @ApiModelProperty(value = "商品保质期", example = "365（天）")
    private Integer protect;

    @ApiModelProperty(value = "库存阈值", example = "30")
    private Integer threshold;

    @ApiModelProperty(value = "商品编号", example = "0001")
    private String number;

    @ApiModelProperty(value = "规格型号", example = "500ml")
    private String spec;

    @ApiModelProperty(value = "商品类别id（内部使用）", example = "1")
    private int categoryId;

    @ApiModelProperty(value = "商品分类", example = "乳制品")
    private String category;

    @ApiModelProperty(value = "商品品牌", example = "伊利")
    private String brand;

    @ApiModelProperty(value = "商品单位", example = "盒")
    private String unit;

    @ApiModelProperty(value = "商品条码", example = "111222")
    private String code;

    @ApiModelProperty(value = "备注信息", example = "")
    private String remark;
    // ================= 批次库存信息 =================
    @ApiModelProperty(value = "不同批次库存列表")
    private List<BatchStockDTO> specs;


    // ================= 若无属性时展示仓库库存 =================
    @ApiModelProperty(value = "仓库库存信息(仅当specs为空时有效)")
    private List<WarehouseStockDTO> warehouses;

}
