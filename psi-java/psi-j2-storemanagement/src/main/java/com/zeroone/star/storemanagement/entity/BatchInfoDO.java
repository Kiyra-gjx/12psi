package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import java.math.BigDecimal;

@Data
@TableName("is_batch_info")
public class BatchInfoDO {

    private String id;

    private String pid;

    private String type;

    @TableField("class")
    private String cls;

    private String info;

    private int direction;

    private BigDecimal nums;

}
