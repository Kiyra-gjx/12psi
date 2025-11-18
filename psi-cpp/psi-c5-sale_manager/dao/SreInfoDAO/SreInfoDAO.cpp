#include "stdafx.h"
#include "SreInfoDAO.h"
#include "SreInfoMapper.h"

std::string SreInfoDAO::queryConditionBuilder(const SreDetailQuery::Wrapper& query, SqlParams& params) {
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->id) {
		sqlCondition << " AND pid=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->id.getValue(""));
	}
	return sqlCondition.str();
}

uint64_t SreInfoDAO::count(const SreDetailQuery::Wrapper& query) {
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM sre_info";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

list<SreInfoViewDO> SreInfoDAO::selectById(const SreDetailQuery::Wrapper& query) {
	//得到多条数据DO
	//查询子表
	//内联商品表获取商品名称和商品编号
	//最后再用id筛选一下
	string sql = R"(
	SELECT 
		g.name goods_name,
		g.number goods_number,
		g.spec goods_spec,
		inf.attr `attr`,
		inf.unit `unit`,
		inf.warehouse warehouse,
		inf.batch batch,
		inf.mfd mfd,
		inf.price price,
		inf.nums `nums`,
		inf.discount discount,
		inf.dsc dsc,
		inf.nums * inf.price total,
		inf.data `data`
	FROM sre_info inf
	INNER JOIN (SELECT id,name,number,spec FROM goods) g
	ON g.id = inf.goods
	WHERE inf.pid=?
	)";
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, query->id.getValue(""));
	return sqlSession->executeQuery<SreInfoViewDO>(sql, SreInfoMapper(), params);
}

bool SreInfoDAO::insert(const shared_ptr<SreInfoDO>& sreInfDO) {
	try {
		//共19个字段
		string sql = R"(
		INSERT INTO sre_info
		(`id`,`pid`,`source`,`goods`,`attr`,`unit`,`warehouse`,`batch`,`mfd`,`serial`,`data`,`price`,`nums`,`discount`,`dsc`,`total`,`tax`,`tat`,`tpt`)
		VALUES( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
		)";
		//注意:加入变量的顺序要和	INSERT顺序一致
		SqlParams params;
		SQLPARAMS_PUSH(params, "s", std::string, sreInfDO->getId());
		SQLPARAMS_PUSH(params, "s", std::string, sreInfDO->getPid());
		SQLPARAMS_PUSH(params, "s", std::string, sreInfDO->getSource());
		SQLPARAMS_PUSH(params, "s", std::string, sreInfDO->getGoods());	//商品id
		SQLPARAMS_PUSH(params, "s", std::string, sreInfDO->getAttr());
		SQLPARAMS_PUSH(params, "s", std::string, sreInfDO->getUnit());
		SQLPARAMS_PUSH(params, "s", std::string, sreInfDO->getWarehouse());
		SQLPARAMS_PUSH(params, "s", std::string, sreInfDO->getBatch());
		SQLPARAMS_PUSH(params, "dt", std::string, sreInfDO->getMfd());		//生产日期
		SQLPARAMS_PUSH(params, "s", std::string, sreInfDO->getSerial());		//序列号
		SQLPARAMS_PUSH(params, "s", std::string, sreInfDO->getData());

		SQLPARAMS_PUSH(params, "d", double, sreInfDO->getPrice());
		SQLPARAMS_PUSH(params, "d", double, sreInfDO->getNums());
		SQLPARAMS_PUSH(params, "d", double, sreInfDO->getDiscount());
		SQLPARAMS_PUSH(params, "d", double, sreInfDO->getDsc());
		SQLPARAMS_PUSH(params, "d", double, sreInfDO->getTotal());
		SQLPARAMS_PUSH(params, "d", double, sreInfDO->getTax());
		SQLPARAMS_PUSH(params, "d", double, sreInfDO->getTat());
		SQLPARAMS_PUSH(params, "d", double, sreInfDO->getTpt());
		return sqlSession->executeUpdate(sql,params) > 0;
	}
	catch (std::exception& e) {
		std::cerr << "SreInfoDAO::insert error : " << e.what() << endl;
		return false;
	}
}

bool SreInfoDAO::removeByPid(const string& pid) {
	try {
		string sql = "DELETE FROM sre_info WHERE `pid`=?";
		SqlParams params;
		SQLPARAMS_PUSH(params, "s", std::string, pid);
		return sqlSession->executeUpdate(sql, params) >= 0;
	}
	catch (std::exception& e) {
		std::cerr << "SreInfoDAO::removeByPid error : " << e.what() << endl;
		return false;
	}
}
