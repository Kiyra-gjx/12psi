package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;
/**
 * @author Coda
 * @date 2025/10/28
 * @description 收发统计表
 */
@Data
@TableName("summary")
public class SummaryDO {
    private String id;
    private String pid;
    private String type;
    private String cls;
    private String info;
    private LocalDateTime time;
    private String goods;
    private String attr;
    private String warehouse;
    private String batch;
    private LocalDateTime mfd;
    private int direction;
    private BigDecimal price;
    private BigDecimal nums;
    private BigDecimal uct;
    private BigDecimal bct;
    private String exist;
    private String balance;
    private String handle;
}
