#pragma once


#ifndef _IMPORT_DAO_
#define _IMPORT_DAO_
#include "BaseDAO.h"
#include"../domain/do/getreturnlistDO.h"
#include"../domain/do/BreInfoDO.h"
#include"../domain/do/RoomDO.h"
#include"domain/do/AccountInfoDO.h"
#include"domain/do/GoodsDO.h"
#include"domain/do/WarehouseDO.h"
#include"domain/do/SupplierDO.h"
#include"domain/do/AccountDO.h"

/**
 * 根据excel报表导入数据
 */
class ImportDAO : public BaseDAO
{
private:

public:

	// 通过商品名和拼音查找商品信息
	PtrGoodsDO selectByName(std::string goodName, std::string py);

	// 通过仓库名找仓库ID
	PtrWarehouseDO selectByWarehouse(std::string warehouse);

	// 通过供应商名字和拼音查看供应商信息
	PtrSupplierDO selectSupplier(std::string name, std::string py);

	// 通过用户名查找用户ID
	PtrAccountDO selectUser(std::string name);
};

#endif // !_IMPORT_DAO_