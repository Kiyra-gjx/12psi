package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;

@Data
@TableName("is_room_info")
public class RoomInfoDO {
    @TableId(value = "id",type = IdType.AUTO)
    private Integer id;

    private Integer pid;

    private String type;

    @TableField("class")
    private Integer cls;

    private Integer info;

    private Integer time;

    private Integer direction;

    private BigDecimal price;

    private BigDecimal nums;
}
