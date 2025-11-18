#include "stdafx.h"
#include "SellDAO.h"
#include "SellMapper.h"
#include "id/UuidFacade.h"
#define SORT_ORDER(x) ((x == 1)?"ASC":"DESC")

std::list<SellDO> SellDAO::selectByNumber(const std::string& number)
{
	// 构建查询SQL
	std::string sql = "SELECT * FROM `sell` WHERE `number` = ?";

	// 设置参数
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, number);
	OATPP_LOGD("SELL", sql.c_str());

	// 执行查询
	//auto resultSet = sqlSession->executeQuery(sql, params);
	SellMapper mapper;
	return sqlSession->executeQuery<SellDO>(sql, mapper, params);
}

std::string SellDAO::queryConditionBuilder(const SellListQuery::Wrapper& query, SqlParams& params) {

	stringstream sqlCondition;
	//根据编号内联详情表得到商品编号，根据商品编号内
	// 联商品表得到商品名称
	if (query->name) {
		sqlCondition << R"(
		INNER JOIN (SELECT pid,goods FROM sell_info) inf ON sell.id=inf.pid
		INNER JOIN (SELECT id,name FROM goods) g ON inf.goods=g.id
	)";
	}

	//构建WHERE用于筛选
	sqlCondition << " WHERE 1=1 ";
	if (query->name) {
		sqlCondition << " AND g.`name` LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	if (query->number) {
		sqlCondition << " AND sell.number LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->number.getValue(""));
	}
	if (query->customer) {
		sqlCondition << " AND sell.customer=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->customer.getValue(""));
	}
	if (query->people) {
		sqlCondition << " AND sell.people=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->people.getValue(""));
	}
	if (query->begintime) {
		sqlCondition << " AND sell.time >= ?";
		SQLPARAMS_PUSH(params, "dt", std::string, query->begintime.getValue(""));
	}
	if (query->endtime) {
		sqlCondition << " AND sell.time <= ?";
		SQLPARAMS_PUSH(params, "dt", std::string, query->endtime.getValue(""));
	}
	if (query->user) {
		sqlCondition << " AND sell.user=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->user.getValue(""));
	}
	if (query->examine) {
		sqlCondition << " AND examine=?";
		SQLPARAMS_PUSH(params, "i", int32_t, query->examine.getValue(0));
	}
	if (query->nucleus) {
		sqlCondition << " AND nucleus=?";
		SQLPARAMS_PUSH(params, "i", int32_t, query->nucleus.getValue(0));
	}
	if (query->cse) {
		sqlCondition << " AND cse=?";
		SQLPARAMS_PUSH(params, "i", int32_t, query->cse.getValue(0));
	}
	if (query->invoice) {
		sqlCondition << " AND invoice=?";
		SQLPARAMS_PUSH(params, "i", int32_t, query->invoice.getValue(0));
	}
	if (query->check) {
		sqlCondition << " AND `check`=?";
		SQLPARAMS_PUSH(params, "i", int32_t, query->check.getValue(0));
	}
	if (query->data) {
		sqlCondition << " AND `data` LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->user.getValue(""));
	}

	return sqlCondition.str();
}

std::string SellDAO::queryOrderBuilder(const SellListQuery::Wrapper& query, SqlParams& params) {
	stringstream sqlOrder;
	sqlOrder << " ORDER BY ";
	if (query->timeSortOrder.get()) {
		sqlOrder << " time " << SORT_ORDER(query->timeSortOrder.getValue(false));
	}
	else if (query->numberSortOrder.get()) {
		sqlOrder << " number " << SORT_ORDER(query->numberSortOrder.getValue(false));
	}
	else if (query->totalSortOrder.get()) {
		sqlOrder << " total " << SORT_ORDER(query->totalSortOrder.getValue(false));
	}
	else if (query->actualSortOrder.get()) {
		sqlOrder << " actual " << SORT_ORDER(query->actualSortOrder.getValue(false));
	}
	else if (query->moneySortOrder.get()) {
		sqlOrder << " sell_money " << SORT_ORDER(query->moneySortOrder.getValue(false));
	}
	else if (query->costSortOrder.get()) {
		sqlOrder << " cost " << SORT_ORDER(query->costSortOrder.getValue(false));
	}
	else {
		sqlOrder << " NULL";
	}
	return sqlOrder.str();
}

uint64_t SellDAO::count(const SellListQuery::Wrapper& query) {
	SqlParams params;
	std::string sql = "SELECT COUNT(*) FROM `sell` ";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

uint64_t SellDAO::countById(const std::string& id) {
	std::string sql = "SELECT COUNT(*) FROM `sell` WHERE id = ?";
	return sqlSession->executeQueryNumerical(sql, "%s", id);
}

std::list<PtrSellViewDO> SellDAO::selectWithPage(const SellListQuery::Wrapper& query) {
	SqlParams params;
	//获取基础信息
	std::string sql = R"(
	SELECT 
	sell.id `id`,
	sell.frame frame,
	sell.customer customer,
	sell.time `time`,
	sell.number `number`,
	sell.total total,
	sell.actual actual,
	sell.money sell_money,
	bill.money bill_money,
	sell.cost cost,
	sell.people people,
	sell.examine examine,
	sell.nucleus nucleus,
	sell.cse cse,
	sell.invoice invoice,
	sell.check `check`,
	sell.user `user`,
	sell.data `data`
	FROM sell
	INNER JOIN 
	(SELECT pid,money FROM sell_bill) bill 
	ON bill.pid=sell.id
	)";
	//构建查询条件
	sql += queryConditionBuilder(query, params);
	//构建排序语句
	sql += queryOrderBuilder(query, params);
	//构建分页条件
	sql += " LIMIT " + std::to_string(query->pageSize) + " OFFSET " + std::to_string((query->pageIndex - 1) * query->pageSize);
	return sqlSession->executeQuery<PtrSellViewDO>(sql, PtrSellViewMapper(), params);
}

PtrSellViewDO SellDAO::selectById(const std::string& id) {
	if (id.empty()) return nullptr;
	SqlParams params;
	std::string sql = R"(
	SELECT 
	sell.id `id`,
	sell.frame frame,
	sell.customer customer,
	sell.time `time`,
	sell.number `number`,
	sell.total total,
	sell.actual actual,
	sell.money sell_money,
	bill.money bill_money,
	sell.cost cost,
	sell.people people,
	sell.examine examine,
	sell.nucleus nucleus,
	sell.cse cse,
	sell.invoice invoice,
	sell.check `check`,
	sell.user `user`,
	sell.data `data`
	FROM sell
	INNER JOIN 
	(SELECT pid,money FROM sell_bill) bill 
	ON bill.pid=sell.id
    WHERE sell.id=?
	)";
	return sqlSession->executeQueryOne<PtrSellViewDO>(sql, PtrSellViewMapper(), "%s", id);
}


bool SellDAO::deleteById(const std::string& id) {
	if (id.empty()) return false;

	SqlParams params;
	std::string sql = "DELETE FROM `sell` WHERE `id`=?";
	SQLPARAMS_PUSH(params, "s", std::string, id);
	return sqlSession->executeUpdate(sql, params) > 0;
}

bool SellDAO::importData(const PayloadDTO& payload, const SellImportDTO::Wrapper& dto, std::string& sell_uuid) {
	::UuidFacade uf;
	sell_uuid = uf.genUuid();

	std::string sql =
		"INSERT INTO `sell` ("
		"`id`,`frame`,`customer`,`time`,`number`,`total`,`actual`,`people`,"
		"`cost`,`account`,`logistics`,`file`,`data`,`more`,`examine`,`nucleus`,"
		"`cse`,`invoice`,`check`,`user`"
		") VALUES ('" + sell_uuid + "','" + dto->frame + "','" + dto->customer + "','" + dto->time + "','" + dto->number + "'," +
		(dto->total ? std::to_string(dto->total) : std::to_string(dto->actual)) + "," +
		std::to_string(dto->actual) + ",'" + (dto->people ? std::string(dto->people) : "") + "'," +
		// cost/account 可为空时按你的表结构处理，这里给 NULL
		"NULL,NULL,'" + (dto->logistics ? std::string(dto->logistics) : "") + "','" +
		(dto->file ? std::string(dto->file) : "") + "','" +
		(dto->data ? std::string(dto->data) : "") + "','" +
		(dto->more ? std::string(dto->more) : "") + "'," +
		std::to_string(dto->examine ? int(*dto->examine) : 0) + "," +
		std::to_string(dto->nucleus ? int(*dto->nucleus) : 0) + "," +
		std::to_string(dto->cse ? int(*dto->cse) : 0) + "," +
		std::to_string(dto->invoice ? int(*dto->invoice) : 0) + "," +
		std::to_string(dto->check ? int(*dto->check) : 0) + ",'" +
		payload.getUsername() + "')";

	return sqlSession->executeUpdate(sql) != 0;
}

bool SellDAO::approveById(const std::string& id) {
	if (id.empty()) return false;
	try {
		SqlParams params;
		std::string sql = "UPDATE sell SET examine = 1 WHERE id = ?";
		SQLPARAMS_PUSH(params, "s", std::string, id);
		int n = sqlSession->executeUpdate(sql, params);
		return n > 0;
	}
	catch (...) { return false; }
}

bool SellDAO::unapproveById(const std::string& id) {
	if (id.empty()) return false;
	try {
		SqlParams params;
		std::string sql = "UPDATE sell SET examine = 0 WHERE id = ?";
		SQLPARAMS_PUSH(params, "s", std::string, id);
		int n = sqlSession->executeUpdate(sql, params);
		return n > 0;
	}
	catch (...) { return false; }
}

bool SellDAO::isOrderApproved(const std::string& id) {
	if (id.empty()) return false;
	try {
		SqlParams params;
		std::string sql = "SELECT COUNT(*) FROM sell WHERE id = ? AND examine = 1";
		SQLPARAMS_PUSH(params, "s", std::string, id);
		int c = sqlSession->executeQueryNumerical(sql, params);
		return c > 0;
	}
	catch (...) { return false; }
}