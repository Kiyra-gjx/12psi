#include "stdafx.h"
#include "SorDAO.h"
#include"id/UuidFacade.h"
//头文件
#include "domain/do/SorInfoDO.h"
#include "dao/SorDAO/SorMapper.h"
#include "dao/SorInfoDAO/SorInfoMapper.h"
//转化数字为排序方式(0：降序1:升序)
#define SORT_ORDER(x) ((x == 1)?"ASC":"DESC")

bool SorDAO::importData(const PayloadDTO& payload,const SorImportDTO::Wrapper& dto,std::string& sor_uuid) {
    //SorDO Do;

    UuidFacade uf;
    //uf.genUuid();
    //stringstream sqlCondition;
    //SqlParams params;
    //string sql = "INSERT INTO `sor` ( \
    //    `id`, `customer`, `time`, `number`, `total`, `actual`,\
    //    `people`, `arrival`, `logistics`, `file`, `data`,\
    //    `examine`, `state`, `user` \
    //    ) VALUES( ?,?,?,?,COALESCE(? , ?),?,\
    //    ?,NULLIF(? , ''),?,?,?\
    //    0,0,?";
    //SQLPARAMS_PUSH(params, "s", std::string, uf.genUuid());
    //SQLPARAMS_PUSH(params, "s", std::string, dto->customer);
    //SQLPARAMS_PUSH(params, "s", std::string, dto->time);
    //SQLPARAMS_PUSH(params, "s", std::string, dto->number);
    //SQLPARAMS_PUSH(params, "d", double, dto->total);
    //SQLPARAMS_PUSH(params, "d", double, dto->actual);
    //SQLPARAMS_PUSH(params, "d", double, dto->actual);
    //SQLPARAMS_PUSH(params, "s", std::string, dto->people);
    //SQLPARAMS_PUSH(params, "s", std::string, dto->arrival);
    //SQLPARAMS_PUSH(params, "s", std::string, dto->logistics);
    //SQLPARAMS_PUSH(params, "s", std::string, dto->file);
    //SQLPARAMS_PUSH(params, "s", std::string, dto->data);
    //SQLPARAMS_PUSH(params, "s", std::string, payload.getUsername());
    sor_uuid = uf.genUuid();

    std::string insertSorSQL = "INSERT INTO `sor` ( \
        `id`, `customer`, `time`, `number`, `total`, `actual`,\
        `people`, `arrival`, `logistics`, `file`, `data`,\
        `examine`, `state`, `user` \
        ) VALUES( '" + sor_uuid + "','" + dto->customer + "','" + dto->time + "','" + dto->number + "'," + \
        (dto->total ? std::to_string(dto->total) : std::to_string(dto->actual)) + "," + \
        std::to_string(dto->actual) + ",'" + dto->people + "'," +\
        (dto->arrival->empty() ? "NOW()" : "'" + dto->arrival + "'") + ",'" + \
        dto->logistics + "','" + dto->file + "','" + dto->data + "',0,0,'" +\
        payload.getUsername() + "')";
    //cout << insertSorSQL << '\n';
    if (sqlSession->executeUpdate(insertSorSQL) == 0) {
        //sqlSession->rollbackTransaction();
        return false;
    }
    //cout << "sor get\n";

    return true;
}


std::string SorDAO::queryConditionBuilder(const SaleOrderListQuery::Wrapper& query, SqlParams& params) {
	stringstream sqlCondition;
	//根据编号内联详情表得到商品编号，根据商品编号内联商品表得到商品名称
	if (query->name) {
		sqlCondition << R"(
		INNER JOIN (SELECT pid,goods FROM sor_info) inf ON sor.id=inf.pid
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
		sqlCondition << " AND number LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->number.getValue(""));
	}
	if (query->customer) {
		sqlCondition << " AND customer=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->customer.getValue(""));
	}
	if (query->people) {
		sqlCondition << " AND people=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->people.getValue(""));
	}
	if (query->begintime) {
		sqlCondition << " AND time >= ?";
		SQLPARAMS_PUSH(params, "dt", std::string, query->begintime.getValue(""));
	}
	if (query->endtime) {
		sqlCondition << " AND time <= ?";
		SQLPARAMS_PUSH(params, "dt", std::string, query->endtime.getValue(""));
	}
	if (query->user) {
		sqlCondition << " AND user=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->user.getValue(""));
	}
	if (query->examine) {
		sqlCondition << " AND examine=?";
		SQLPARAMS_PUSH(params, "i", int32_t, query->examine.getValue(0));
	}
	/*if (query->nucleus) {
		sqlCondition << " AND nucleus=?";
		SQLPARAMS_PUSH(params, "i", int32_t, query->nucleus.getValue(0));
	}*/
	/*if (query->cse) {
		sqlCondition << " AND cse=?";
		SQLPARAMS_PUSH(params, "i", int32_t, query->cse.getValue(0));
	}*/
	/*if (query->invoice) {
		sqlCondition << " AND invoice=?";
		SQLPARAMS_PUSH(params, "i", int32_t, query->invoice.getValue(0));
	}*/
	/*if (query->check) {
		sqlCondition << " AND sor.check=?";
		SQLPARAMS_PUSH(params, "i", int32_t, query->check.getValue(0));
	}*/
	if (query->data) {
		sqlCondition << " AND `data` LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->data.getValue(""));
	}
	return sqlCondition.str();
  
}
std::string SorDAO::queryOrderBuilder(const SaleOrderListQuery::Wrapper& query, SqlParams& params) {
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
	else if (query->arrivalSortOrder.get()) {
		sqlOrder << " arrival " << SORT_ORDER(query->arrivalSortOrder.getValue(false));
	}
	/*else if (query->moneySortOrder.get()) {
		sqlOrder << " sor_money " << SORT_ORDER(query->moneySortOrder.getValue(false));
	}*/
	/*else if (query->costSortOrder.get()) {
		sqlOrder << " cost " << SORT_ORDER(query->costSortOrder.getValue(false));
	}*/
	else {
		sqlOrder.str("");
	}
	return sqlOrder.str();
}

uint64_t SorDAO::count(const SaleOrderListQuery::Wrapper& query) {
	string sql = "SELECT count(*) FROM sor ";
	SqlParams params;
	
	sql += queryConditionBuilder(query, params);

	return sqlSession->executeQueryNumerical(sql, params);
}

//获取原始数据
std::list<PtrSorDO> SorDAO::selectAll(const SaleOrderListQuery::Wrapper& query) {
	SqlParams params;
	//获取基础信息
	std::string sql = R"(
	SELECT 
	sor.id `id`,
	frame frame,
	customer customer,
	time `time`,
	number `number`,
	total total,
	actual actual,
	arrival arrival,
	people people,
	examine examine,
	`state` `state`,
	`user` `user`,
	`data` `data`
	FROM sor
	)";
	
	//构建查询条件
	sql += queryConditionBuilder(query, params);
	//构建排序语句
	sql += queryOrderBuilder(query, params);
	//构建分页条件
	std::stringstream limitClause; limitClause << " LIMIT " << query->pageSize << " OFFSET " << ((query->pageIndex - 1) * query->pageSize);
	sql += limitClause.str();
	return sqlSession->executeQuery<PtrSorDO>(sql, SorSimpleMapper(), params);
}


PtrSorDO SorDAO::selectById(const string& id) {
	string sql = R"(select id,frame,customer,`time`,`number`,`total`,actual,arrival,people,examine,`state`,`user`,`data`
		FROM sor 
		WHERE id = ?)";
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, id);
	cout << "id = " << id << endl;
	return sqlSession->executeQueryOne<PtrSorDO>(sql, SorSimpleMapper(), params);
}

bool SorDAO::deleteById(const std::string& id)
{
    if (id.empty()) {
        std::cerr << "SorDAO: id is empty string" << std::endl;
        return false;
    }
        std::cout << "SorDAO: Executing delete for id: '" << id << "'" << std::endl;

        SqlParams params;
        std::string sql = "DELETE FROM sor WHERE id = ?";

        // 浣跨敤 SQLPARAMS_PUSH 瀹忓畨鍏ㄥ湴娣诲姞鍙傛暟
        SQLPARAMS_PUSH(params, "s", std::string, id);

        // 姝ｇ‘鐨勮皟鐢ㄦ柟寮?
        int affectedRows = sqlSession->executeUpdate(sql, params);

        std::cout << "SorDAO: Affected rows: " << affectedRows << std::endl;
        return affectedRows > 0;
    }


bool SorDAO::approveById(const std::string& id)
{
    if (id.empty()) {
        return false;
    }

    try {
        SqlParams params;
        // 浣跨敤 examine 瀛楁琛ㄧず瀹℃牳鐘舵�侊紝0=鏈鏍革紝1=宸插鏍?
        std::string sql = "UPDATE sor SET examine = 1 WHERE id = ?";

        SQLPARAMS_PUSH(params, "s", std::string, id);

        int affectedRows = sqlSession->executeUpdate(sql, params);
        return affectedRows > 0;
    }
    catch (const std::exception& e) {
        std::cerr << "SorDAO: Approve error: " << e.what() << std::endl;
        return false;
    }
}


bool SorDAO::unapproveById(const std::string& id)
{
    if (id.empty()) {
        return false;
    }

    try {
        SqlParams params;
        // 鍙嶅鏍革細灏?examine 瀛楁鏀瑰洖 0锛堟湭瀹℃牳锛?
        std::string sql = "UPDATE sor SET examine = 0 WHERE id = ?";

        SQLPARAMS_PUSH(params, "s", std::string, id);

        int affectedRows = sqlSession->executeUpdate(sql, params);
        return affectedRows > 0;
    }
    catch (const std::exception& e) {
        std::cerr << "SorDAO: Unapprove error: " << e.what() << std::endl;
        return false;
    }
}

bool SorDAO::isOrderApproved(const std::string& id)
{
    if (id.empty()) {
        return false;
    }

    try {
        SqlParams params;
        // 妫�鏌ヨ鍗曟槸鍚﹀瓨鍦ㄤ笖宸插鏍?(examine = 1)
        std::string sql = "SELECT COUNT(*) FROM sor WHERE id = ? AND examine = 1";

        SQLPARAMS_PUSH(params, "s", std::string, id);

        int count = sqlSession->executeQueryNumerical(sql, params);
        return count > 0;
    }
    catch (...) {
        return false;
    }
}

bool SorDAO::SorUpdate(const PtrSorDO& sorDO)
{
	if(!sorDO || sorDO->getId().empty()) {
		return false;
	}

	SqlParams params;
	std::string sql = R"(
	UPDATE sor
	SET
		cusomer = ?,
		time = ?,
		data = ?,
		logistics = ?,
		people = ?,
		actual = ?,
		arrival = ?,
		file = ?
	WHERE id = ?
	)";
	SQLPARAMS_PUSH(params, "s", std::string, sorDO->getCustomer());
	SQLPARAMS_PUSH(params, "s", std::string, sorDO->getTime());
	SQLPARAMS_PUSH(params, "s", std::string, sorDO->getData());
	SQLPARAMS_PUSH(params, "s", std::string, sorDO->getLogistics());
	SQLPARAMS_PUSH(params, "s", std::string, sorDO->getPeople());
	SQLPARAMS_PUSH(params, "s", double, sorDO->getActual());
	SQLPARAMS_PUSH(params, "s", std::string, sorDO->getArrival());
	SQLPARAMS_PUSH(params, "s", std::string, sorDO->getFile());
	SQLPARAMS_PUSH(params, "s", std::string, sorDO->getId());

	return sqlSession->executeUpdate(sql, params) > 0;
}

std::vector<PtrSorDO> SorDAO::querySimpleReport(const std::string& startDate, const std::string& endDate)
{
	

	SqlParams params;
	std::string sql = R"(
	SELECT
		frame,
		customer,
		time,
		number,
		total,
		actual,
		arrival,
		people,
		examine,
		state,
		user,
		data
	FROM sor 
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

	auto listResult = sqlSession->executeQuery<PtrSorDO>(sql, SorSimpleReportMapper(), params);

	if(listResult.empty()) {
		return {};
	}
	return std::vector<PtrSorDO>(listResult.begin(), listResult.end());
}

std::vector<PtrSorDetailDO> SorDAO::queryDetailReport(const std::string& orderNoLike)
{
	std::vector<PtrSorDetailDO> detailList;

	SqlParams mainParams;
	std::string mainSql = R"(
	SELECT
		id,
		customer,
		time,
		number,
		total,
		actual,
		people,
		arrival,
		logistics,
		data
	FROM sor
	WHERE 1=1
	)";
	if (!orderNoLike.empty()) {
		mainSql += " AND `id` LIKE CONCAT('%', ?, '%')";
		SQLPARAMS_PUSH(mainParams, "s", std::string, orderNoLike);
	}

	auto mainListResult = sqlSession->executeQuery<PtrSorDO>(mainSql, SorDetailReportMapper(), mainParams);
	
	for(const auto& mainDO : mainListResult) {
		auto detailDO = std::make_shared<SorDetailDO>();
		detailDO->sor = mainDO;
		SqlParams infoParams;
		std::string infoSql = R"(
		SELECT
			g.name AS goodsName,
			g.spec AS sepc,
			si.attr,
			si.unit,
			si.warehouse,
			si.price,
			si.nums,
			si.handle,
			si.discount,	
			si.dsc,
			si.total,
			si.data
		FROM sor_info si
		LEFT JOIN goods g ON si.goods = g.id
		WHERE si.pid = ?
		)";
		SQLPARAMS_PUSH(infoParams, "s", std::string, mainDO->getId());
		auto infoListResult = sqlSession->executeQuery<PtrSorInfoDO>(infoSql, SorInfoDAOMapper(), infoParams);
		detailDO->sorInfoList = std::vector<PtrSorInfoDO>(infoListResult.begin(), infoListResult.end());
		detailList.push_back(detailDO);
	}

	return detailList;
}