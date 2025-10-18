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
    @ApiModelProperty(value = "商品名称",example = "刀具")
    private String name;
    @ApiModelProperty(value = "商品编号",example = "0001")
    private String number;
    @ApiModelProperty(value = "规格型号",example = "DJ-001")
    private String spec;
    @ApiModelProperty(value = "商品类别",example = "1")
    private int category;
    @ApiModelProperty(value = "商品品牌",example = "飞虎")
    private String brand;
    @ApiModelProperty(value = "商品条码",example = "111222")
    private String code;
    @ApiModelProperty(value = "仓库信息",example = "1号仓库")
    private String warehouse;
}
