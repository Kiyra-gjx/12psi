#include "stdafx.h"
#include "WarehouseService.h"
#include "dao/WarehouseDAO/WarehouseDAO.h"
#include "id/UuidFacade.h"
#include "id/SnowFlake.h"

WareListPageDTO::Wrapper WarehouseService::WarehouselistAll(const WarehouseQuery::Wrapper& query)
{

	// 构建返回对象
	auto pages = WareListPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	WarehouseDAO dao;
	uint64_t count = dao.countW(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<WarehouseDO> result = dao.selectWarehouseList(query);
	// 将DO转换成DTO
	for (auto& res : result) {
		auto dto = WareListDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, res, id,Id,name, Name, number, Number, frame, Frame, data, Data);
		pages->addData(dto);
	}
	return pages;
}

oatpp::List<WareNameListDTO::Wrapper> WarehouseService::WareNameList()
{
	//构建返回对象
	auto ll = oatpp::List<WareNameListDTO::Wrapper>::createShared();
	WarehouseDAO dao;
	list<WarehouseDO> result = dao.selectWarehouseNameList();
	for (auto& res : result) {
		auto dto = WareNameListDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, res, id, Id, name, Name,number,Number);
		ll->push_back(dto);
	}
	return ll;
}

// 根据Id查询指定仓库详情信息
WarehouseDetailDTO::Wrapper WarehouseService::getWarehouseDetailById(const string& id)
{
	// 定义查询数据对象
	WarehouseDAO wareDao;
	// 利用wareDao查询，返回的结果do用res接收
	auto res = wareDao.selectWareDetailById(id);
	
	//结果判空
	if (!res)
	{
		return nullptr;
	}

	//将结果do转化成dto
	auto wareDto = WarehouseDetailDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(wareDto, res,
		id, Id, name, Name, number, Number, frame, Frame, contacts, Contacts, tel, Tel, add, Add, data, Data);

	//返回转化好的dto
	return wareDto;
}

// 新增仓库
string WarehouseService::addWarehouse(const WarehouseAddDTO::Wrapper& dto) 
{
	// 将dto转化成do数据，以便dao利用do进行数据库操作
	WarehouseDO wareDo;
	ZO_STAR_DOMAIN_DTO_TO_DO(wareDo, dto,
		Name, name, Number, number, Frame, frame, Contacts, contacts, Tel, tel, Add, add, Data, data);

	// 生成唯一标识id
	UuidFacade uf;
	wareDo.setId(uf.genUuid());

	//定义dao
	WarehouseDAO wareDao;
	//执行插入操作
	bool success = wareDao.insert(wareDo);

	//把id返回
	if (success)
	{
		return wareDo.getId();
	}
	else 
	{
		return "";
	}
}


bool WarehouseService::updateData(const WarehouseDetailDTO::Wrapper& dto)
{
	//雪花算法
	SnowFlake snowFlake(1, 1);
	// 组装DO数据
	WarehouseDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, Id, id, Name, name, Number, number, Frame, frame, Contacts, contacts, Tel, tel, Add, add, Data, data);
	// 执行数据修改
	WarehouseDAO dao;
	return dao.update(data) == 1;
}

bool WarehouseService::removeData(const oatpp::List<oatpp::String>& ids)
{
	WarehouseDAO dao;
	std::list<std::string> datas;
	for (auto one : *ids.get())
		datas.emplace_back(one.getValue({}));
	int rows = dao.deleteByIds<WarehouseDO>(datas);
	if (rows == ids->size())
		return true;
	return false;
}
