package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;

@Data
@TableName("is_room")
public class RoomDO {
    @TableId(value = "id",type = IdType.AUTO)
    private Integer id;

    private Integer warehouse;

    private Integer goods;

    private String attr;

    private BigDecimal nums;
}
