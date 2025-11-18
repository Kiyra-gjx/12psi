#include "stdafx.h"
#include "SreService.h"
#include "dao/SreInfoDAO/SreInfoDAO.h"
#include "../SreInfoService/SreInfoService.h"
#include "domain/do/SrebillDO.h"
#include "dao/SrebillDAO/SrebillDAO.h"
#include "id/UuidFacade.h"
#include <regex>
#include "./dao/SreDAO/SreDAO.h"       // SreDAO
#include "domain/do/SreDO.h"     // 销售退货单主表DO
#include "domain/do/SreInfoDO.h" // 销售退货单明细表DO

SrePageDTO::Wrapper SreService::listAll(const SreListQuery::Wrapper& query) {
	//构建返回对象
    auto sreLists = SrePageDTO::createShared();
	sreLists->pageIndex = query->pageIndex;
	sreLists->pageSize = query->pageSize;

	//查询数据总条数
	SreDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0) {
		return sreLists;
	}

	//分页查询
	sreLists->total = count;
	sreLists->calcPages();
	list<SreViewDO> result = dao.selectWithPage(query);
	

	//SreViewDO转为SreListDTO并加入SrePageDTO
	for (SreViewDO& sub : result) {
		auto dto = SreListDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id, frame, Frame, customer, Customer, time, Time,number, Number);
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, totalMoney, Total, actual, Actual, money, Money, cost, Cost,people, People, data, Data);
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, examine, Examine, nucleus, Nucleus, cse, Cse, invoice, Invoice, check, Check, user, User);
		sreLists->addData(dto);
	}

	return sreLists;
}

SreDetailDTO::Wrapper SreService::getDetail(const SreDetailQuery::Wrapper& query) {
	SreListDTO listDto;
	SreInfoDAO infDao;
	SreDAO listDao;
	SreInfoService infService;
	auto detail = SreDetailDTO::createShared();

	//listDO转为detailDTO中的对应部分
	uint64_t count = listDao.countById(query);
	if (count <= 0) {
		return detail;
	}

	//实际上list内只有一个变量,但是不知道为什么用front取值会显示临时变量被销毁
	for (auto& listDo : listDao.selectById(query)) {
		ZO_STAR_DOMAIN_DO_TO_DTO(detail, listDo, id, Id, frame, Frame, customer, Customer, time, Time, number, Number);
		ZO_STAR_DOMAIN_DO_TO_DTO(detail, listDo, totalMoney, Total, actual, Actual, money, Money, cost, Cost, people, People, data, Data);
		ZO_STAR_DOMAIN_DO_TO_DTO(detail, listDo, examine, Examine, nucleus, Nucleus, cse, Cse, invoice, Invoice, check, Check, user, User);
	}
	
	count = infDao.count(query);
	if (count <= 0) {
		return detail;
	}
	detail->handle = count;
	auto infos = infService.getSreInfosByid(query);
	detail->sreinfos = infos;
	return detail;
}

std::string SreService::addList(const SreAddDTO::Wrapper& dto) {
	//虽然标了下划线，但是生成id没问题
	UuidFacade uf(1);
	string sreid = uf.genUuid();

	//获取多条SreInfoDO并插入
	double totalMoney = 0;
	double actual = 0;
	if (dto->infos) {
		int serial = 0;
		SreInfoDAO infoDAO;
		for (auto& one : *dto->infos) {
			serial++;
			auto infoDO = make_shared<SreInfoDO>();
			infoDO->setId(uf.genUuid());
			infoDO->setPid(sreid);
			infoDO->setSource(one->source ? one->source->c_str() : "");
			infoDO->setGoods(one->goods ? one->goods->c_str() : "");
			infoDO->setAttr(one->attr ? one->attr->c_str() : "");
			infoDO->setUnit(one->unit ? one->unit->c_str() : "");
			infoDO->setWarehouse(one->warehouse ? one->warehouse->c_str() : "");
			infoDO->setBatch(one->batch ? one->batch->c_str() : "");
			infoDO->setMfd(one->mfd ? one->mfd->c_str() : "2025-1-1");
			infoDO->setSerial(std::to_string(serial));
			infoDO->setData(one->mfd ? one->data->c_str() : "");
			infoDO->setPrice(one->price ? *one->price : 0.0);
			infoDO->setNums(one->nums ? *one->nums : 0.0);
			infoDO->setDiscount(one->discount ? *one->discount : 0.0);
			
			//计算金额
			double total = infoDO->getNums() * infoDO->getPrice();
			totalMoney += total;
			double dsc = infoDO->getDiscount() * total;
			total -= dsc;
			actual += total;

			infoDO->setTotal(total);
			infoDO->setDsc(dsc);
			infoDO->setTax(0.0);		//找不到税率相关的传入入口
			infoDO->setTat(0.0);
			infoDO->setTpt(0.0);
			try {
				infoDAO.insert(infoDO);
			}
			catch (const exception& e) {
				OATPP_LOGE("SreService", "addList SreInfoDO Failed %s,serial = %d", e.what(),serial);
				return "";
			}
		}
	}else{
		return "";
	}

	//获取SreDO并插入
	auto sreDO = std::make_shared<SreDO>();
	sreDO->setId(sreid);
	sreDO->setSource(dto->source ? dto->source->c_str() : "");
	sreDO->setFrame(dto->frame ? dto->frame->c_str() : "");
	sreDO->setCustomer(dto->customer ? dto->customer->c_str() : "");
	sreDO->setTime(dto->time ? dto->time->c_str() : "2025-1-1");
	sreDO->setNumber(dto->number ? dto->source->c_str() : "xxxx");

	sreDO->setTotal(totalMoney);
	sreDO->setActual(actual);
	sreDO->setMoney(dto->money ? *dto->money : 0.0);
	sreDO->setCost(dto->cost ? *dto->cost : 0.0);

	sreDO->setAccount(dto->account ? dto->account->c_str() : "");
	sreDO->setPeople(dto->people ? dto->people->c_str() : "");
	sreDO->setLogistics(dto->logistics ? dto->logistics->c_str() : "");
	sreDO->setFile(dto->file ? dto->file->c_str() : "");
	sreDO->setData(dto->data ? dto->data->c_str() : "");
	sreDO->setMore(dto->more ? dto->more->c_str() : "");
	sreDO->setUser(dto->user ? dto->user->c_str() : "");

	sreDO->setExamine(dto->examine ? *dto->examine : 0);
	sreDO->setNucleus(dto->nucleus ? *dto->nucleus : 0);
	sreDO->setCse(dto->cse ? *dto->cse : 0);
	sreDO->setInvoice(dto->invoice ? *dto->invoice : 0);
	sreDO->setCheck(dto->check ? *dto->check : 0);
	SreDAO sreDAO;
	try {
		sreDAO.insert(sreDO);
	}
	catch (const exception& e) {
		OATPP_LOGE("SreService", "addList sreDO Failed:%s", e.what());
		return "";
	}

	//获取SreBillDO并插入
	auto srebillDO = std::make_shared<SrebillDO>();
	srebillDO->setId(uf.genUuid());
	srebillDO->setPid(sreid);
	srebillDO->setType("");		//不清楚什么叫做核销类型
	srebillDO->setSource(dto->source ? dto->source->c_str() : "");
	srebillDO->setTime(dto->time ? dto->time->c_str() : "2025-1-1");
	srebillDO->setMoney(0);		//默认核销金额为0
	SrebillDAO billDAO;
	try {
		billDAO.insert(srebillDO);
	}
	catch (const exception& e) {
		OATPP_LOGE("SreService", "addList SrebillDO Failed %s", e.what());
		return "";
	}
	return sreDO->getId();
}

//松 额外实现的方法1 ————更新退货单
StringJsonVO::Wrapper SreService::update(const SreUpdateDTO::Wrapper& dto) {
	auto resp = StringJsonVO::createShared();
	try {

		// 1. 校验必填字段 `id`（无值则直接返回错误）
		if (!dto->id || dto->id->empty()) {
			resp->code = 400;
			resp->message = "退货单ID不能为空";
			resp->data = "fail";
			return resp;
		}
		std::string id = dto->id->c_str(); // 提取原生字符串


		// 1. DTO → DO 转换
		auto sreDO = std::make_shared<SreDO>();
		sreDO->setId(dto->id);
		if (dto->customer)      sreDO->setCustomer(dto->customer.getValue(""));
		if (dto->time)          sreDO->setTime(dto->time.getValue(""));
		if (dto->data)          sreDO->setData(dto->data.getValue(""));
		if (dto->logistics)     sreDO->setLogistics(dto->logistics.getValue(""));
		if (dto->file)          sreDO->setFile(dto->file.getValue(""));
		if (dto->more)          sreDO->setMore(dto->more.getValue(""));
		char examineVal = dto->examine ? static_cast<char>(dto->examine.getValue(0)) : 0;
		sreDO->setExamine(examineVal);

		// 2. 调用DAO执行修改
		SreDAO dao;
		bool isSuccess = dao.update(sreDO);

		// 3. 构造响应VO
		resp->code = 200;
		resp->message = isSuccess ? "销售退货单修改成功" : "销售退货单修改失败";
		resp->data = isSuccess ? "success" : "fail";
	}
	catch (const std::exception& e) {
		resp->code = 500;
		resp->message = "系统异常：" + std::string(e.what());
		resp->data = "";
	}
	return resp;
}

//松 额外实现的方法2 ————导出简单报表
std::vector<SreExportSimpleDTO::Wrapper> SreService::querySimpleList(const SreExportSimpleQuery::Wrapper& query) {

	//类型转换报的空指针错误处理
	std::string startDate = query->startDate ? query->startDate->c_str() : "";
	std::string endDate = query->endDate ? query->endDate->c_str() : "";

	// 1. 调用DAO查询主表数据
	SreDAO dao;

	auto sreDOList = dao.querySimpleList(
		startDate,
		endDate
	);

	// 2. DO → DTO 转换
	std::vector<SreExportSimpleDTO::Wrapper> dtoList;
	for (const auto& doItem : sreDOList) {
		auto dto = SreExportSimpleDTO::createShared();
		dto->frame = doItem->getFrame();
		dto->customer = doItem->getCustomer();
		dto->time = doItem->getTime();
		dto->number = doItem->getNumber();
		dto->total = doItem->getTotal();
		dto->actual = doItem->getActual();
		dto->money = doItem->getMoney();
		dto->cost = doItem->getCost();
		dto->people = doItem->getPeople();
		dto->examine = static_cast<oatpp::Int8>(doItem->getExamine()); // char→Int8
		dto->nucleus = static_cast<oatpp::Int8>(doItem->getNucleus());
		dto->cse = static_cast<oatpp::Int8>(doItem->getCse());
		dto->invoice = static_cast<oatpp::Int8>(doItem->getInvoice());
		dto->check = static_cast<oatpp::Int8>(doItem->getCheck());
		dto->user = doItem->getUser();
		dto->data = doItem->getData();
		dtoList.push_back(dto);
	}
	return dtoList;
}

//松 额外实现的方法3————导出详细报表
std::vector<SreExportDetailDTO::Wrapper> SreService::queryDetailList(const SreExportDetailQuery::Wrapper& query) {
	// 1. 提取查询参数（处理 oatpp 包装类型 → 原生类型）
	std::string orderNoLike = query->orderNoLike ? query->orderNoLike->c_str() : "";
	std::string customer = query->customer ? query->customer->c_str() : "";
	//int examineStatus = query->examineStatus ? query->examineStatus.getValue(-1) : -1;

	// 1. 调用DAO查询主表+明细表关联数据
	SreDAO dao;
	auto detailDOList = dao.queryDetailList(
		orderNoLike,
		customer
		//examineStatus
	);

	//// ========== 控制台打印：验证 DAO 返回的 DO 列表 ==========
	//std::cout << "DAO 返回的 detailDOList 大小: " << detailDOList.size() << std::endl;
	//if (!detailDOList.empty()) {
	//    auto firstDO = detailDOList[0];
	//    if (firstDO && firstDO->mainDO) {
	//        std::cout << "第一个 DO 的主表 ID: " << firstDO->mainDO->getId() << std::endl;
	//        std::cout << "第一个 DO 的明细数量: " << firstDO->itemDOList.size() << std::endl;
	//    }
	//    else {
	//        std::cout << "第一个 DO 或其 mainDO 为空" << std::endl;
	//    }
	//}
	//else {
	//    std::cout << "DAO 返回的 detailDOList 为空" << std::endl;
	//    return {}; // 直接返回空，避免后续转换
	//}
	// 2. DO → DTO 转换（主表+商品明细）

	std::vector<SreExportDetailDTO::Wrapper> dtoList;
	for (const auto& detailDO : detailDOList) {
		if (!detailDO || !detailDO->mainDO) continue;

		auto dto = SreExportDetailDTO::createShared();
		// 主表信息转换
		dto->customer = detailDO->mainDO->getCustomer();
		dto->billDate = detailDO->mainDO->getTime();
		dto->billNo = detailDO->mainDO->getNumber();
		dto->billAmount = detailDO->mainDO->getTotal();
		dto->billCost = detailDO->mainDO->getCost();
		dto->actualAmount = detailDO->mainDO->getActual();
		dto->writeOffAmount = static_cast<oatpp::Float64>(detailDO->mainDO->getNucleus());
		dto->settlementAccount = detailDO->mainDO->getAccount();
		dto->invoiceInfo = static_cast<oatpp::Int32>(detailDO->mainDO->getInvoice());
		dto->relatedPerson = detailDO->mainDO->getPeople();
		dto->logisticsInfo = detailDO->mainDO->getLogistics();
		dto->remark = detailDO->mainDO->getData();

		// 商品明细转换
		auto items = oatpp::data::mapping::type::Vector<SreDetailItemDTO::Wrapper>::createShared();
		for (const auto& itemDO : detailDO->itemDOList) {
			if (!itemDO) continue;
			auto itemDTO = SreDetailItemDTO::createShared();
			itemDTO->goodsName = itemDO->getGoodsName();
			itemDTO->spec = itemDO->getSpec();
			itemDTO->attr = itemDO->getAttr();
			itemDTO->unit = itemDO->getUnit();
			itemDTO->warehouse = itemDO->getWarehouse();
			itemDTO->price = itemDO->getPrice();
			itemDTO->nums = itemDO->getNums();
			itemDTO->discountRate = itemDO->getDiscount();
			itemDTO->discountAmount = itemDO->getDsc();
			itemDTO->amount = itemDO->getTotal();
			itemDTO->taxRate = itemDO->getTax();
			itemDTO->taxAmount = itemDO->getTat();
			itemDTO->taxIncludedAmount = itemDO->getTpt();
			itemDTO->remark = itemDO->getData();
			items->push_back(itemDTO);
		}
		dto->items = items;

		dtoList.push_back(dto);
	}
	return dtoList;
}

bool SreService::removeById(const std::string& id) {
	SreDAO sreDAO;
	SreInfoDAO infoDAO;
	SrebillDAO billDAO;
	
	try {
		OATPP_LOGI("SreService", "removeById: Starting deletion for sale return order id=%s", id.c_str());
		
		// 1. 首先删除退货单详情表（sre_info）中的关联记录
		// 注意：这里的id在sre_info表中对应的是pid字段
		bool infoDeleted = infoDAO.removeByPid(id);
		if (!infoDeleted) {
			OATPP_LOGE("SreService", "removeById: Failed to delete sre_info records for pid=%s", id.c_str());
			return false;
		}
		OATPP_LOGI("SreService", "removeById: Successfully deleted sre_info records for pid=%s", id.c_str());
		
		// 2. 删除退货单账单表（sre_bill）中的关联记录
		// 注意：这里的id在sre_bill表中对应的是pid字段
		bool billDeleted = billDAO.removeByPid(id);
		if (!billDeleted) {
			OATPP_LOGE("SreService", "removeById: Failed to delete sre_bill records for pid=%s", id.c_str());
			return false;
		}
		OATPP_LOGI("SreService", "removeById: Successfully deleted sre_bill records for pid=%s", id.c_str());
		
		// 3. 最后删除退货单主表（sre）记录
		bool sreDeleted = sreDAO.delById(id);
		if (!sreDeleted) {
			OATPP_LOGE("SreService", "removeById: Failed to delete sre record for id=%s", id.c_str());
			return false;
		}
		
		OATPP_LOGI("SreService", "removeById: Successfully deleted sale return order id=%s and all related records", id.c_str());
		return true;
	}
	catch (const exception& e) {
		OATPP_LOGE("SreService", "removeById: Exception occurred while deleting id=%s - %s", id.c_str(), e.what());
		return false;
	}
}

bool SreService::checkById(const std::string& id, bool checkStatus) {
	SreDAO sreDAO;
	
	try {
		OATPP_LOGI("SreService", "checkById: Starting check operation for sale return order id=%s, checkStatus=%d", 
			id.c_str(), checkStatus ? 1 : 0);
		
		// 更新销售退货单的核对状态
		// checkStatus: true表示核对(状态值为1), false表示反核对(状态值为0)
		bool updated = sreDAO.updateCheckStatus(id, checkStatus ? 1 : 0);
		
		if (!updated) {
			OATPP_LOGE("SreService", "checkById: Failed to update check status for id=%s", id.c_str());
			return false;
		}
		
		OATPP_LOGI("SreService", "checkById: Successfully updated check status for id=%s to %d", 
			id.c_str(), checkStatus ? 1 : 0);
		return true;
	}
	catch (const exception& e) {
		OATPP_LOGE("SreService", "checkById: Exception occurred while updating check status for id=%s - %s", 
			id.c_str(), e.what());
		return false;
	}
}

//批量审核退货单
BatchOperationVO::Wrapper SreService::batchApprove(const SaleReturnAuditDTO::Wrapper& dto)
{
	auto result = BatchOperationVO::createShared();
	result->successCount = 0;
	result->failureCount = 0;
	result->failureIds = oatpp::Vector<oatpp::String>::createShared();

	if (!dto || !dto->ids) {
		return result;
	}

	SreDAO dao;

	for (const auto& id : *dto->ids) {
		if (!id || id->empty()) {
			result->failureCount = result->failureCount + 1;
			result->failureIds->push_back(id);
			continue;
		}

		try {
			if (dao.approveById(id->c_str())) {
				result->successCount = result->successCount + 1;
			}
			else {
				result->failureCount = result->failureCount + 1;
				result->failureIds->push_back(id);
			}
		}
		catch (...) {
			result->failureCount = result->failureCount + 1;
			result->failureIds->push_back(id);
		}
	}

	return result;
}

//批量反审核退货单
BatchOperationVO::Wrapper SreService::batchUnapprove(const SaleReturnAuditDTO::Wrapper& dto)
{
	auto result = BatchOperationVO::createShared();
	result->successCount = 0;
	result->failureCount = 0;
	result->failureIds = oatpp::Vector<oatpp::String>::createShared();

	if (!dto || !dto->ids) {
		return result;
	}

	SreDAO dao;

	for (const auto& id : *dto->ids) {
		if (!id || id->empty()) {
			result->failureCount = result->failureCount + 1;
			result->failureIds->push_back(id);
			continue;
		}

		try {
			if (dao.unapproveById(id->c_str())) {
				result->successCount = result->successCount + 1;
			}
			else {
				result->failureCount = result->failureCount + 1;
				result->failureIds->push_back(id);
			}
		}
		catch (...) {
			result->failureCount = result->failureCount + 1;
			result->failureIds->push_back(id);
		}
	}

	return result;
}

//数据导入

ImportResultDTO::Wrapper SreService::importData(const SaleReturnBatchImportDTO::Wrapper& dto) {
	auto result = ImportResultDTO::createShared();

	if (!dto || !dto->importData) {
		result->successCount = 0;
		result->failCount = 0;
		result->totalCount = 0;
		return result;
	}

	result->totalCount = dto->importData->size();
	result->successCount = 0;
	result->failCount = 0;
	result->errors = {};

	SreDAO sreDao;

	int rowIndex = 0;
	for (const auto& importDto : *dto->importData) {
		rowIndex++;

		try {
			std::string sre_uuid;

			// 创建PayloadDTO对象
			PayloadDTO payload;
			payload.setUsername(*dto->username);  // 设置用户名

			// 使用payload参数调用importData
			if (!sreDao.importData(payload, importDto, sre_uuid)) {
				auto error = ImportErrorDTO::createShared();
				error->rowIndex = rowIndex;
				error->number = importDto->number;
				error->message = "导入销售退货单失败";
				result->errors->push_back(error);
				result->failCount = result->failCount + 1;
				continue;
			}

			result->successCount = result->successCount + 1;

		}
		catch (const std::exception& e) {
			auto error = ImportErrorDTO::createShared();
			error->rowIndex = rowIndex;
			error->number = importDto->number;
			error->message = "导入过程中发生异常: " + std::string(e.what());
			result->errors->push_back(error);
			result->failCount = result->failCount + 1;
		}
	}

	return result;
}