package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
@TableName("serve_info")
public class ServeInfoDO {
    private String id;
    private String pid;
    private String type;
    private String cls;
    private String info;
    private LocalDateTime time;
    private BigDecimal price;
    private BigDecimal nums;
}
