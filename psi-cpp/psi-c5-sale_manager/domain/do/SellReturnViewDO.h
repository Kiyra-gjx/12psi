#pragma once
#ifndef _SELL_RETURN_VIEW_DO_
#define _SELL_RETURN_VIEW_DO_
#include "DoInclude.h"

//暂时实现和定义SellReturnDO和SellReturnInfoDO
class SellReturnDO : public BaseDO {
public:
    // 退货单ID
    MYSQL_SYNTHESIZE(string, id, Id);
    // 关联销售单ID
    MYSQL_SYNTHESIZE(string, source, Source);
    // 所属组织
    MYSQL_SYNTHESIZE(string, frame, Frame);
    // 客户
    MYSQL_SYNTHESIZE(string, customer, Customer);
    // 单据时间
    MYSQL_SYNTHESIZE(string, time, Time);
    // 单据编号
    MYSQL_SYNTHESIZE(string, number, Number);
    // 单据金额
    MYSQL_SYNTHESIZE(double, total, Total);
    // 实际金额
    MYSQL_SYNTHESIZE(double, actual, Actual);
    // 实付金额
    MYSQL_SYNTHESIZE(double, money, Money);
    // 单据费用
    MYSQL_SYNTHESIZE(double, cost, Cost);
    // 结算账户
    MYSQL_SYNTHESIZE(string, account, Account);
    // 关联人员
    MYSQL_SYNTHESIZE(string, people, People);
    // 物流信息
    MYSQL_SYNTHESIZE(string, logistics, Logistics);
    // 单据附件
    MYSQL_SYNTHESIZE(string, file, File);
    // 备注信息
    MYSQL_SYNTHESIZE(string, data, Data);
    // 扩展信息
    MYSQL_SYNTHESIZE(string, more, More);
    // 审核状态（0未审核/1已审核）
    MYSQL_SYNTHESIZE(int, examine, Examine);
    // 核销状态
    MYSQL_SYNTHESIZE(int, nucleus, Nucleus);
    // 费用状态
    MYSQL_SYNTHESIZE(int, cse, Cse);
    // 发票状态
    MYSQL_SYNTHESIZE(int, invoice, Invoice);
    // 核对状态
    MYSQL_SYNTHESIZE(int, check, Check);
    // 制单人
    MYSQL_SYNTHESIZE(string, user, User);
public:
    SellReturnDO() : BaseDO("sre")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("source", "s", source);
        MYSQL_ADD_FIELD("frame", "s", frame);
        MYSQL_ADD_FIELD("customer", "s", customer);
        MYSQL_ADD_FIELD("time", "dt", time);
        MYSQL_ADD_FIELD("number", "s", number);
        MYSQL_ADD_FIELD("total", "d", total);
        MYSQL_ADD_FIELD("actual", "d", actual);
        MYSQL_ADD_FIELD("money", "d", money);
        MYSQL_ADD_FIELD("cost", "d", cost);
        MYSQL_ADD_FIELD("account", "s", account);
        MYSQL_ADD_FIELD("people", "s", people);
        MYSQL_ADD_FIELD("logistics", "s", logistics);
        MYSQL_ADD_FIELD("file", "s", file);
        MYSQL_ADD_FIELD("data", "s", data);
        MYSQL_ADD_FIELD("more", "s", more);
        MYSQL_ADD_FIELD("examine", "i", examine);
        MYSQL_ADD_FIELD("nucleus", "i", nucleus);
        MYSQL_ADD_FIELD("cse", "i", cse);
        MYSQL_ADD_FIELD("invoice", "i", invoice);
        MYSQL_ADD_FIELD("check", "i", check);
        MYSQL_ADD_FIELD("user", "s", user);
    }
};

class SellReturnInfoDO : public BaseDO {
public:
    // 明细ID（主键）
    MYSQL_SYNTHESIZE(string, id, Id);
    // 所属退货单ID（关联 sre 表的 id）
    MYSQL_SYNTHESIZE(string, pid, Pid);
    // 关联销售单明细ID
    MYSQL_SYNTHESIZE(string, source, Source);
    // 关联的商品ID
    MYSQL_SYNTHESIZE(string, goods, Goods);
    // 商品辅助属性（如规格、颜色）
    MYSQL_SYNTHESIZE(string, attr, Attr);
    // 计量单位
    MYSQL_SYNTHESIZE(string, unit, Unit);
    // 所属仓库
    MYSQL_SYNTHESIZE(string, warehouse, Warehouse);
    // 商品批次号
    MYSQL_SYNTHESIZE(string, batch, Batch);
    // 生产日期
    MYSQL_SYNTHESIZE(string, mfd, Mfd);
    // 退货单价
    MYSQL_SYNTHESIZE(double, price, Price);
    // 退货数量
    MYSQL_SYNTHESIZE(double, nums, Nums);
    // 商品序列号（多个用逗号分隔）
    MYSQL_SYNTHESIZE(string, serial, Serial);
    // 折扣率（百分比）
    MYSQL_SYNTHESIZE(double, discount, Discount);
    // 折扣金额
    MYSQL_SYNTHESIZE(double, dsc, Dsc);
    // 明细总金额（未折扣）
    MYSQL_SYNTHESIZE(double, total, Total);
    // 税率（百分比）
    MYSQL_SYNTHESIZE(double, tax, Tax);
    // 税额
    MYSQL_SYNTHESIZE(double, tat, Tat);
    // 价税合计（折扣后）
    MYSQL_SYNTHESIZE(double, tpt, Tpt);
    // 备注信息
    MYSQL_SYNTHESIZE(string, data, Data);
public:
    // 构造函数：指定对应的数据表名 "sre_info"，并映射所有字段
    SellReturnInfoDO() : BaseDO("sre_info")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("pid", "s", pid);
        MYSQL_ADD_FIELD("source", "s", source);
        MYSQL_ADD_FIELD("goods", "s", goods);
        MYSQL_ADD_FIELD("attr", "s", attr);
        MYSQL_ADD_FIELD("unit", "s", unit);
        MYSQL_ADD_FIELD("warehouse", "s", warehouse);
        MYSQL_ADD_FIELD("batch", "s", batch);
        MYSQL_ADD_FIELD("mfd", "dt", mfd);
        MYSQL_ADD_FIELD("price", "d", price);
        MYSQL_ADD_FIELD("nums", "d", nums);
        MYSQL_ADD_FIELD("serial", "s", serial);
        MYSQL_ADD_FIELD("discount", "d", discount);
        MYSQL_ADD_FIELD("dsc", "d", dsc);
        MYSQL_ADD_FIELD("total", "d", total);
        MYSQL_ADD_FIELD("tax", "d", tax);
        MYSQL_ADD_FIELD("tat", "d", tat);
        MYSQL_ADD_FIELD("tpt", "d", tpt);
        MYSQL_ADD_FIELD("data", "s", data);
    }
};

// 定义智能指针别名，解决 !!商品明细!! 里的 `PtrSellReturnInfoDO` 未定义问题
// 注意这里的智能指针类型为 `PtrSellReturnInfoDO`，如果名字有冲突，请自行修改
typedef std::shared_ptr<SellReturnInfoDO> PtrSellReturnInfoDO;
typedef std::shared_ptr<SellReturnDO> PtrSellReturnDO;

/**
 * 销售退货单视图实体类
 */
class SellReturnViewDO : public SellReturnDO, public SellReturnInfoDO {
public:
    // 1. 客户相关（列表/报表场景需用）
    MYSQL_SYNTHESIZE(string, customerName, CustomerName);        // 客户ID对应的客户名称（关联customer表）
    MYSQL_SYNTHESIZE(string, customerNumber, CustomerNumber);    // 客户编号

    // 2. 仓库相关（报表场景需用）
    MYSQL_SYNTHESIZE(string, warehouseName, WarehouseName);      // 仓库ID对应的仓库名称（关联warehouse表）

    // 3. 人员相关（详情场景需用）
    MYSQL_SYNTHESIZE(string, peopleName, PeopleName);            // 关联人员姓名
    MYSQL_SYNTHESIZE(string, userName, UserName);                // 制单人姓名

    // 4. 账户相关（详情场景需用）
    MYSQL_SYNTHESIZE(string, accountName, AccountName);          // 结算账户名称

    // 5. 原销售单相关（详情场景需用）
    MYSQL_SYNTHESIZE(string, sourceNumber, SourceNumber);        // 原销售单编号
    MYSQL_SYNTHESIZE(string, sourceTime, SourceTime);            // 原销售单时间

    // 6. 商品明细（详情/报表场景需用）
    MYSQL_SYNTHESIZE(std::vector<PtrSellReturnInfoDO>, items, Items); // 商品明细列表（关联sre_info表）

    // 7. 状态名称（所有场景可能需用）
    MYSQL_SYNTHESIZE(string, examineStatusName, ExamineStatusName);   // 审核状态编码对应的名称
    MYSQL_SYNTHESIZE(string, nucleusStatusName, NucleusStatusName);   // 核销状态编码对应的名称
    MYSQL_SYNTHESIZE(string, cseStatusName, CseStatusName);           // 费用状态编码对应的名称
    MYSQL_SYNTHESIZE(string, invoiceStatusName, InvoiceStatusName);   // 发票状态编码对应的名称
    MYSQL_SYNTHESIZE(string, checkStatusName, CheckStatusName);       // 核对状态编码对应的名称

    // 8. 商品信息扩展（报表场景需用）
    MYSQL_SYNTHESIZE(string, goodsName, GoodsName);               // 商品名称
    MYSQL_SYNTHESIZE(string, goodsNumber, GoodsNumber);           // 商品编号
    MYSQL_SYNTHESIZE(string, goodsSpec, GoodsSpec);               // 商品规格

public:
    // 构造函数：复用父类SellReturnDO的构造（自动关联sre表字段）
    SellReturnViewDO() : SellReturnDO() {}

    // 便捷构造：从主表DO初始化，快速填充核心字段
    //explicit SellReturnViewDO(PtrSellReturnDO mainDO) {
    //    if (mainDO) {
    //        this->id = mainDO->id;
    //        this->source = mainDO->source;
    //        this->frame = mainDO->frame;
    //        this->customer = mainDO->customer;
    //        this->time = mainDO->time;
    //        this->number = mainDO->number;
    //        this->total = mainDO->total;
    //        this->actual = mainDO->actual;
    //        this->money = mainDO->money;
    //        this->cost = mainDO->cost;
    //        this->account = mainDO->account;
    //        this->people = mainDO->people;
    //        this->logistics = mainDO->logistics;
    //        this->file = mainDO->file;
    //        this->data = mainDO->data;
    //        this->more = mainDO->more;
    //        this->examine = mainDO->examine;
    //        this->nucleus = mainDO->nucleus;
    //        this->cse = mainDO->cse;
    //        this->invoice = mainDO->invoice;
    //        this->check = mainDO->check;
    //        this->user = mainDO->user;
    //         //... 其他主表字段按需复制
    //    }
    //}

    // 添加商品明细项
    void addItem(PtrSellReturnInfoDO item) {
        items->push_back(item);
    }

    // 获取商品明细列表
    std::vector<PtrSellReturnInfoDO> getItems() const {
        return *items;
    }

    // 清空商品明细
    void clearItems() {
        items->clear();
    }
};

// 定义销售退货单视图的智能指针
typedef std::shared_ptr<SellReturnViewDO> PtrSellReturnViewDO;

#endif // !_SELL_RETURN_VIEW_DO_