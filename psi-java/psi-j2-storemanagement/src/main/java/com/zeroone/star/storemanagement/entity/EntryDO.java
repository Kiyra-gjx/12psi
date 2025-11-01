package com.zeroone.star.storemanagement.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.zeroone.star.project.dto.j2.store.FileDTO;
import com.zeroone.star.project.dto.j2.store.LogisticsDTO;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.List;

@Data
public class EntryDO {
        @TableId(type = IdType.ASSIGN_ID)
        private String id;

        private String supplier;

        private String frame;

        private LocalDateTime time;

        private String number;

        private Integer type;

        private BigDecimal total;

        private BigDecimal cost;

        private String people;

        private String logistics;

        private String file;

        private String data;

        private Object more;

        private Integer examine;

        private Integer cse;

        private Integer check;

        private String user;

}
