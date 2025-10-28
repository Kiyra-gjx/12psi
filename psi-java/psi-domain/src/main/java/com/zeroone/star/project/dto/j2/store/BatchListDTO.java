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
    @ApiModelProperty(value = "商品id（内部使用）", example = "1")
    private Integer id;

    @ApiModelProperty(value = "商品名称", example = "牛奶")
    private String name;

    @ApiModelProperty(value = "库存数量", example = "300")
    private BigDecimal totalStock;

    @ApiModelProperty(value = "保质期（天）", example = "365")
    private Integer protect;

    @ApiModelProperty(value = "库存阈值", example = "30")
    private Integer threshold;

    @ApiModelProperty(value = "商品编号", example = "0001")
    private String number;

    @ApiModelProperty(value = "规格型号", example = "500ml")
    private String spec;

    @ApiModelProperty(value = "商品类别id（内部使用）", example = "1")
    private int categoryId;

    @ApiModelProperty(value = "商品分类")
    private CategoryDataDTO categoryData;

    @ApiModelProperty(value = "商品品牌", example = "伊利")
    private String brand;

    @ApiModelProperty(value = "商品单位", example = "盒")
    private String unit;

    @ApiModelProperty(value = "商品条码", example = "111222")
    private String code;

    @ApiModelProperty(value = "商品备注", example = "")
    private String remark;

    @ApiModelProperty(value = "批次产品[0:关闭|1:启用]", example = "0")
    private Integer batch;

    @ApiModelProperty(value = "批次号列表")
    private List<BatchNumberDTO> batches;


    // ================= 不是批次产品直接展示仓库库存 =================
    @ApiModelProperty(value = "仓库库存信息（非批次产品使用）")
    private List<WarehouseStockDTO> warehouses;

}
