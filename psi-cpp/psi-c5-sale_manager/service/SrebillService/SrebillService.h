#pragma once
/*
 * 销售退货单核销/结算 Service（仅声明，不含实现）
 * 依赖：DAO/DO/DTO，供主表或控制器调用
 */

#include "domain/GlobalInclude.h"
#include "oatpp/core/Types.hpp"

 // DTO
#include "domain/dto/SaleReturnOrderDTO.h"                       

// DO
#include "domain/do/SrebillDO.h"                       

// DAO
#include "dao/SrebillDAO/SrebillDAO.h"                        

class SrebillService {
public:

};