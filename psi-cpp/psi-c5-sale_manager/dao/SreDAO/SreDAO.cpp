#include "stdafx.h"
#include "SreDAO.h"
#include "SreMapper.h"
#include "id/UuidFacade.h"

//转化数字为排序方式(0：降序1:升序)
#define SORT_ORDER(x) ((x == 1)?"ASC":"DESC")

std::string SreDAO::queryConditionBuilder(const SreListQuery::Wrapper& query, SqlParams& params) {
	stringstream sqlCondition;
	//根据编号内联详情表得到商品编号，根据商品编号内联商品表得到商品名称
	if (query->name) {
		sqlCondition << R"(
		INNER JOIN (SELECT pid,goods FROM sre_info) inf ON sre.id=inf.pid
		INNER JOIN (SELECT id,name FROM goods) g ON inf.goods=g.id
	)";
	}

	//构建WHRER用于筛选
	sqlCondition << " WHERE 1=1 ";
	if (query->name) {
		sqlCondition << " AND g.`name` LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	if (query->number) {
		sqlCondition << " AND sre.number LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->number.getValue(""));
	}
	if (query->customer) {
		sqlCondition << " AND sre.customer=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->customer.getValue(""));
	}
	if (query->people) {
		sqlCondition << " AND sre.people=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->people.getValue(""));
	}
	if (query->begintime) {
		sqlCondition << " AND sre.time >= ?";
		SQLPARAMS_PUSH(params, "dt", std::string, query->begintime.getValue(""));
	}
	if (query->endtime) {
		sqlCondition << " AND sre.time <= ?";
		SQLPARAMS_PUSH(params, "dt", std::string, query->endtime.getValue(""));
	}
	if (query->user) {
		sqlCondition << " AND sre.user=?";
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
		sqlCondition << " AND check=?";
		SQLPARAMS_PUSH(params, "i", int32_t, query->check.getValue(0));
	}
	if (query->data) {
		sqlCondition << " AND `data` LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->user.getValue(""));
	}
	return sqlCondition.str();
}

std::string SreDAO::queryOrderBuilder(const SreListQuery::Wrapper& query, SqlParams& params) {
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
		sqlOrder << " sre_money " << SORT_ORDER(query->moneySortOrder.getValue(false));
	}
	else if (query->costSortOrder.get()) {
		sqlOrder << " cost " << SORT_ORDER(query->costSortOrder.getValue(false));
	}
	else {
		sqlOrder << " NULL";
	}
	return sqlOrder.str();
}

uint64_t SreDAO::count(const SreListQuery::Wrapper& query) {
	SqlParams params;
	std::string sql = "SELECT COUNT(*) FROM sre";
	sql += queryConditionBuilder(query,params);
	return sqlSession->executeQueryNumerical(sql,params);
}

uint64_t SreDAO::countById(const SreDetailQuery::Wrapper& query) {
	SqlParams params;
	std::string sql = "SELECT COUNT(*) FROM sre WHERE id=?";
	SQLPARAMS_PUSH(params, "s", std::string, query->id.getValue(""));
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<SreViewDO> SreDAO::selectWithPage(const SreListQuery::Wrapper& query) {
	SqlParams params;
	//获取基础信息
	std::string sql = R"(
	SELECT 
	sre.id `id`,
	sre.frame frame,
	sre.customer customer,
	sre.time `time`,
	sre.number `number`,
	sre.total total,
	sre.actual actual,
	sre.money sre_money,
	bill.money bill_money,
	sre.cost cost,
	sre.people people,
	sre.examine examine,
	sre.nucleus nucleus,
	sre.cse cse,
	sre.invoice invoice,
	sre.check `check`,
	sre.user `user`,
	sre.data `data`
	FROM sre
	INNER JOIN 
	(SELECT pid,money FROM sre_bill) bill 
	ON bill.pid=sre.id
	)";
	//构建查询条件
	sql += queryConditionBuilder(query, params);
	//构建排序语句
	sql += queryOrderBuilder(query, params);
	//构建分页条件
	sql += " LIMIT " + std::to_string(query->pageSize) + " OFFSET " + std::to_string((query->pageIndex - 1) * query->pageSize);
	return sqlSession->executeQuery<SreViewDO>(sql, SreMapper(), params);
}

std::list<SreViewDO> SreDAO::selectById(const SreDetailQuery::Wrapper& query) {
	SqlParams params;
	//获取基础信息
	std::string sql = R"(
	SELECT 
	sre.id `id`,
	sre.frame frame,
	sre.customer customer,
	sre.time `time`,
	sre.number `number`,
	sre.total total,
	sre.actual actual,
	sre.money sre_money,
	bill.money bill_money,
	sre.cost cost,
	sre.people people,
	sre.examine examine,
	sre.nucleus nucleus,
	sre.cse cse,
	sre.invoice invoice,
	sre.check `check`,
	sre.user `user`,
	sre.data `data`
	FROM sre
	INNER JOIN 
	(SELECT pid,money FROM sre_bill) bill 
	ON bill.pid=sre.id
	WHERE sre.id=?
	)";
	return sqlSession->executeQuery<SreViewDO>(sql, SreMapper(), "%s", query->id.getValue(""));
}

bool SreDAO::insert(const PtrSreDO& sreDO) {
	try {
		//共插入22个字段
		std::string sql = R"(
			INSERT INTO sre
			(`id`,`source`,`frame`,`customer`,`time`,`number`,`total`,`actual`,`money`,`cost`,`account`,`people`,`logistics`,`file`,`data`,`more`,`user`,`examine`,`nucleus`,`cse`,`invoice`,`check`)
			VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)			 
		)";
		//注意:params的顺序要和insert的顺序完全一致
		SqlParams params;
		SQLPARAMS_PUSH(params, "s", std::string, sreDO->getId());
		SQLPARAMS_PUSH(params, "s", std::string, sreDO->getSource());
		SQLPARAMS_PUSH(params, "s", std::string, sreDO->getFrame());
		SQLPARAMS_PUSH(params, "s", std::string, sreDO->getCustomer());
		SQLPARAMS_PUSH(params, "dt", std::string, sreDO->getTime());
		SQLPARAMS_PUSH(params, "s", std::string, sreDO->getNumber());
		SQLPARAMS_PUSH(params, "d", double, sreDO->getTotal());
		SQLPARAMS_PUSH(params, "d", double, sreDO->getActual());
		SQLPARAMS_PUSH(params, "d", double, sreDO->getMoney());
		SQLPARAMS_PUSH(params, "d", double, sreDO->getCost());

		SQLPARAMS_PUSH(params, "s", std::string, sreDO->getAccount());
		SQLPARAMS_PUSH(params, "s", std::string, sreDO->getPeople());
		SQLPARAMS_PUSH(params, "s", std::string, sreDO->getLogistics());
		SQLPARAMS_PUSH(params, "s", std::string, sreDO->getFile());
		SQLPARAMS_PUSH(params, "s", std::string, sreDO->getData());
		SQLPARAMS_PUSH(params, "s", std::string, sreDO->getMore());
		SQLPARAMS_PUSH(params, "s", std::string, sreDO->getUser());

		SQLPARAMS_PUSH(params, "i", uint32_t, sreDO->getExamine());
		SQLPARAMS_PUSH(params, "i", uint32_t, sreDO->getNucleus());
		SQLPARAMS_PUSH(params, "i", uint32_t, sreDO->getCse());
		SQLPARAMS_PUSH(params, "i", uint32_t, sreDO->getInvoice());
		SQLPARAMS_PUSH(params, "i", uint32_t, sreDO->getCheck());
		
		return sqlSession->executeUpdate(sql, params) > 0;
	}
	catch (std::exception& e) {
		std::cerr << "SreDAO::insert error " << e.what() << std::endl;
		return false;
	}
	return false;

}

// 松额外实现的方法1 ————导出简单报表
std::vector<PtrSreDO> SreDAO::querySimpleList(
	const std::string& startDate,
	const std::string& endDate
) {
	SqlParams params;
	std::string sql = R"(
        SELECT frame, customer, time, number, total, actual, money, cost, people, examine, nucleus, cse, invoice, `check`, `user`, data 
        FROM `sre` 
        WHERE 1=1
    )";

	// 拼接时间范围条件
	if (!startDate.empty()) {
		sql += " AND `time` >= ?";
		SQLPARAMS_PUSH(params, "dt", std::string, startDate);
	}
	if (!endDate.empty()) {
		sql += " AND `time` <= ?";
		SQLPARAMS_PUSH(params, "dt", std::string, endDate);
	}

	//// 执行查询：模板参数指定为SreDO::PtrSreDO，Mapper为SreMapper
	//auto result = sqlSession->executeQuery<PtrSreDO>(sql, SreMapper(), params);
	//return result;
	// 执行查询，获取list结果
	auto listResult = sqlSession->executeQuery<PtrSreDO>(sql, SreSimpleReportMapper(), params);

	//避免空指针——————————————————10.30下午添加
	if (listResult.empty()) {
		return {}; // 空结果直接返回空vector
	}

	// 将list转换为vector
	std::vector<PtrSreDO> vectorResult;
	vectorResult.reserve(listResult.size()); // 预分配内存提升效率
	for (auto& item : listResult) {
		vectorResult.push_back(item);
	}

	return vectorResult;
}

// 松额外实现的方法2 ————导出详细报表
std::vector<PtrSreDetailDO> SreDAO::queryDetailList(
	const std::string& orderNoLike,
	const std::string& customer
	//int examineStatus
) {

	//// 打印传入参数
	//std::cout << "传入 orderNoLike: " << orderNoLike << std::endl;
	//std::cout << "传入 customer: " << customer << std::endl;

	std::vector<PtrSreDetailDO> resultList;

	// 步骤1：查询主表列表（复用主表查询逻辑，只取关键字段）
	SqlParams mainParams;
	std::string mainSql = R"(
    SELECT 
        s.`id`, s.`customer`, s.`time`, s.`number`, s.`total`, s.`examine`, s.`data`,
        s.`cost`, s.`actual`, s.`nucleus`, s.`account`, s.`invoice`, s.`people`, s.`logistics`
    FROM `sre` s
    WHERE 1=1
    )";
	if (!orderNoLike.empty()) {
		mainSql += " AND `id` LIKE CONCAT('%', ?, '%')";
		SQLPARAMS_PUSH(mainParams, "s", std::string, orderNoLike);
	}
	if (!customer.empty()) {
		mainSql += " AND `customer` = ?";
		SQLPARAMS_PUSH(mainParams, "s", std::string, customer);
	}

	auto mainDOList = sqlSession->executeQuery<PtrSreDO>(mainSql, SreDetailReportMapper(), mainParams);


	// ========== 步骤2：对每个主表，查询对应的明细表 ==========
	for (const auto& mainDO : mainDOList) {
		if (!mainDO) continue; // 忽略空对象

		auto detail = std::make_shared<SreDetailDO>();
		detail->mainDO = mainDO; // 关联主表数据

		// 查询明细表：sre_info WHERE pid = 主表ID
		SqlParams itemParams;
		std::string itemSql = R"(
        SELECT 
            si.*, 
            g.`name` AS goodsName,  -- 关联goods表获取商品名称
            g.`spec` AS spec       -- 关联goods表获取商品规格
        FROM `sre_info` si
        LEFT JOIN `goods` g ON si.`goods` = g.`id`  -- 关联条件：sre_info.goods = goods.id
        WHERE `pid` = ?
        )";
		SQLPARAMS_PUSH(itemParams, "s", std::string, mainDO->getId());

		// 执行明细表查询，映射到 PtrSreInfoDO 列表
		auto itemDOList = sqlSession->executeQuery<PtrSreInfoDO>(itemSql, SreInfoMapper(), itemParams);

		// 将明细表数据转换为 vector 并赋值
		detail->itemDOList.assign(itemDOList.begin(), itemDOList.end());

		resultList.push_back(detail);
	}

	return resultList;
}

// 松额外实现的方法3 ————修改退货单数据
bool SreDAO::update(const PtrSreDO& sreDO) {
	if (!sreDO || sreDO->getId().empty()) return false;

	// 打印各字段长度
	SqlParams params;
	std::string sql = R"(
        UPDATE `sre`
        SET `customer`=?, `time`=?, `data`=?, `logistics`=?, `file`=?, `more`=?, `examine`=?
        WHERE `id`=?
    )";

	// 按字段顺序绑定参数（使用智能指针的getter方法）
	SQLPARAMS_PUSH(params, "s", std::string, sreDO->getCustomer());
	SQLPARAMS_PUSH(params, "dt", std::string, sreDO->getTime());
	SQLPARAMS_PUSH(params, "s", std::string, sreDO->getData());
	SQLPARAMS_PUSH(params, "s", std::string, sreDO->getLogistics());
	SQLPARAMS_PUSH(params, "s", std::string, sreDO->getFile());
	SQLPARAMS_PUSH(params, "s", std::string, sreDO->getMore());
	SQLPARAMS_PUSH(params, "i", int, static_cast<int>(sreDO->getExamine())); // examine是tinyint，转int
	SQLPARAMS_PUSH(params, "s", std::string, sreDO->getId());

	return sqlSession->executeUpdate(sql, params) > 0;

}


bool SreDAO::delById(const std::string& id) {
	try {
		std::string sql = "DELETE FROM sre WHERE `id`=?";
		SqlParams params;
		SQLPARAMS_PUSH(params, "s", std::string, id);
		return sqlSession->executeUpdate(sql, params) > 0;
	}
	catch (std::exception& e) {
		std::cerr << "SreDAO::delById error " << e.what() << std::endl;
		return false;
	}
	return false;
}

bool SreDAO::updateCheckStatus(const std::string& id, int checkStatus) {
	try {
		std::string sql = "UPDATE sre SET `check`=? WHERE `id`=?";
		SqlParams params;
		SQLPARAMS_PUSH(params, "i", int, checkStatus);
		SQLPARAMS_PUSH(params, "s", std::string, id);
		return sqlSession->executeUpdate(sql, params) > 0;
	}
	catch (std::exception& e) {
		std::cerr << "SreDAO::updateCheckStatus error " << e.what() << std::endl;
		return false;
	}
	return false;
}


// 审核DAO
bool SreDAO::approveById(const std::string& id) {
	if (id.empty()) return false;

	SqlParams params;
	std::string sql = "UPDATE `sre` SET `examine` = 1 WHERE `id` = ? AND `examine` = 0";
	SQLPARAMS_PUSH(params, "s", std::string, id);

	return sqlSession->executeUpdate(sql, params) > 0;
}

//反审核DAO
bool SreDAO::unapproveById(const std::string& id) {
	if (id.empty()) return false;

	SqlParams params;
	std::string sql = "UPDATE `sre` SET `examine` = 0 WHERE `id` = ? AND `examine` = 1";
	SQLPARAMS_PUSH(params, "s", std::string, id);

	return sqlSession->executeUpdate(sql, params) > 0;
}

//数据导入DAO
bool SreDAO::importData(const PayloadDTO& payload, const oatpp::Object<SaleReturnOrderImportDTO>& dto, std::string& sre_uuid) {
	UuidFacade uf;
	sre_uuid = uf.genUuid();

	// 构建SQL语句 - 只使用SreReturnOrderImportDTO中实际存在的字段
	std::string insertSreSQL = "INSERT INTO `sre` ( \
        `id`, `source`, `frame`, `customer`, `time`, `number`, \
        `total`, `actual`, `money`, `cost`, `account`, \
        `people`, `logistics`, `file`, `data`, `more`, \
        `examine`, `nucleus`, `cse`, `invoice`, `check`, `user` \
        ) VALUES( '" + sre_uuid + "',";

	// source字段 - 在DTO中不存在，设为NULL
	insertSreSQL += "NULL,";

	// frame字段 - 在DTO中不存在，使用默认值'0'
	insertSreSQL += "'0',";

	// customer字段 - 必填
	insertSreSQL += "'" + *dto->customer + "','";

	// time字段 - 必填
	insertSreSQL += *dto->time + "','";

	// number字段 - 必填
	insertSreSQL += *dto->number + "',";

	// total字段
	insertSreSQL += std::to_string(dto->total) + ",";

	// actual字段
	insertSreSQL += std::to_string(dto->actual) + ",";

	// money字段
	insertSreSQL += std::to_string(dto->money) + ",";

	// cost字段 - 在DTO中不存在，使用默认值0.0000
	insertSreSQL += "0.0000,";

	// account字段 - 在DTO中不存在，设为NULL
	insertSreSQL += "NULL,";

	// people字段
	if (dto->people) {
		insertSreSQL += "'" + *dto->people + "',";
	}
	else {
		insertSreSQL += "NULL,";
	}

	// logistics字段
	if (dto->logistics) {
		insertSreSQL += "'" + *dto->logistics + "',";
	}
	else {
		insertSreSQL += "NULL,";
	}

	// file字段 - 在DTO中不存在，设为NULL
	insertSreSQL += "NULL,";

	// data字段
	if (dto->remark) {
		insertSreSQL += "'" + *dto->remark + "',";
	}
	else {
		insertSreSQL += "NULL,";
	}

	// more字段 - 在DTO中不存在，设为NULL
	insertSreSQL += "NULL,";

	// 状态字段和用户
	insertSreSQL += "0,0,0,0,0,'";
	insertSreSQL += payload.getUsername() + "')";

	// 执行SQL
	if (sqlSession->executeUpdate(insertSreSQL) == 0) {
		return false;
	}

	return true;
}