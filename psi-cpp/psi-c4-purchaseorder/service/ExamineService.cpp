#include "stdafx.h"
#include"ExamineService.h"
#include"../dao/ExamineDAO.h"
#include"../domain/do/BuyDO.h"

pair<bool, string> ExamineService::examineOrder(const ExamineDTO::Wrapper& dto)
{
	// 组装DO数据
	BuyDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, Id, id, Source, source);

	// 查询单据的审核状态
	ExamineDAO dao;
	auto res = dao.selectById(dto->id);

	// 没有找到目标
	if (!res)
		return { 0,"can't find the order" };


	int exam = res->getExamine();

	// 根据审核状态执行不同的处理逻辑
	if (exam == 1)
	{// 审核 -> 未审核


		// 检查数据是否合法


		// 修改数据
		data.setExamine(0);
		bool is_ok = dao.update(data) == 1;

		return is_ok ? make_pair(1, "") : make_pair(0, "update error");

	}
	else if (exam == 0)
	{// 未审核 -> 审核

		// 检查数据是否合法


		// 修改数据
		data.setExamine(1);
		bool is_ok = dao.update(data) == 1;

		return is_ok ? make_pair(1, "") : make_pair(0, "update error");
	}



	return { 0,"unknown error" };
}