#ifndef _SRE_BILL_DO_
#define _SRE_BILL_DO_

#include "DoInclude.h"


class SrebillDO : public BaseDO
{
	//id
	MYSQL_SYNTHESIZE(string, id, Id);
	//所属账户
	MYSQL_SYNTHESIZE(string, pid, Pid);
	//类型
	MYSQL_SYNTHESIZE(string, type, Type);
	//关联单据
	MYSQL_SYNTHESIZE(string, source, Source);
	//时间
	MYSQL_SYNTHESIZE(string, time, Time);
	//核销金额
	MYSQL_SYNTHESIZE(double, money, Money);


public:
	SrebillDO() : BaseDO("sre_bill")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("pid", "s", pid);
		MYSQL_ADD_FIELD("type", "s", type);
		MYSQL_ADD_FIELD("source", "s", source);
		MYSQL_ADD_FIELD("time", "dt", time);
		MYSQL_ADD_FIELD("money", "d", money);
	}

};
// 定义智能指针
typedef std::shared_ptr<SrebillDO> PtSrebillDO;


#endif