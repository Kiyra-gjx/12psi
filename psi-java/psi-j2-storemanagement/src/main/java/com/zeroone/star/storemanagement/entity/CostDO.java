package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.TableField;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDate;

@Data
public class CostDO {

  private String id;

  private String type;

  @TableField("class")
  private String cls;

  private LocalDate time;

  private String iet;

  private BigDecimal money;

  private String data;

  private BigDecimal settle;

  private int state;


}
