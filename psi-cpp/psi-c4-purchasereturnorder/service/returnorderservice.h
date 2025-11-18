#ifndef _RETURNORDERSERVICE_H_
#define _RETURNORDERSERVICE_H_
#include "../domain/vo/ReturnOrderVO.h"
#include "../domain/dto/ReturnOrderCheckDTO.h"

/**
 * 核对/反核对采购退货单服务实现
 */
class returncheckservice
{
public:
	// 修改数据
	bool updateData(const returnordercheckDTO::Wrapper& dto);
};

#endif // !_RETURNORDERSERVICE_H_

