package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;

@Data
@TableName("batch")
public class BatchDO {

    @TableId(value = "id",type = IdType.AUTO)
    private String id;

    @TableField("room")
    private String room;

    @TableField("warehouse")
    private String warehouse;

    @TableField("goods")
    private String goods;

    @TableField("number")
    private String number;

    @TableField("time")
    private LocalDate time;

    @TableField("nums")
    private BigDecimal nums;

}
