#ifndef _RETURNCHECKDAO_H_
#define _RETURNCHECKDAO_H_
#include "BaseDAO.h"
#include "../domain/do/getreturnlistDO.h"

/**
 * 核对/反核对采购退货单操作实现
 */
class BrecheckDAO : public BaseDAO
{
public:
	bool updateBrecheck(const BreDO& dto);
};
#endif