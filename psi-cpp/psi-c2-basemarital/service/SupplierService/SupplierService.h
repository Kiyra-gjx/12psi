#pragma once
#ifndef _SUPLIER_SERVICE_H
#define _SUPLIER_SERVICE_H
#include "../../domain/dto/SupplierDTO/SupplierDTO.h"
#include "../../domain/query/SupplierQuery/SupplierQuery.h"
#include "../../domain/vo/SupplierVO/SupplierVO.h"
#include "../../domain/do/SupplierDO.h"

class SupplierService
{
public:
	//分页查询供应商列表
	SupplierListPageDTO::Wrapper listSuppliers(const SupplierQuery::Wrapper& query);
	//根据名称查询供应商详情
	SupplierDetailDTO::Wrapper getSupplierDetail(const oatpp::String& name);
	//通过ID删除数据
	bool removeData(const oatpp::List<oatpp::String>& ids);
	//分页查询所有数据
	SupplierPageDTO::Wrapper listAll(const SupplierQuery::Wrapper& query);
	bool Import(list<SupplierDTO>& dtos);
	//添加供应商
	std::string saveSupplier(const SupplierAddDTO::Wrapper& dto);
	//修改供应商
	bool updateSupplier(const SupplierUpdateDTO::Wrapper& dto);
};

#endif
