#pragma once
/*
 * 销售退货单明细 Service（仅声明，不含实现）
 * 依赖：DAO/DO/DTO，供主表或控制器调用
 */

#include "domain/GlobalInclude.h"
#include "oatpp/core/Types.hpp"

 // DTO
#include "domain/dto/SaleReturnOrderDTO.h"                     

// DO
#include "domain/do/SreInfoDO.h"                       

// DAO
#include "dao/SreInfoDAO/SreInfoDAO.h"                        
#include "domain/query/SaleReturnOrderQuery.h"

class SreInfoService {
public:
	//把符合条件的DO转为DTO
	oatpp::List<SreSingleInfoDTO::Wrapper> getSreInfosByid(const SreDetailQuery::Wrapper& query);

};
