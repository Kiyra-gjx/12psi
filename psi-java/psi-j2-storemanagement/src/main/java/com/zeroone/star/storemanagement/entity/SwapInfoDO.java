package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;

@Data
@TableName("is_swap_info")
public class SwapInfoDO {

    private String id;

    private String pid;

    private String goods;

    private String attr;

    private String unit;

    private String warehouse;

    private String storehouse;

    private String batch;

    private LocalDate mfd;

    private BigDecimal price;

    private BigDecimal nums;

    private String serial;

    private BigDecimal total;

    private String data;


}
