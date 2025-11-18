#include "stdafx.h"
#include "ExReportDeService.h"
#include "../dao/ExReportDeDAO.h"
#include "id/UuidFacade.h"
// #include "SimpleDateTimeFormat.h"


// ExReportDeDTO::Wrapper ExReportDeService::selectOne(const ExReportDeQUERY::Wrapper& query) {
	// // 查询单条数据
	// ExReportDeDAO dao;
 //
	// auto result =  dao.selectOne(query);
	// // 如果没有数据，返回空指针
	// if (!result)
	// {
	// 	return nullptr;
	// }
 //
 //    // 转换数据到DTO
 //    auto dto = ExReportDeDTO::createShared();
 //    PotableInfoDO& sub = *result; // 解引用shared_ptr
 //
 //    // 主键字段 - 确保ExReportDeDTO有这些成员
 //    ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id);
 //    // 如果不需要pid字段，可以注释掉下面这行
 //    // ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, pid, Pid);
 //
 //    // // 业务字段 - 根据实际存在的字段进行映射
 //    // ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, goods, Goods);
 //    // // 如果PurchaseOrderDetailsDO没有spec字段，可以注释掉下面这行
 //
 //
	// ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
	// 	pid, Pid,
	// 	source, Source,
	// 	goods, Goods,
	// 	attr, Attr,
	// 	unit, Unit,
	// 	warehouse, Warehouse,
	// 	batch, Batch,
	// 	mfd, Mfd,
	// 	price, Price,
	// 	nums, Nums,
	// 	serial, Serial,
	// 	discount, Discount,
	// 	dsc, Dsc,
	// 	total, Total,
	// 	tax, Tax,
	// 	tat, Tat,
	// 	tpt, Tpt,
	// 	data, Data,
	// 	retreat, Retreat
	// );

    // ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id);
    // ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, goods, Goods);
    // ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, attr, Attr);
    // ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, unit, Unit);
    // ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, warehouse, Warehouse);
    // ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, price, Price);
    // ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, nums, Nums);
    // ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, total, Total);
    // ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, tax, Tax);
    // ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, tat, Tat);
    // ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, tpt, Tpt);
    // ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, data, Data);

    // return dto;
// 	return {};
// }

ExReportDeDTO::Wrapper ExReportDeService::selectAll(const ExReportDeQUERY::Wrapper &query) {
	auto pages = ExReportDePageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	return {};
}
