#pragma once

#ifndef _BRE_BILL_DO_
#define _BRE_BILL_DO_
#include "DoInclude.h"



/**
 * 采购退货单核销详情
 */
class BreBillDO : public BaseDO
{
	// 编号
	MYSQL_SYNTHESIZE(string, id, Id);
	// 所属单据
	MYSQL_SYNTHESIZE(int, pid, Pid);
	// 核销类型
	MYSQL_SYNTHESIZE(string, type, Type);
	// 关联单据
	MYSQL_SYNTHESIZE(int, source, Source);
	// 单据时间
	MYSQL_SYNTHESIZE(int, time, Time);
	// 核销金额
	MYSQL_SYNTHESIZE(double, money, Money);
public:
	BreBillDO() : BaseDO("write_off")  // 这里表名可根据实际情况修改
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("pid", "i", pid);
		MYSQL_ADD_FIELD("type", "s", type);
		MYSQL_ADD_FIELD("source", "i", source);
		MYSQL_ADD_FIELD("time", "i", time);
		MYSQL_ADD_FIELD("money", "d", money);
	}
};

// 给BreBillDO智能指针设定一个别名方便使用
typedef std::shared_ptr<BreBillDO> PtrBreBillDO;

#endif // !_BRE_BILL_DO_