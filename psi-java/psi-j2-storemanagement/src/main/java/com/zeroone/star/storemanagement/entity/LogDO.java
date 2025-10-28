package com.zeroone.star.storemanagement.entity;

import lombok.Data;

import java.time.LocalDateTime;

@Data
public class LogDO {
    private String id;
    private LocalDateTime time;
    private String user;
    private String info;
}
