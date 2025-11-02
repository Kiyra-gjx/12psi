package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

@Data
public class RoomInfoDO {

    private String id;

    private String pid;

    private String type;

    @TableField("class")
    private String cls;

    private String info;

    private LocalDateTime time;

    private Integer direction;

    private BigDecimal price;

    private BigDecimal nums;
}
