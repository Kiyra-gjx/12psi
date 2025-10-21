package com.zeroone.star.project.query.j2.store;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.query.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 13:46
 * @Description: 商品详情查询对象
 * @Version: 1.0
 */
@Data
@ApiModel("商品详情查询对象")
public class InventoryDetailQuery extends PageQuery {

    @ApiModelProperty(value = "商品ID", example = "1",required = true)
    private Integer goodsId;

    @ApiModelProperty(value = "商品属性ID", example = "101",required = true)
    private Integer attrId;

    @ApiModelProperty(value = "单据ID（隐藏属性）", example = "1",required = true)
    private Integer documentId;

    @ApiModelProperty(value = "单据编号", example = "PUR-20231001")
    private String documentNumber;

    @ApiModelProperty(value = "单据类型（可选多个）")
    private List<String> documentTypes;

    @ApiModelProperty(value = "开始日期（String类型接收）", example = "2024-10-01")
    private String startDate;

    @ApiModelProperty(value = "结束日期（String类型接收）", example = "2025-10-01")
    private String endDate;

    @ApiModelProperty(value = "所属仓库")
    private List<Integer> warehouse;

}
