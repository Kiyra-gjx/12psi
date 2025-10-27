package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
@TableName("extry_info")
public class ExtryInfoDO {
//其他出库单详情
    private String id;

    private String pid;

    private String goods;

    private String attr;

    private String unit;

    private String warehouse;

    private String batch;

    private LocalDateTime mfd;

    private BigDecimal price;

    private BigDecimal nums;

    private String serial;

    private BigDecimal total;

    private String data;
}
