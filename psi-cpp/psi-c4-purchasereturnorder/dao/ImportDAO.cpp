#include"ImportDAO.h"
#include"ReviewOrderMapper.h"
#include "stdafx.h"


PtrGoodsDO ImportDAO::selectByName(std::string goodName, std::string py)
{
	string sql = "select id,name,py,unit from goods where (name,py) = (?,?)";

	return sqlSession->executeQueryOne<PtrGoodsDO>(sql, PtrImportGoodsMapper(), "%s%s", goodName, py);
}

PtrWarehouseDO ImportDAO::selectByWarehouse(std::string warehouse)
{
	string sql = "select id from warehouse where name = ?";

	return sqlSession->executeQueryOne<PtrWarehouseDO>(sql, PtrImportWarehouseMapper(), "%s", warehouse);
}

PtrSupplierDO ImportDAO::selectSupplier(std::string name, std::string py)
{
	string sql = "select id from supplier where name =? AND py =?";

	return sqlSession->executeQueryOne<PtrSupplierDO>(sql, PtrImportSupplierMapper(), "%s%s", name, py);
}

PtrAccountDO ImportDAO::selectUser(std::string name)
{
	string sql = "select id from account where name =?";

	return sqlSession->executeQueryOne<PtrAccountDO>(sql, PtrImportAccountMapper(), "%s", name);
}
