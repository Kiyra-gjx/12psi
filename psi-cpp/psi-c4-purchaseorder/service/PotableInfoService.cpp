#include"stdafx.h"
#include"./PotableInfoService.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"
#include"../dao/PotableInfoDAO.h"
#include"../domain/dto/PotableInfoDTO.h"
#include"../domain/do/PotableInfoDO.h"

PotableInfoDTO::Wrapper PotableInfoService::tableInfo(const PotableInfoQuery::Wrapper& query)
{
		auto pages= PotableInfoDTO::createShared();//定义返回dto
		PotableInfoDAO dao;//定义DAO用于操作
		auto res = dao.selectPotableInfoPID(query);//res获取操作结果(通常是DO形式)
		//将DO转换成DTO
		for (auto& sud:res) {
			auto dto = Potable_InfoDTO::createShared();
			ZO_STAR_DOMAIN_DO_TO_DTO(dto, sud, name, Name, attr, Attr, unit, Unit, warehouse, Warehouse,
				data, Data, price, Price, nums, Nums, dsc, Dsc, total, Total);
			pages->addData(dto);
		}

	return pages;
	
}
