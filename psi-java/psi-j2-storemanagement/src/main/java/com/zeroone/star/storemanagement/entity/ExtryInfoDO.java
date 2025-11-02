package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;

@Data
@TableName("is_extry_info")
public class ExtryInfoDO {
//其他出库单详情
    @TableId(value = "id",type = IdType.AUTO)
    private Integer id;

    private Integer pid;

    private Integer goods;

    private String attr;

    private String unit;

    private Integer warehouse;

    private String batch;

    private Integer mfd;

    private BigDecimal price;

    private BigDecimal nums;

    private String serial;

    private BigDecimal total;

    private String data;
}
