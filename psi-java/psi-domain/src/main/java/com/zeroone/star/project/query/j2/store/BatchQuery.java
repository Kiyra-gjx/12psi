package com.zeroone.star.project.query.j2.store;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import io.swagger.models.auth.In;
import lombok.Data;

import java.time.LocalDate;
import java.util.List;

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

    @ApiModelProperty(value = "商品ID",example = "1")
    private String  goodsId;

    @ApiModelProperty(value = "商品名称",example = "牛奶")
    private String goodsName;

    @ApiModelProperty(value = "商品编号",example = "0001")
    private String goodsNumber;

    @ApiModelProperty(value = "批次号码",example = "20231001")
    private String batchNumber;

    @ApiModelProperty(value = "生产日期",example = "2025-10-15")
    private LocalDate productDate;

    @ApiModelProperty(value = "商品型号",example = "500ml")
    private String goodsSpec;

    @ApiModelProperty(value = "商品类别ID",example = "1")
    private String  goodsCategoryId;

    @ApiModelProperty(value = "商品品牌",example = "苹果")
    private String goodsBrand;

    @ApiModelProperty(value = "商品条码",example = "111222")
    private String goodsCode;

    @ApiModelProperty(value = "仓库信息",example = "1")
    private List<String> warehouseIds;


    @ApiModelProperty(
            value = "批次类型：0-常规批次，1-预警批次",
            example = "1")
    private Integer batchState;
}
