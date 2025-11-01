package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@TableName("record")
public class RecordDO {
    private String id;

    private String type;

    private String source;

    private LocalDateTime time;

    private String user;

    private String info;
}
