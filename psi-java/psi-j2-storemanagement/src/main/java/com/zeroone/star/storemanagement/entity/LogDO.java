package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
/**
 * @author Coda
 * @date 2025/10/28
 * @description 日志表实体类
 */
@Data
@TableName("is_log")
public class LogDO {
    @TableId(value = "id",type = IdType.AUTO)
    private Integer id;
    private Integer time;
    private Integer user;
    private String info;
}
