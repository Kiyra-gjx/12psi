package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import lombok.Data;
import java.math.BigDecimal;

@Data
public class BatchInfo {

    private String id;

    private String pid;

    private String type;

    @TableField("class")
    private String cls;

    private String info;

    private int direction;

    private BigDecimal nums;

}
