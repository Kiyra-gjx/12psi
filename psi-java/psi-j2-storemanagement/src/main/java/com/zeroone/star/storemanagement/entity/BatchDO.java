package com.zeroone.star.storemanagement.entity;

import lombok.Data;
import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
public class BatchDO {

    private String id;

    private String room;

    private String warehouse;

    private String goods;

    private String number;

    private LocalDateTime time;

    private BigDecimal nums;

}
