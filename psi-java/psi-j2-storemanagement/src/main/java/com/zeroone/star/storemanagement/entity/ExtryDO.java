package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;

@Data
@TableName("extry")
public class ExtryDO {
//其他出库单
        private String id;

        private String customer;

        private String frame;

        private Integer time;

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

        @TableField("`check`")
        private Integer check;

        @TableField("`user`")
        private String user;

    }


