#include "stdafx.h"
#include "./PotableService.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"
#include"../dao/PotableDAO.h"
#include"../domain/dto/PotableDTO.h"
#include"../domain/do/PotaleDO.h"

PotablePageDTO::Wrapper PotableService::table_odds(const PotableQuery::Wrapper& query)
{
	//构建返回对象
	auto pages=PotablePageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;
	// 查询数据总条数
	PotableDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<PotableDO>data_list = dao.selectWithPage(query);
	//将DO转换成DTO
	for(auto &sub:data_list)
	{
		auto dto = PotableDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, frame, Frame, number, Number, 
		supplier, Supplier, user,User,time,Time, total,Total, actual, Actual,
		money,Money, cost,Cost, people, People, examine, Examine, nucleus, 
		Nucleus, cse, Cse, invoice, Invoice, check, Check, data, Data);
		pages->addData(dto);
	}
	return pages;
}