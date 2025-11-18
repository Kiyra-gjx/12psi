#pragma once
#ifndef _EXREPORTSIM_SERVICE_
#define _EXREPORTSIM_SERVICE_
#include "../domain/vo/ExReportDeJsonVO.h"
#include "../domain/query/ExReportDeQUERY.h"
#include "../domain/dto/ExReportDeDTO.h"

class ExReportDeService
{
public:
	// 查询全部的结果
	ExReportDeDTO::Wrapper selectAll(const ExReportDeQUERY::Wrapper& query);
	// 查询一条数据
	// ExReportDeDTO::Wrapper selectOne(const ExReportDeQUERY::Wrapper& query);
	//// 通过ID查询单个数据
	//ExReportSimDTO::Wrapper getById(std::string id);
	//// 保存数据
	//std::string saveData(const ExReportSimAddDTO::Wrapper& dto);
	//// 修改数据
	//bool updateData(const ExReportSimDTO::Wrapper& dto);
	//// 通过ID删除数据
	//bool removeData(const oatpp::List<oatpp::String>& ids);
};






#endif // !_SAMPLE_SERVICE_