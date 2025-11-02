package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;

@Data
@TableName("is_batch")
public class BatchDO {

    @TableId(value = "id",type = IdType.AUTO)
    private  Integer id;

    @TableField("room")
    private Integer room;

    @TableField("warehouse")
    private Integer warehouse;

    @TableField("goods")
    private Integer goods;

    @TableField("number")
    private String number;

    @TableField("time")
    private Integer time;

    @TableField("nums")
    private BigDecimal nums;

}
