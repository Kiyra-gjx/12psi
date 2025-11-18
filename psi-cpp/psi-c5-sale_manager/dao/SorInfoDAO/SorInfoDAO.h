#pragma once

#ifndef _DETAILSALEORDER_DAO_
#define _DETAILSALEORDER_DAO_
#include "BaseDAO.h"
#include "../../domain/do/SorInfoDO.h"
#include"../../domain/dto/SaleOrderListDTO.h"
//#include "../../domain/query/SorInfoQuery.h"


/*
	销售订单详情数据表操作实现
*/
class SorInfoDAO : public BaseDAO
{
private:
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    SampleDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
	// Parameter:   const queryConditionBuilder::Wrapper& query 查询数据对象
	// Parameter:   SqlParams& params 存放查询数据的参数对象
	// Description: 查询条件构建器，根据queryConditionBuilder对象动态构建查询条件相关参数
	//************************************
	//inline std::string queryConditionBuilder(const SorInfoQuery::Wrapper& query, SqlParams& params);

public:
	// 像数据表中插入信息
	bool insertSorInfo(const SorInfoDO& soiDO);
	// 根据ID查询记录
	// 获取数据列表
	//std::list<PtrSor_infoDO> selectAll(const SorInfoQuery::Wrapper& query);
	// 查询总记录数
	int64_t count();
	// 根据销售订单ID删除对应记录
	int deleteSorInfoByID(const string& id);
	// 更新值
	int updateSorInfo(const SorInfoDO& soiDO);
	//导入数据
	bool importData(const PayloadDTO& payload, const SorImportDTO::Wrapper& dto, const std::string& sor_uuid);

	std::list<PtrSorInfoDO> selectByOrderId(string id);

};


#endif // !_DETAILSALEORDER_DAO_
