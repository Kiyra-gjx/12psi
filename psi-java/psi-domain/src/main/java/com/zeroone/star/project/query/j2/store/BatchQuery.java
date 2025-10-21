package com.zeroone.star.project.query.j2.store;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import io.swagger.models.auth.In;
import lombok.Data;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.query.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 10:37
 * @Description: 批次查询参数对象
 * @Version: 1.0
 */
@Data
@ApiModel("批次查询对象")
public class BatchQuery extends PageQuery {

    // ==================== 商品基础信息条件 ====================
    @ApiModelProperty(value = "商品ID",example = "1")
    private Integer goodsId;

    @ApiModelProperty(value = "商品名称（可选）",example = "牛奶")
    private String goodsName;

    @ApiModelProperty(value = "商品编号",example = "0001")
    private String goodsNumber;

    @ApiModelProperty(value = "批次号码",example = "20231001")
    private String batchNumber;

    @ApiModelProperty(value = "生产日期",example = "2025-10-15")
    private String productDate;

    @ApiModelProperty(value = "商品型号",example = "500ml")
    private String goodsSpec;

    @ApiModelProperty(value = "商品类别ID",example = "1")
    private Integer categoryId;

    @ApiModelProperty(value = "商品类别名称（可选）",example = "默认类别")
    private String categoryName;

    @ApiModelProperty(value = "商品品牌",example = "苹果")
    private String brand;

    @ApiModelProperty(value = "商品条码",example = "111222")
    private String code;
    // ==================== 仓库信息条件 ===================
    @ApiModelProperty(value = "仓库ID",example = "1")
    private Integer warehouseId;

    @ApiModelProperty(value = "仓库名称（可选）",example = "上海仓库")
    private String warehouseName;

    @ApiModelProperty(
            value = "批次类型：0-常规批次，1-非零批次，2-预警批次",
            example = "1")
    private Integer batchType;
}
