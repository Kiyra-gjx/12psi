package com.zeroone.star.project.query.j2.store;

import com.zeroone.star.project.query.PageQuery;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.time.LocalDate;
import java.util.List;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.query.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 10:41
 * @Description: 批次查询详情参数对象
 * @Version: 1.0
 */
@Data
@ApiModel("批次查询详情参数")
public class BatchDetailQuery extends PageQuery {
    @ApiModelProperty(value = "批次ID(隐藏属性)", example = "1")
    private List<Integer> batchId;
    @ApiModelProperty(value = "单据编号", example = "QTRKD2510181347194")
    private String number;
    @ApiModelProperty(value = "单据类型", example = "采购单")
    private List<String> type;
    @ApiModelProperty(value = "开始日期", example = "2025-10-13")
    private LocalDate startDate;
    @ApiModelProperty(value = "结束日期", example = "2025-10-22")
    private LocalDate endDate;
    @ApiModelProperty(value = "所属仓库", example = "0")
    private List<Integer> warehouse;
}
