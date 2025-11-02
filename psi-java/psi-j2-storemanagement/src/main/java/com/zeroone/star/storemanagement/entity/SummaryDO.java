package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;
/**
 * @author Coda
 * @date 2025/10/28
 * @description 收发统计表
 */
@Data
@TableName("is_summary")
public class SummaryDO {
    private Integer id;
    private Integer pid;
    private String type;
    @TableField("class")
    private Integer cls;
    private Integer info;
    private Integer time;
    private Integer goods;
    private String attr;
    private Integer warehouse;
    private String batch;
    private Integer mfd;
    private int direction;
    private BigDecimal price;
    private BigDecimal nums;
    private BigDecimal uct;
    private BigDecimal bct;
    private String exist;
    private String balance;
    private String handle;
}
