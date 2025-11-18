#pragma once
#include "DoInclude.h"

class SreDO : public BaseDO {
	//添加字段成员对象
	//退货单id
	MYSQL_SYNTHESIZE(string, id, Id);
	//关联单据|SELL
	MYSQL_SYNTHESIZE(string, source, Source);
	//所属组织
	MYSQL_SYNTHESIZE(string, frame, Frame);
	//客户
	MYSQL_SYNTHESIZE(string, customer, Customer);// 修改大小写！！！！！！！！
	//单据时间
	MYSQL_SYNTHESIZE(string, time, Time);
	//单据编号
	MYSQL_SYNTHESIZE(string, number, Number);
	//单据金额
	MYSQL_SYNTHESIZE(double, total, Total);// 单据金额（修正为double）！！！！！！！！！
	//实际金额
	MYSQL_SYNTHESIZE(double, actual, Actual);
	//实付金额
	MYSQL_SYNTHESIZE(double, money, Money);
	//单据费用
	MYSQL_SYNTHESIZE(double, cost, Cost);
	//结算账户
	MYSQL_SYNTHESIZE(string, account, Account);
	//关联人员
	MYSQL_SYNTHESIZE(string, people, People);
	//物流信息
	MYSQL_SYNTHESIZE(string, logistics, Logistics);
	//单据附件
	MYSQL_SYNTHESIZE(string, file, File);
	//备注信息
	MYSQL_SYNTHESIZE(string, data, Data);
	//扩展信息
	MYSQL_SYNTHESIZE(string, more, More);
	//审核状态[0:未审核|1:已审核]
	MYSQL_SYNTHESIZE(char, examine, Examine);
	//核销状态[0:未核销|1:部分核销|2:已核销]
	MYSQL_SYNTHESIZE(char, nucleus, Nucleus);
	//费用状态[0:未结算|1:部分解释|2:已结算|3:无需结算]
	MYSQL_SYNTHESIZE(char, cse, Cse);
	//发票状态[0:未开票|1:部分开票|2:已开票|3:无需开票]
	MYSQL_SYNTHESIZE(char, invoice, Invoice);
	//核对状态[0:未核对|1:已核对]
	MYSQL_SYNTHESIZE(char, check, Check);
	//制单人
	MYSQL_SYNTHESIZE(string, user, User);

	//为DO类添加对应的字段域成员对象
public:
	SreDO() : BaseDO("sre") {
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("source", "s", source);
		MYSQL_ADD_FIELD_NULLABLE("frame", "s", frame, false);
		MYSQL_ADD_FIELD_NULLABLE("customer", "s", customer, false);
		MYSQL_ADD_FIELD_NULLABLE("time", "dt", time, false);
		MYSQL_ADD_FIELD_NULLABLE("number", "s", number, false);
		MYSQL_ADD_FIELD_NULLABLE("total", "d", total, false);// 类型改为double！！！！！！
		MYSQL_ADD_FIELD_NULLABLE("actual", "d", actual, false);
		MYSQL_ADD_FIELD_NULLABLE("money", "d", money, false);
		MYSQL_ADD_FIELD_NULLABLE("cost", "d", cost, false);

		MYSQL_ADD_FIELD("account", "s", account);
		MYSQL_ADD_FIELD("people", "s", people);
		MYSQL_ADD_FIELD("logistics", "s", logistics);
		MYSQL_ADD_FIELD("file", "s", file);
		MYSQL_ADD_FIELD("data", "s", this->data);// data修改为this->data 
		MYSQL_ADD_FIELD("more", "s", more);

		MYSQL_ADD_FIELD_NULLABLE("examine", "i", examine, false);
		MYSQL_ADD_FIELD_NULLABLE("nucleus", "i", nucleus, false);
		MYSQL_ADD_FIELD_NULLABLE("cse", "i", cse, false);
		MYSQL_ADD_FIELD_NULLABLE("invoice", "i", invoice, false);
		MYSQL_ADD_FIELD_NULLABLE("check", "i", check, false);
		MYSQL_ADD_FIELD_NULLABLE("user", "s", user, false);
	}
};

class SreViewDO : public SreDO {
	//核销金额
	MYSQL_SYNTHESIZE(double, writeOffMoney, WriteOffMoney);
};

typedef std::shared_ptr<SreDO> PtrSreDO;
typedef std::shared_ptr<SreViewDO> PtrSreViewDO;
