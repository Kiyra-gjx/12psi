package com.zeroone.star.storemanagement.entity;

import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
public class EntryDO {

        private String id;

        private String supplier;

        private String frame;

        private LocalDateTime time;

        private String number;

        private Integer type;

        private BigDecimal total;

        private BigDecimal cost;

        private String people;

        private String logistics;

        private String file;

        private String data;

        private String more;

        private Integer examine;

        private Integer cse;

        private Integer check;

        private String user;

}
