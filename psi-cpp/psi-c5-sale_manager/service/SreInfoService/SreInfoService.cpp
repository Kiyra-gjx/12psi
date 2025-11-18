#include "stdafx.h"
#include "SreInfoService.h"
#include "dao/SreInfoDAO/SreInfoDAO.h"
#include "domain/do/SreInfoDO.h"

oatpp::List<SreSingleInfoDTO::Wrapper> SreInfoService::getSreInfosByid(const SreDetailQuery::Wrapper& query) {
	auto infos = oatpp::List<SreSingleInfoDTO::Wrapper>::createShared();
	SreInfoDAO dao;
	list<SreInfoViewDO> dolist = dao.selectById(query);
	for (const auto& one : dolist) {
		auto dto = SreSingleInfoDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, one, goodsName, GoodsName, goodsNumber, GoodsNumber, goodsSpec, GoodsSpec, attr, Attr, unit, Unit);
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, one,warehouse,Warehouse,price,Price,nums,Nums,discount,Discount,dsc,Dsc,total,Total,data,Data);
		infos->push_back(dto);
	}
	return infos;
}