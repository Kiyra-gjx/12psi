#include "stdafx.h"
#include "PurchaseOrderJsDAO.h"
#include "id/UuidFacade.h" 
#include <sstream>
#include "SqlSession.h" 

// 新增采购单（buy主表）
std::string PurchaseOrderDAO::addPurchaseOrder(const BuyJsDO& data) {
	string sql = "INSERT INTO `buy` (`id`, `frame`, `supplier`, `time`, `number`, `total`, `actual`, `money`, `cost`, `account`, `people`, `logistics`, `file`, `more`, `data`, `examine`, `nucleus`, `cse`, `invoice`, `check`, `user`) "
		"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"; 

	UuidFacade uf;
	auto id = uf.genUuid();
	SqlParams params;

	SQLPARAMS_PUSH(params, "s", std::string, id);
	SQLPARAMS_PUSH(params, "s", std::string, data.getFrame()); 
	SQLPARAMS_PUSH(params, "s", std::string, data.getSupplier()); 
	SQLPARAMS_PUSH(params, "s", std::string, data.getTime()); 
	SQLPARAMS_PUSH(params, "s", std::string, data.getNumber());
	SQLPARAMS_PUSH(params, "d", double, data.getTotal());
	SQLPARAMS_PUSH(params, "d", double, data.getActual());
	SQLPARAMS_PUSH(params, "d", double, data.getMoney());
	SQLPARAMS_PUSH(params, "d", double, data.getCost());
	SQLPARAMS_PUSH(params, "s", std::string, data.getAccount()); 
	SQLPARAMS_PUSH(params, "s", std::string, data.getPeople()); 
	SQLPARAMS_PUSH(params, "s", std::string, data.getLogistics());
	SQLPARAMS_PUSH(params, "s", std::string, data.getFile()); 
	SQLPARAMS_PUSH(params, "s", std::string, data.getMore()); 
	SQLPARAMS_PUSH(params, "s", std::string, data.getData());
	SQLPARAMS_PUSH(params, "i", int, data.getExamine()); 
	SQLPARAMS_PUSH(params, "i", int, data.getNucleus());
	SQLPARAMS_PUSH(params, "i", int, data.getCse());
	SQLPARAMS_PUSH(params, "i", int, data.getInvoice());
	SQLPARAMS_PUSH(params, "i", int, data.getCheck()); 
	SQLPARAMS_PUSH(params, "s", std::string, data.getUser()); 

	auto result = sqlSession->executeUpdate(sql, params);
	if (result <= 0) {
		return "failed";
	}
	return id; // 成功
}


// 新增采购单（buy_info副表）
bool PurchaseOrderDAO::addInfo(const BuyInfoDO& data) {

	string sql = "INSERT INTO `buy_info` (`id`, `pid`, `source`, `goods`, `attr`, `unit`, `warehouse`, `price`, `nums`, `total`, `tpt`) "
		"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"; 

	UuidFacade uf;
	auto id = uf.genUuid();
	SqlParams params;

	SQLPARAMS_PUSH(params, "s", std::string, id);
	SQLPARAMS_PUSH(params, "s", std::string, data.getPid());
	SQLPARAMS_PUSH(params, "s", std::string, data.getSource());
	SQLPARAMS_PUSH(params, "s", std::string, data.getGoods());
	SQLPARAMS_PUSH(params, "s", std::string, data.getAttr());
	SQLPARAMS_PUSH(params, "s", std::string, data.getUnit());
	SQLPARAMS_PUSH(params, "s", std::string, data.getWarehouse());
	SQLPARAMS_PUSH(params, "d", double, data.getPrice());
	SQLPARAMS_PUSH(params, "d", double, data.getNums());
	SQLPARAMS_PUSH(params, "d", double, data.getTotal());
	SQLPARAMS_PUSH(params, "d", double, data.getTpt());

	auto result = sqlSession->executeUpdate(sql, params);
	return result > 0;
}

//删除采购单
// 查找要删除的采购单id及其审核状态
uint64_t PurchaseOrderDAO::countByIdAndStatus(string id, int status)
{
	string sql = "SELECT COUNT(*) FROM `buy` WHERE `id` = ? AND `examine` = ?";
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, id);
	SQLPARAMS_PUSH(params, "i", int, status);
	return sqlSession->executeQueryNumerical(sql, params);
}

// 通过pid删除buy_info副表记录
int PurchaseOrderDAO::deleteInfoByPid(string pid)
{
	string sql = "DELETE FROM `buy_info` WHERE `pid` = ?";
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, pid);
	return sqlSession->executeUpdate(sql, params);
}

// 通过id删除buy主表记录
int PurchaseOrderDAO::deleteById(string id)
{
	string sql = "DELETE FROM `buy` WHERE `id`=?";
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, id);
	return sqlSession->executeUpdate(sql, params);
}