package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
@TableName("room_info")
public class RoomInfoDO {

    private String id;

    private String pid;

    private String type;

    @TableField("class")
    private String cls;

    private String info;

    private LocalDateTime time;

    private Integer direction;

    private BigDecimal price;

    private BigDecimal nums;
}
