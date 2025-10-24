package com.zeroone.star.storemanagement.entity;

import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
public class Cost {

  private String id;
  private String type;
  private String cls;
  private LocalDateTime time;
  private String iet;
  private BigDecimal money;
  private String data;
  private BigDecimal settle;
  private int state;


}
