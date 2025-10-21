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
 * @Description: 批次查询详情数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("批次查询详情数据对象")
public class BatchDetailDTO {
    @ApiModelProperty(value = "id", example = "1")
    private int id;

    @ApiModelProperty(value = "所属id", example = "1")
    private int pid;

    @ApiModelProperty(value = "方向", example = "[0:出|1:入]")
    private int direction;

    @ApiModelProperty(value = "出入数量", example = "1")
    private BigDecimal nums;

    @ApiModelProperty(value = "单据类型", example = "entry")
    private String type;

    @ApiModelProperty(value = "所属详情", example = "8")
    private int info;

    @ApiModelProperty(value = "所属类", example = "3")
    private int cls;

    @ApiModelProperty(value = "扩展信息", example = "type:'其他入库单',direction:'增加'")
    private List<String> extension;

    @ApiModelProperty(value = "详情数据")
    private List<BatchDetailDataDTO> sourceData;

}
