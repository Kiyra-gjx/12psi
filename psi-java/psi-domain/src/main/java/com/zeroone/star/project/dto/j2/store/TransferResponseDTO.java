package com.zeroone.star.project.dto.j2.store;

import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.dto.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 22:36
 * @Description: 调拨单响应DTO
 * @Version: 1.0
 */
@Data
@ApiModel("调拨单响应")
public class TransferResponseDTO {
    @ApiModelProperty(value = "操作状态", example = "success", allowableValues = "success,error")
    private String state;

    @ApiModelProperty(value = "响应信息", example = "4")
    private Object info;
}
