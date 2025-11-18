#pragma once
#ifndef _BUY_BILL_DO_
#define _BUY_BILL_DO_
#include "DoInclude.h"

//采购单核销详情 数据库实体类
class BuyBillDO : public BaseDO
{
	//主键ID
	MYSQL_SYNTHESIZE(string, id, Id);
	//所属单据
	MYSQL_SYNTHESIZE(string, pid, Pid);
	//核销类型
	MYSQL_SYNTHESIZE(string, type, Type);
	//关联单据
	MYSQL_SYNTHESIZE(string, source, Source);
	//单据时间
	MYSQL_SYNTHESIZE(string, time, Time);
	//核销金额
	MYSQL_SYNTHESIZE(double, money, Money);

public:
	BuyBillDO() : BaseDO("buy_bill")// 对应数据库buy_bill表
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("pid", "s", pid);
		MYSQL_ADD_FIELD("type", "s", type);
		MYSQL_ADD_FIELD("source", "s", source);
		MYSQL_ADD_FIELD("time", "s", time);
		MYSQL_ADD_FIELD("money", "d", money);
	}
};

// 定义智能指针别名
typedef std::shared_ptr<BuyBillDO> PtrBuyBillDo;
#endif // !_BUY_BILL_DO_