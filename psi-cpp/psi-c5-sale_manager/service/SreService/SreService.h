#pragma once
/*
 * 销售退货单主表 Service（仅声明，不含实现）
 */

#include "domain/GlobalInclude.h"
#include "oatpp/core/Types.hpp"

 // DTO
#include "domain/dto/SaleReturnOrderDTO.h"                               
// DAO
#include "dao/SreDAO/SreDAO.h"        
//DO
#include "domain/do/SreDO.h"
//Query
#include "domain/query/SaleReturnOrderQuery.h"
// 松 额外引入的头文件
#include "domain/vo/BaseJsonVO.h"

//jinyang
#include<domain/vo/SaleReturnOrderVO.h>

class SreService {
public:
	//月庄负责的 接口
	//1.分页查询所有数据
	SrePageDTO::Wrapper listAll(const SreListQuery::Wrapper& query);
	//2.查询数据详情
	SreDetailDTO::Wrapper getDetail(const SreDetailQuery::Wrapper& query);
	////3.新增销售退货单
	std::string addList(const SreAddDTO::Wrapper& dto);
	//松 额外加的函数
	// 接口1：修改销售退货单
	StringJsonVO::Wrapper update(const SreUpdateDTO::Wrapper& dto);

	// 接口2：查询简单报表数据（DO→DTO转换）
	std::vector<SreExportSimpleDTO::Wrapper> querySimpleList(const SreExportSimpleQuery::Wrapper& query);

	// 接口3：查询详细报表数据（主表+明细表 DO→DTO转换）
	std::vector<SreExportDetailDTO::Wrapper> queryDetailList(const SreExportDetailQuery::Wrapper& query);
	//4.删除销售退货单
	bool removeById(const std::string& id);
	//5.核对/反核对销售退货单
	bool checkById(const std::string& id, bool checkStatus);

	//批量导入退货单数据
	ImportResultDTO::Wrapper importData(const SaleReturnBatchImportDTO::Wrapper& dto);

	// 批量审核  
	BatchOperationVO::Wrapper batchApprove(const SaleReturnAuditDTO::Wrapper& dto);

	// 批量反审核  
	BatchOperationVO::Wrapper batchUnapprove(const SaleReturnAuditDTO::Wrapper& dto);
};