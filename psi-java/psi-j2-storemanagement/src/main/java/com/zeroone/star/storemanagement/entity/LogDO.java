package com.zeroone.star.storemanagement.entity;

import lombok.Data;

import java.time.LocalDateTime;
/**
 * @author Coda
 * @date 2025/10/28
 * @description 日志表实体类
 */
@Data
public class LogDO {
    private String id;
    private LocalDateTime time;
    private String user;
    private String info;
}
