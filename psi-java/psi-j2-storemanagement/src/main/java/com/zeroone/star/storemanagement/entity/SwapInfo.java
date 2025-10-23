package com.zeroone.star.storemanagement.entity;

import lombok.Data;

import java.math.BigDecimal;
import java.util.Date;

@Data
public class SwapInfo {

    private String id;

    private String pid;

    private String good;

    private String attr;

    private String unit;

    private String warehouse;

    private String storehouse;

    private String batch;

    private Date mfd;

    private BigDecimal price;

    private BigDecimal nums;

    private String serial;

    private BigDecimal total;

    private String data;


}
