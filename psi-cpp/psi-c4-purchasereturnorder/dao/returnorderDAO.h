#ifndef _RETURNORDERDAO_H_
#define _RETURNORDERDAO_H_
#include "BaseDAO.h"
#include "../domain/do/ReturnorderInfoDO.h"

/**
 * 修改采购退货单操作实现
 */
class BreInfoDAO : public BaseDAO
{
public:
	bool updateBreInfo(const BreInfoDO& dto);
};
#endif