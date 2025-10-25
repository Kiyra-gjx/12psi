package com.zeroone.star.storemanagement.entity;

import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
public class ExtryDO {
//其他出库单
        private Integer id;

        private Integer customer;

        private int frame;

        private LocalDateTime time;

        private String number;

        private Integer type;

        private BigDecimal total;

        private BigDecimal cost;

        private Integer people;

        private String logistics;

        private String file;

        private String data;

        private String more;

        private Integer examine;

        private Integer cse;

        private Integer check;

        private Integer user;

    }


