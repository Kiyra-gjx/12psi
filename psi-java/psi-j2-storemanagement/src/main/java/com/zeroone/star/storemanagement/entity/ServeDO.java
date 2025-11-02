package com.zeroone.star.storemanagement.entity;

import lombok.Data;

import java.math.BigDecimal;

/**
 * @author Coda
 * @date 2025/10/28
 * @description 服务信息
 */
@Data
public class ServeDO {
    private String id;
    private String goods;
    private String attr;
    private BigDecimal nums;
}
