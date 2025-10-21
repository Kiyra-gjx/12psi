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
 * @CreateTime: 2025-10-21 22:55
 * @Description: 其他出库单修改数据对象
 * @Version: 1.0
 */
@Data
@ApiModel("其他出库单修改数据对象")
public class OtherInListUpdateDTO {
    @ApiModelProperty(value = "其他入库单数据信息对象")
    OtherInListDTO otherInListDTO;

    @ApiModelProperty(value = "出库单详细信息列表")
    List<OtherInListInfoDTO> otherInListInfoDTOList;

    @ApiModelProperty(value = "单据费用列表")
    List<CostDTO> costDTOList;
}
