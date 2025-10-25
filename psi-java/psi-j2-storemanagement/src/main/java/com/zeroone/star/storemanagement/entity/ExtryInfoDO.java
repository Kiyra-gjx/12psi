package com.zeroone.star.storemanagement.entity;

import lombok.Data;

@Data
public class ExtryInfoDO {
//其他出库单详情
    private int id;

    private int pid;

    private int goods;

    private String attr;

    private String unit;

    private int warehouse;

    private String batch;

    private int mfd;

    private float price;

    private float nums;

    private String serial;

    private float total;

    private String data;
}
