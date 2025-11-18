#include "stdafx.h"
#include "SorService.h"
#include"dao/SorDAO/SorDAO.h"
#include"dao/SorInfoDAO/SorInfoDAO.h"
#include "service/SellInfoService/SellInfoService.h"	//销售单详情查询
#include "service/BorInfoService/BorInfoService.h"		//采购订单详情查询
#include "domain/do/SellInfoDO.h"
#include "domain/do/BorInfoDO.h"
#include "../../Macros.h"
#include "NacosClient.h"
#include "id/UuidFacade.h"
#include "TransactionManager.h"



typedef oatpp::data::mapping::type::String String;

bool SorService::importData(const PayloadDTO& payload, const SorImportDTO::Wrapper& dto)
{
	SorDAO sordao;
	SorInfoDAO sorinfodao;
	std::string sor_uuid;
	return sordao.importData(payload,dto,sor_uuid)&&sorinfodao.importData(payload,dto,sor_uuid);
}




SO_by_saleJsonVO::Wrapper SorService::getSellGenerateData(const SellGenerateDTO::Wrapper& create)
{
	std::string pid = create->pid;
	auto res = SO_by_saleJsonVO::createShared();
	SellInfoService ser;
	PtrSellInfoDO sdo = ser.queryByPid(pid);
	// 如果查询失败
	if (!sdo)
	{
		res->code = 114514;
		res->message = "Can't find the corresponding PID";
		return res;
	}

	res->pid = String(sdo.get()->getPid());
	res->goods = String(sdo.get()->getGoods());
	res->unit = String(sdo.get()->getUnit());
	//仓库要与销售订单一致
	res->warehouse = create->warehouse;
	res->price = sdo.get()->getPrice();
	res->nums = sdo.get()->getNums();
	res->total = sdo.get()->getTotal();
	res->tax = sdo.get()->getTax();
	res->tat = sdo.get()->getTat();
	res->tpt = sdo.get()->getTpt();


	return res;
}

PO_by_saleJsonVO::Wrapper SorService::getPurchaseGenerateData(const PurchaseGenerateDTO::Wrapper& create)
{
	std::string pid = create->pid;
	auto res = PO_by_saleJsonVO::createShared();
	BorInfoService ber;
	PtrBorInfoDO sdo = ber.queryByPid(pid);
	// 如果查询失败
	if (!sdo)
	{
		res->code = 114514;
		res->message = "Can't find the corresponding PID";
		return res;
	}

	res->pid = String(sdo.get()->getPid());
	res->goods = String(sdo.get()->getGoods());
	res->unit = String(sdo.get()->getUnit());
	//仓库要与销售订单一致
	res->warehouse = create->warehouse;
	res->price = sdo.get()->getPrice();
	res->nums = sdo.get()->getNums();
	res->total = sdo.get()->getTotal();
	res->tax = sdo.get()->getTax();
	res->tat = sdo.get()->getTat();
	res->tpt = sdo.get()->getTpt();

	return res;
}


//分页查询销售订单列表（条件+分页）
SaleOrderListPageDTO::Wrapper SorService::listAll(const SaleOrderListQuery::Wrapper& query) {
	auto page = SaleOrderListPageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	SorDAO sd;
	auto count = sd.count(query);
	if (count <= 0) {
		return page;
	}
	page->total = count;
	page->calcPages();

	//std::string urlPrefix = getDfsServerAddrssUrl();
	auto list = sd.selectAll(query);

	for (auto one : list) {
		auto saleOrder = SaleOrderListDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO_1(saleOrder, one, frame, Frame, customer, Customer, time, Time, number,
			Number, total, Total, actual, Actual, arrival, Arrival, people, People, examine, Examine, state,
			State, user, User, data, Data);
		//判断
		/*if (one->getAnnex()) {
			saleOrder->fileUrl = urlPrefix + one->getAnnex()->getSavePath();
		}*/
		page->addData(saleOrder);
	}
	return page;
}

std::string SorService::saveData(const SaleOrderAddDTO::Wrapper& dto) {
	//将dto中数据提取到do中
	//dto中sor字段正常，sorinfo和good字段存储在列表字段中
	UuidFacade uf(1);
	auto id = uf.genUuid();
	std::cout << id << " " << id.size() << '\n';

	//存储销售订单字段
	SorDO sdo;
	sdo.setId(id);
	//sdo.setExamine(0);
	ZO_STAR_DOMAIN_DTO_TO_DO(sdo, dto, Customer, customer, Time, time, Number, number, Total, total, Actual,
		actual, People, people, Arrival, arrival, Logistics, logistics, Data, data, Examine, examine, State,
		state, User, user);
	SorDAO sd;
	SorInfoDAO sid;
	// 定义事务管理器
	TransactionManager tm(&sd, &sid);
	int rows = sd.insert(sdo);
	// 存储销售订单详情
	for (auto& goodinfodto : *dto->goodses) {
		SorInfoDO sido;
		sido.setId(uf.genUuid());
		sido.setPid(id);
		ZO_STAR_DOMAIN_DTO_TO_DO(sido, goodinfodto, Total, total, Tat, tat);
		sido.setTpt(sido.getTotal() - sido.getTat());
		ZO_STAR_DOMAIN_DTO_TO_DO(sido, goodinfodto, Goods, goods, Attr, attr, Unit, unit, Warehouse,
			warehouse, Price, price, Nums, nums, Discount, discount, Dsc, dsc, Total, total);
		rows += sid.insert(sido);
	}
	// 判断是否提交事务
	if (rows == dto->goodses->size() + 1)
	{
		tm.commit();
		return id;
	}
	tm.rollback();
	return "";
}

////获取文件服务器地址
//std::string SorService::getDfsServerAddrssUrl() {
//	/** 定义一个Nacos客户端对象，用于获取配置 */
//	NacosClient _ns(ServerInfo::getInstance().getNacosAddr(), ServerInfo::getInstance().getNacosNs());
//#ifdef LINUX
//	/** 读取配置数据节点 */
//	auto _thirdServerConfig = _ns.getConfig("third-services.yaml");
//#else
//	/** 读取配置数据节点 */
//	auto _thirdServerConfig = _ns.getConfig("./conf/third-services.yaml");
//#endif
//	return "http://" + YamlHelper().getString(&_thirdServerConfig, "fastdfs.nginx-servers") + "/";
//}


bool SorService::deleteById(const oatpp::String& id)
{
    if (!id || id->empty()) {
        return false;
    }
    const char* idStr = id->c_str();
    SorDAO dao;
    if (idStr == nullptr) {
        return false;
    }
    return dao.deleteById(idStr);
}

// 批量删除销售订单
SorDeleteResultVO::Wrapper SorService::batchDelete(const SorDeleteDTO::Wrapper& dto)
{
    auto result = SorDeleteResultVO::createShared();
    result->successCount = 0;
    result->failureCount = 0;
    result->failedOrderIds = oatpp::List<oatpp::String>::createShared();

    if (!dto || !dto->orderIds) {
        return result;
    }

    SorDAO dao;

    for (const auto& id : *dto->orderIds) {
        if (!id || id->empty()) {
            result->failureCount = result->failureCount + 1;
            result->failedOrderIds->push_back(id);
            continue;
        }

        try {
            if (deleteById(id)) {
                result->successCount = result->successCount + 1;
            }
            else {
                result->failureCount = result->failureCount + 1;
                result->failedOrderIds->push_back(id);
            }
        }
        catch (...) {
            result->failureCount = result->failureCount + 1;
            result->failedOrderIds->push_back(id);
        }
    }

    return result;
}

// 批量审核 - 保留带失败订单ID列表的版本
SorAuditResultVO::Wrapper SorService::batchApprove(const SorAuditDTO::Wrapper& dto)
{
    auto result = SorAuditResultVO::createShared();
    result->successCount = 0;
    result->failureCount = 0;
    result->failedOrderIds = oatpp::List<oatpp::String>::createShared();

    if (!dto || !dto->orderIds) {
        return result;
    }

    SorDAO dao;

    for (const auto& id : *dto->orderIds) {
        if (!id || id->empty()) {
            result->failureCount = result->failureCount + 1;
            result->failedOrderIds->push_back(id);
            continue;
        }

        try {
            if (dao.approveById(id->c_str())) {
                result->successCount = result->successCount + 1;
            }
            else {
                result->failureCount = result->failureCount + 1;
                result->failedOrderIds->push_back(id);
            }
        }
        catch (...) {
            result->failureCount = result->failureCount + 1;
            result->failedOrderIds->push_back(id);
        }
    }

    return result;
}

// 批量反审核 - 保留带失败订单ID列表的版本
SorAuditResultVO::Wrapper SorService::batchUnapprove(const SorAuditDTO::Wrapper& dto)
{
    auto result = SorAuditResultVO::createShared();
    result->successCount = 0;
    result->failureCount = 0;
    result->failedOrderIds = oatpp::List<oatpp::String>::createShared();

    if (!dto || !dto->orderIds) {
        return result;
    }

    SorDAO dao;

    for (const auto& id : *dto->orderIds) {
        if (!id || id->empty()) {
            result->failureCount = result->failureCount + 1;
            result->failedOrderIds->push_back(id);
            continue;
        }

        try {
            if (dao.unapproveById(id->c_str())) {
                result->successCount = result->successCount + 1;
            }
            else {
                result->failureCount = result->failureCount + 1;
                result->failedOrderIds->push_back(id);
            }
        }
        catch (...) {
            result->failureCount = result->failureCount + 1;
            result->failedOrderIds->push_back(id);
        }
    }

    return result;
}

bool SorService::updateSaleOrder(const SorUpdateDTO::Wrapper& dto)
{
	if(!dto->id || dto->id->empty()) {
		return false;
	}
	auto id = dto->id->c_str();
	auto sorDO = std::make_shared<SorDO>();
	sorDO->setId(id);
	if(dto->customer && !dto->customer->empty()) {
		sorDO->setCustomer(dto->customer->c_str());
	}
	if(dto->time && !dto->time->empty()) {
		sorDO->setTime(dto->time->c_str());
	}
	if(dto->data && !dto->data->empty()) {
		sorDO->setData(dto->data->c_str());
	}
	if(dto->logistics && !dto->logistics->empty()) {
		sorDO->setLogistics(dto->logistics->c_str());
	}
	if(dto->people && !dto->people->empty()) {
		sorDO->setPeople(dto->people->c_str());
	}
	sorDO->setActual(dto->actual);
	if(dto->arrival && !dto->arrival->empty()) {
		sorDO->setArrival(dto->arrival->c_str());
	}
	if(dto->file && !dto->file->empty()) {
		sorDO->setFile(dto->file->c_str());
	}
	SorDAO dao;
	return dao.SorUpdate(sorDO);
	
}

std::vector<SorExportSimpleDTO::Wrapper> SorService::querySimpleReport(const SorExportSimpleQuery::Wrapper& query)
{
	std::string startDate = query->startDate ? query->startDate->c_str() : "";
	std::string endDate = query->endDate ? query->endDate->c_str() : "";

	SorDAO dao;
	// 查询简单报表数据
	auto sorDOList = dao.querySimpleReport(startDate, endDate);
	std::vector<SorExportSimpleDTO::Wrapper> dtoList;
	for(const auto& sorDO : sorDOList) {
		auto dto = SorExportSimpleDTO::createShared();
		dto->frame = sorDO->getFrame();
		dto->customer = sorDO->getCustomer();
		dto->time = sorDO->getTime();
		dto->number = sorDO->getNumber();
		dto->total = sorDO->getTotal();
		dto->actual = sorDO->getActual();
		dto->arrival = sorDO->getArrival();
		dto->people = sorDO->getPeople();
		dto->examine = sorDO->getExamine();
		dto->state = sorDO->getState();
		dto->user = sorDO->getUser();
		dto->data = sorDO->getData();
		dtoList.push_back(dto);
	}
	return dtoList;
}

std::vector<SorExportDetailDTO::Wrapper> SorService::queryDetailReport(const SorExportDetailQuery::Wrapper& query)
{
	std::string orderNoLike = query->orderNoLike ? query->orderNoLike->c_str() : "";
	SorDAO dao;
	auto sorDOList = dao.queryDetailReport(orderNoLike);
	std::vector<SorExportDetailDTO::Wrapper> dtoList;
	for (const auto& sorDO : sorDOList) {
		auto dto = SorExportDetailDTO::createShared();
		dto->customer = sorDO->sor->getCustomer();
		dto->time = sorDO->sor->getTime();
		dto->number = sorDO->sor->getNumber();
		dto->total = sorDO->sor->getTotal();
		dto->actual = sorDO->sor->getActual();
		dto->people = sorDO->sor->getPeople();
		dto->arrival = sorDO->sor->getArrival();
		dto->logistics = sorDO->sor->getLogistics();
		dto->data = sorDO->sor->getData();

		auto items = oatpp::data::mapping::type::Vector<SorExportDetailItemDTO::Wrapper>::createShared();
		for (const auto& item : sorDO->sorInfoList) {
			auto itemDTO = SorExportDetailItemDTO::createShared();
			itemDTO->goodsName = item->getGoodsName();
			itemDTO->spec = item->getSpec();
			itemDTO->attr = item->getAttr();
			itemDTO->unit = item->getUnit();
			itemDTO->warehouse = item->getWarehouse();
			itemDTO->price = item->getPrice();
			itemDTO->nums = item->getNums();
			itemDTO->handle = item->getHandle();
			itemDTO->discount = item->getDiscount();
			itemDTO->dsc = item->getDsc();
			itemDTO->total = item->getTotal();
			itemDTO->data = item->getData();
			items->push_back(itemDTO);
		}
		dto->items = items;
		dtoList.push_back(dto);
	}
	return dtoList;
}