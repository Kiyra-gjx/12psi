package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;

@Data
@TableName("room")
public class RoomDO {

    private String id;

    private String warehouse;

    private String goods;

    private String attr;

    private BigDecimal nums;
}
