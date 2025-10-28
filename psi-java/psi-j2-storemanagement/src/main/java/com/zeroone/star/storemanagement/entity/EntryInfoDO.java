package com.zeroone.star.storemanagement.entity;

import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
public class EntryInfoDO {

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
