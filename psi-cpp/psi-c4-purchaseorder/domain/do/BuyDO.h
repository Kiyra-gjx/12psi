#pragma once

#ifndef _BUY_DO_H
#define _BUY_DO_H
#include "DoInclude.h"

/**
 * 采购单 数据库实体类
 */
class BuyDO : public BaseDO {
    // 编号
    MYSQL_SYNTHESIZE(string, id, Id);
    // 关联单据
    MYSQL_SYNTHESIZE(string, source, Source);
    // 所属组织
    MYSQL_SYNTHESIZE(string, frame, Frame);
    // 供应商
    MYSQL_SYNTHESIZE(string, supplier, Supplier);
    // 单据时间（数据表为datetime，此处用string存储时间字符串，如"2025-10-28 10:00:00"）
    MYSQL_SYNTHESIZE(string, time, Time);
    // 单据编号
    MYSQL_SYNTHESIZE(string, number, Number);
    // 单据金额（decimal(16,4) 映射为 double）
    MYSQL_SYNTHESIZE(double, total, Total);
    // 实际金额（decimal(16,4) 映射为 double）
    MYSQL_SYNTHESIZE(double, actual, Actual);
    // 实付金额（decimal(16,4) 映射为 double）
    MYSQL_SYNTHESIZE(double, money, Money);
    // 单据费用（decimal(16,4) 映射为 double）
    MYSQL_SYNTHESIZE(double, cost, Cost);
    // 结算账户
    MYSQL_SYNTHESIZE(string, account, Account);
    // 关联人员
    MYSQL_SYNTHESIZE(string, people, People);
    // 物流信息（text 映射为 string）
    MYSQL_SYNTHESIZE(string, logistics, Logistics);
    // 单据附件（text 映射为 string）
    MYSQL_SYNTHESIZE(string, file, File);
    // 备注信息
    MYSQL_SYNTHESIZE(string, data, Data);
    // 扩展信息（text 映射为 string）
    MYSQL_SYNTHESIZE(string, more, More);
    // 审核状态 [0: 未审核 | 1: 已审核]（tinyint 映射为 int）
    MYSQL_SYNTHESIZE(int, examine, Examine);
    // 核销状态 [0: 未核销 | 1: 部分核销 | 2: 已核销]（tinyint 映射为 int）
    MYSQL_SYNTHESIZE(int, nucleus, Nucleus);
    // 费用状态 [0: 未结算 | 1: 部分结算 | 2: 已结算 | 3: 无需结算]（tinyint 映射为 int）
    MYSQL_SYNTHESIZE(int, cse, Cse);
    // 发票状态 [0: 未开票 | 1: 部分开票 | 2: 已开票 | 3: 无需开具]（tinyint 映射为 int）
    MYSQL_SYNTHESIZE(int, invoice, Invoice);
    // 核对状态 [0: 未核对 | 1: 已核对]（tinyint 映射为 int）
    MYSQL_SYNTHESIZE(int, check, Check);
    // 制单人（数据表为 varchar(32)，修正为 string 类型）
    MYSQL_SYNTHESIZE(string, user, User);

public:
    BuyDO() : BaseDO("buy")  // 对应数据库buy表
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("source", "s", source);
        MYSQL_ADD_FIELD("frame", "s", frame);
        MYSQL_ADD_FIELD("supplier", "s", supplier);
        MYSQL_ADD_FIELD("time", "s", time);
        MYSQL_ADD_FIELD("number", "s", number);
        MYSQL_ADD_FIELD("total", "d", total);
        MYSQL_ADD_FIELD("actual", "d", actual);
        MYSQL_ADD_FIELD("money", "d", money);
        MYSQL_ADD_FIELD("cost", "d", cost);
        MYSQL_ADD_FIELD("account", "s", account);
        MYSQL_ADD_FIELD("people", "s", people);
        MYSQL_ADD_FIELD("logistics", "s", logistics);
        MYSQL_ADD_FIELD("file", "s", file);
        MYSQL_ADD_FIELD("data", "s", this->data);
        MYSQL_ADD_FIELD("more", "s", more);
        MYSQL_ADD_FIELD("examine", "i", examine);
        MYSQL_ADD_FIELD("nucleus", "i", nucleus);
        MYSQL_ADD_FIELD("cse", "i", cse);
        MYSQL_ADD_FIELD("invoice", "i", invoice);
        MYSQL_ADD_FIELD("check", "i", check);
        MYSQL_ADD_FIELD("user", "s", user);  // 占位符修正为 "s"，匹配 string 类型
    }
};

// 给buyDO智能指针设定一个别名方便使用
typedef std::shared_ptr<BuyDO> PtrBuyDO;

#endif // !_BUY_DO_H