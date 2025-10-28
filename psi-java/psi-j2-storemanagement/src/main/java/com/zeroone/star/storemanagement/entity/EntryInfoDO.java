package com.zeroone.star.storemanagement.entity;

import lombok.Data;

import java.time.LocalDateTime;

@Data
public class EntryInfoDO {

    private int id;

    private int pid;

    private int goods;

    private String attr;

    private String unit;

    private int warehouse;

    private String batch;

    private LocalDateTime mfd;

    private float price;

    private float nums;

    private String serial;

    private float total;

    private String data;
}
