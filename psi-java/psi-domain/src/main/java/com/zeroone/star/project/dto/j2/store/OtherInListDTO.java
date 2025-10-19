package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-18 18:18
 * @Description: 其他入库单数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("其他入库单数据对象")
public class OtherInListDTO {
    @ApiModelProperty(value = "id", example = "1")
    int id;
    @ApiModelProperty(value = "供应商", example = "0")
    int supplier;
    @ApiModelProperty(value = "所属组织", example = "0")
    int frame;
    @ApiModelProperty(value = "单据时间", example = "1760457600")
    int time;
    @ApiModelProperty(value = "单据编号", example = "QTRKD2510150905505")
    String number;
    @ApiModelProperty(value = "单据类型", example = "0")
    int type;
    @ApiModelProperty(value = "单据成本", example = "2.0000")
    float total;
    @ApiModelProperty(value = "单据费用", example = "111.0000")
    float cost;
    @ApiModelProperty(value = "关联人员", example = "1")
    int people;
    @ApiModelProperty(value = "物流信息", example = "{\"key\":\"auto\",\"name\":\"自动识别\",\"number\":\"\"}")
    String logistic;
    @ApiModelProperty(value = "单据附件", example = "[{\"name\":\"5B1CBE37203B5F19F4A745CEEF3C4FAB.png\",\"url\":\"http:\\/\\/localhost:8080\\/static\\/upload\\/entry\\/68f46902ab8d9.png\"}]")
    String file;
    @ApiModelProperty(value = "备注信息", example = "111")
    String data;
    @ApiModelProperty(value = "扩展信息", example = "111")
    String more;
    @ApiModelProperty(value = "审核状态", example = "1")
    int examine;
    @ApiModelProperty(value = "费用状态", example = "1")
    int cse;
    @ApiModelProperty(value = "核对状态", example = "1")
    int check;
    @ApiModelProperty(value = "制单人", example = "1")
    int user;
}
