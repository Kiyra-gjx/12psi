#ifndef _PURCHASE_DING_DAN_DO_
#define _PURCHASE_DING_DAN_DO_
#include "DoInclude.h"

/**
 * 采购订单数据库实体类（对应bor表）
 */
class PurchaseDingDanDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 关联单据
	MYSQL_SYNTHESIZE(string, source, Source);
	// 所属组织
	MYSQL_SYNTHESIZE(string, frame, Frame);
	// 供应商
	MYSQL_SYNTHESIZE(string, supplier, Supplier);
	// 单据时间
	MYSQL_SYNTHESIZE(string, time, Time);
	// 单据编号
	MYSQL_SYNTHESIZE(string, number, Number);
	// 单据金额
	MYSQL_SYNTHESIZE(double, total, Total);
	// 实际金额
	MYSQL_SYNTHESIZE(double, actual, Actual);
	// 关联人员
	MYSQL_SYNTHESIZE(string, people, People);
	// 到货时间
	MYSQL_SYNTHESIZE(string, arrival, Arrival);
	// 物流信息
	MYSQL_SYNTHESIZE(string, logistics, Logistics);
	// 单据附件
	MYSQL_SYNTHESIZE(string, file, File);
	// 备注信息
	MYSQL_SYNTHESIZE(string, data, Data);
	// 扩展信息
	MYSQL_SYNTHESIZE(string, more, More);
	// 审核状态[0:未审核|1:已审核]
	MYSQL_SYNTHESIZE(int, examine, Examine);
	// 入库状态[0:未入库|1:部分入库|2:已入库|3:关闭]
	MYSQL_SYNTHESIZE(int, state, State);
	// 制单人
	MYSQL_SYNTHESIZE(string, user, User);

public:
	PurchaseDingDanDO() : BaseDO("bor")  // 绑定数据库表名为bor
	{
		// 注册主键字段（id）
		MYSQL_ADD_FIELD_PK("id", "s", id);
		// 注册普通字段（字段名，类型标识，成员变量）
		MYSQL_ADD_FIELD("source", "s", source);
		MYSQL_ADD_FIELD("frame", "s", frame);
		MYSQL_ADD_FIELD("supplier", "s", supplier);
		MYSQL_ADD_FIELD("time", "s", time);  // datetime用字符串存储
		MYSQL_ADD_FIELD("number", "s", number);
		MYSQL_ADD_FIELD("total", "d", total);  // decimal对应double类型
		MYSQL_ADD_FIELD("actual", "d", actual);
		MYSQL_ADD_FIELD("people", "s", people);
		MYSQL_ADD_FIELD("arrival", "s", arrival);  // datetime用字符串存储
		MYSQL_ADD_FIELD("logistics", "s", logistics);  // text对应string
		MYSQL_ADD_FIELD("file", "s", file);
		MYSQL_ADD_FIELD("data", "s", data);
		MYSQL_ADD_FIELD("more", "s", more);
		MYSQL_ADD_FIELD("examine", "i", examine);  // tinyint对应int
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("user", "s", user);
	}
};

// 定义智能指针别名，方便使用
typedef std::shared_ptr<PurchaseDingDanDO> PtrPurchaseDingDanDO;
#endif // !_PURCHASE_DING_DAN_DO_