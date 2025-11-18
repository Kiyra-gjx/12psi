#pragma once
#ifndef _EXAMINE_SERVICE_H
#define _EXAMINE_SERVICE_H

#include "domain/dto/ExamineDTO.h"

/**
 * 采购单审核/反审核业务逻辑类
 */
class ExamineService {

public:
	// 审核和反审核订单
	pair<bool, string> examineOrder(const ExamineDTO::Wrapper& dto);
};

#endif // !_EXAMINE_SERVICE_H
