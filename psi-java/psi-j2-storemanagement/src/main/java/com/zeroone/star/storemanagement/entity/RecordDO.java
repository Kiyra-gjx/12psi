package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("is_record")
public class RecordDO {
    @TableId(value = "id",type = IdType.AUTO)
    private Integer id;

    private String type;

    private Integer source;

    private Integer time;

    private Integer user;

    private String info;
}
