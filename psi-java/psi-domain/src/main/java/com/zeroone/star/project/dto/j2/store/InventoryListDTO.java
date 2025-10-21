package com.zeroone.star.project.dto.j2.store;

import com.alibaba.excel.annotation.ExcelProperty;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.util.List;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 10:43
 * @Description: 库存查询数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("库存列表对象")
public class InventoryListDTO {
    // ================= 商品基础信息 =================
    @ApiModelProperty(value = "商品ID（内部使用）", example = "1")
    private Integer id;

    @ExcelProperty(value = "商品名称", index = 0)
    @ApiModelProperty(value = "商品名称", example = "iphone")
    private String name;

    @ExcelProperty(value = "库存数量", index = 1)
    @ApiModelProperty(value = "商品总库存（所有属性库存的合计）", example = "300")
    private BigDecimal totalStock;

    @ExcelProperty(value = "预警阈值", index = 4)
    @ApiModelProperty(value = "库存阈值", example = "30")
    private Integer threshold;

    @ExcelProperty(value = "商品编号", index = 5)
    @ApiModelProperty(value = "商品编号", example = "0001")
    private String number;

    @ExcelProperty(value = "规格型号", index = 6)
    @ApiModelProperty(value = "规格型号", example = "17pro")
    private String spec;

    @ApiModelProperty(value = "商品类型对象")
    private CategoryDataDto categoryData;

    @ExcelProperty(value = "商品品牌", index = 8)
    @ApiModelProperty(value = "商品品牌", example = "苹果")
    private String brand;

    @ExcelProperty(value = "商品单位", index = 9)
    @ApiModelProperty(value = "商品单位", example = "个")
    private String unit;

    @ExcelProperty(value = "商品条码", index = 10)
    @ApiModelProperty(value = "商品条码", example = "111222")
    private String code;

    @ExcelProperty(value = "商品备注", index = 11)
    @ApiModelProperty(value = "备注信息", example = "")
    private String remark;

    // ================= 属性库存信息 =================
    @ApiModelProperty(value = "商品属性库存列表")
    private List<AttrStockDTO> specs;

    @ExcelProperty(value = "商品名称", index = 2)
    // ================= 若无属性时展示仓库库存 =================
    @ApiModelProperty(value = "仓库库存信息(仅当specs为空时有效)")
    private List<WarehouseStockDTO> warehouses;


}
