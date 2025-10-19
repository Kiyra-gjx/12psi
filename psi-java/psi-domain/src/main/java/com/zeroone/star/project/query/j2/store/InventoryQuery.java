package com.zeroone.star.project.query.j2.store;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.query.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 10:29
 * @Description: 商品查询参数对象
 * @Version: 1.0
 */
@Data
@ApiModel("商品查询参数")
public class InventoryQuery extends PageQuery {

    // ==================== 商品基础信息条件 ====================
    @ApiModelProperty(value = "商品名称",example = "iphone")
    private String name;

    @ApiModelProperty(value = "商品编号",example = "0001")
    private String number;

    @ApiModelProperty(value = "规格型号",example = "17pro")
    private String spec;

    @ApiModelProperty(value = "商品类别id",example = "1")
    private Integer category;

    @ApiModelProperty(value = "商品类别名称",example = "默认类别")
    private String categoryName;

    @ApiModelProperty(value = "商品品牌",example = "苹果")
    private String brand;

    @ApiModelProperty(value = "商品条码",example = "111222")
    private String code;
    // ==================== 仓库信息条件 ===================
    @ApiModelProperty(value = "仓库ID",example = "1")
    private Integer warehouseId;

    @ApiModelProperty(value = "仓库名称",example = "上海仓库")
    private String warehouseName;

    @ApiModelProperty(
            value = "库存类型：0-常规库存，1-非零库存，2-预警库存",
            example = "1")
    private Integer stockType;
}
