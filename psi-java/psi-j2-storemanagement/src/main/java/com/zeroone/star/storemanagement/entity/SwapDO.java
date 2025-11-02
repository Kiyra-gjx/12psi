package com.zeroone.star.storemanagement.entity;


import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;

@Data
public class SwapDO {

    private String id;

    private String frame;

    private LocalDate time;

    private String number;

    private BigDecimal total;

    private BigDecimal cost;

    private String logistics;

    private String people;

    private String file;

    private String data;

    private String more;

    private int examine;

    private int cse;

    private String user;


}
