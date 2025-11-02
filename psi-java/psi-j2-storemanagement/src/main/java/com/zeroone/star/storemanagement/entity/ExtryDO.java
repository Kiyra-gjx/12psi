package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;

@Data
@TableName("is_extry")
public class ExtryDO {
//其他出库单
        @TableId(value = "id",type = IdType.AUTO)
        private Integer id;

        private Integer customer;

        private Integer frame;

        private Integer time;

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

        @TableField("`check`")
        private Integer check;

        @TableField("`user`")
        private Integer user;

    }


