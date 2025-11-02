package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;

@Data
@TableName("is_goods")
public class GoodsDO {
    @TableId(value = "id",type = IdType.AUTO)
    private Integer id;

    private String name;

    private String py;

    private String number;

    private String spec;

    private Integer category;

    private String brand;

    private String unit;

    private BigDecimal buy;

    private BigDecimal sell;

    private String code;

    private String location;

    private BigDecimal stock;

    private Integer type;

    private String data;

    private String imgs;

    private String details;

    private String units;

    private String strategy;

    private Integer serial;

    private Integer batch;

    private Integer validity;

    private Integer protect;

    private Integer threshold;

    private String more;
}
