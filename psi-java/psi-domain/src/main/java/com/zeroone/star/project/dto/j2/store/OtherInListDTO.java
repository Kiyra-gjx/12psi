package com.zeroone.star.project.dto.j2.store;

import com.alibaba.excel.annotation.ExcelProperty;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.util.List;


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

    @ExcelProperty(value = "供应商", index = 1)
    @ApiModelProperty(value = "供应商", example = "0")
    int supplier;

    @ExcelProperty(value = "所属组织", index = 0)
    @ApiModelProperty(value = "所属组织", example = "0")
    int frame;

    @ExcelProperty(value = "单据时间", index = 3)
    @ApiModelProperty(value = "单据时间", example = "1760457600")
    int time;

    @ExcelProperty(value = "单据编号", index = 4)
    @ApiModelProperty(value = "单据编号", example = "QTRKD2510150905505")
    String number;

    @ExcelProperty(value = "单据类型", index = 2)
    @ApiModelProperty(value = "单据类型", example = "0")
    int type;

    @ExcelProperty(value = "单据成本", index = 5)
    @ApiModelProperty(value = "单据成本", example = "2.0000")
    float total;

    @ExcelProperty(value = "单据费用", index = 6)
    @ApiModelProperty(value = "单据费用", example = "111.0000")
    float cost;

    @ExcelProperty(value = "关联人员", index = 7)
    @ApiModelProperty(value = "关联人员", example = "1")
    int people;

    @ApiModelProperty(value = "物流信息", example = "{\"key\":\"auto\",\"name\":\"自动识别\",\"number\":\"\"}")
    String logistic;

    @ApiModelProperty(value = "单据附件", example = "[{\"name\":\"5B1CBE37203B5F19F4A745CEEF3C4FAB.png\",\"url\":\"http:\\/\\/localhost:8080\\/static\\/upload\\/entry\\/68f46902ab8d9.png\"}]")
    String file;

    @ExcelProperty(value = "备注信息", index = 12)
    @ApiModelProperty(value = "备注信息", example = "111")
    String data;

    @ApiModelProperty(value = "扩展信息", example = "111")
    String more;

    @ExcelProperty(value = "审核状态", index = 8)
    @ApiModelProperty(value = "审核状态", example = "1")
    private Integer examine;

    @ExcelProperty(value = "费用状态", index = 9)
    @ApiModelProperty(value = "费用状态", example = "1")
    int cse;

    @ExcelProperty(value = "核对状态", index = 10)
    @ApiModelProperty(value = "核对状态", example = "1")
    int check;

    @ExcelProperty(value = "制单人", index = 11)
    @ApiModelProperty(value = "制单人", example = "1")
    int user;

    @ApiModelProperty(value = "入库单详细信息列表")
    List<OtherInListInfoDTO> otherInListInfoDTOList;

    @ApiModelProperty(value = "单据费用列表", example = "{id: 7, type: \"entry\", class: 4, time: \"2025-10-15\", iet: 5, money: 111, data: \"\", settle: 0, state: 0}")
    List<CostDTO> costDTOList;
}
