#pragma once
#ifndef _EXAMINE_DAO_H
#define _EXAMINE_DAO_H

#include "BaseDAO.h"
#include "../domain/do/BuyDO.h"

/**
 * 采购单审核/反审核数据库访问对象
 */
class ExamineDAO : public BaseDAO
{
public:
	// 通过ID查询采购单的数据
	PtrBuyDO selectById(std::string id);
};


#endif // !_EXAMINE_DAO_H
