package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import io.swagger.models.auth.In;
import lombok.Data;

import java.math.BigDecimal;
import java.util.List;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 18:15
 * @Description: 库存盘点数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("库存盘点数据对象")
public class InventoryVerifyListDTO {

    @ApiModelProperty(value = "库存盘点id", example = "1")
    private Integer id;
    @ApiModelProperty(value = "商品名称", example = "刀具")
    private String name;
    @ApiModelProperty(value = "库存数量", example = "122")
    private String totalStock;
    @ApiModelProperty(value = "该属性的仓库库存明细",example = "1号仓库：111,2号仓库：10...")
    private List<WarehouseStockDTO> warehouses;
    @ApiModelProperty(value = "盘盈盘亏", example = "120")
    private BigDecimal InventoryDifference;
    @ApiModelProperty(value="商品编号",example = "0003")
    private String number;
    @ApiModelProperty(value = "规格型号", example = "DJ-111")
    private String spec;
    @ApiModelProperty(value = "商品分类id", example = "7")
    private Integer categoryId;
    @ApiModelProperty(value = "商品类型对象",example = "id:7,pid:1,name=’五金工具‘，sort:1,data:'五金工具'")
    private CategoryDataDTO categoryData;
    @ApiModelProperty(value = "商品品牌", example = "飞虎")
    private String brand;
    @ApiModelProperty(value = "商品单位", example = "个")
    private String unit;
    @ApiModelProperty(value = "商品条码", example = "1")
    private String code;
    @ApiModelProperty(value = "商品备注", example = "随便")
    private String data;
}
