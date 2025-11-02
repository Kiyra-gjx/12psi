package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;

/**
 * @author Coda
 * @date 2025/10/28
 * @description 服务信息
 */
@Data
@TableName("is_serve")
public class ServeDO {
    @TableId(value = "id",type = IdType.AUTO)
    private Integer id;
    private Integer goods;
    private String attr;
    private BigDecimal nums;
}
