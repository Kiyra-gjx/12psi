#include "stdafx.h"
#include "SellService.h"
#include "../../dao/SellDAO/SellDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"
#include <iostream>
#include"../../dao/SellInfoDAO/SellInfoDAO.h"
#include "dao/SellbillDAO/SellbillDAO.h"

SellPageDTO::Wrapper SellService::queryWithPage(const SellListQuery::Wrapper& query)
{
	auto pagedto = SellPageDTO::createShared();
	//构建返回对象
	pagedto->pageIndex = query->pageIndex;
	pagedto->pageSize = query->pageSize;

	//查询数据总条数
	SellDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0) {
		return pagedto;
	}

	//分页查询
	pagedto->total = count;
	pagedto->calcPages();
	auto result = dao.selectWithPage(query);

	//SellViewDO转为SellListDTO并加入SellPageDTO
	for (auto& sub : result) {
		auto dto = SellListDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, (*sub), id, Id, frame, Frame, customer, Customer, time, Time, number, Number);
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, (*sub), totalMoney, Total, actual, Actual, money, Money, cost, Cost, people, People, data, Data);
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, (*sub), examine, Examine, nucleus, Nucleus, cse, Cse, invoice, Invoice, check, Check, user, User);
		pagedto->addData(dto);
	}

	return pagedto;
}

SellDetailDTO::Wrapper SellService::queryById(const std::string& id)
{
	//取出详细商品信息
	auto detail_dto = SellDetailDTO::createShared();
	SellInfoDAO inf_dao;
	uint64_t count = inf_dao.count(id);
	if (count <= 0) {
		return detail_dto;
	}

	auto list_info_do = inf_dao.select(id);
	detail_dto->sellinfos = oatpp::List<OneSingleInfoDTO::Wrapper>::createShared();
	for (auto& one_do : list_info_do) {
		if (one_do == nullptr) continue;
		auto info_dto = OneSingleInfoDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(info_dto, (*one_do), goodsName, GoodsName, goodsNumber, GoodsNumber, goodsSpec, GoodsSpec, attr, Attr, unit, Unit, retreat, Retreat);
		ZO_STAR_DOMAIN_DO_TO_DTO(info_dto, (*one_do), warehouse, Warehouse, price, Price, nums, Nums, discount, Discount, dsc, Dsc, total, Total, data, Data);
		detail_dto->sellinfos->push_back(info_dto);
	}

	//取出主信息
	SellDAO sell_dao;
	if (sell_dao.countById(id) <= 0) {
		return detail_dto;
	}
	auto one_do = sell_dao.selectById(id);
	ZO_STAR_DOMAIN_DO_TO_DTO(detail_dto, (*one_do), id, Id, frame, Frame, customer, Customer, time, Time, number, Number);
	ZO_STAR_DOMAIN_DO_TO_DTO(detail_dto, (*one_do), totalMoney, Total, actual, Actual, money, Money, cost, Cost, people, People, data, Data);
	ZO_STAR_DOMAIN_DO_TO_DTO(detail_dto, (*one_do), examine, Examine, nucleus, Nucleus, cse, Cse, invoice, Invoice, check, Check, user, User);
	detail_dto->handle = count;

	return detail_dto;
}

std::string SellService::create(const SellCreateDTO::Wrapper& dto)
{
	//虽然标了下划线，但是生成id没问题
	UuidFacade uf(1);
	string sellid = uf.genUuid();

	//获取多条sellInfoDO并插入
	double totalMoney = 0;
	double actual = 0;
	if (dto->sellinfos) {
		int serial = 0;
		SellInfoDAO infoDAO;
		for (auto& one : *dto->sellinfos) {
			serial++;
			auto infoDO = make_shared<SellInfoDO>();
			infoDO->setId(uf.genUuid());
			infoDO->setPid(sellid);
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
			infoDO->setRetreat(0.0);
			try {
				infoDAO.insert(*infoDO);
			}
			catch (const exception& e) {
				OATPP_LOGE("SellService", "addList SellInfoDO Failed %s,serial = %d", e.what(), serial);
				return "";
			}
		}
	}
	else {
		return "";
	}

	//获取SellDO并插入
	auto sellDO = std::make_shared<SellDO>();
	sellDO->setId(sellid);
	sellDO->setSource(dto->source ? dto->source->c_str() : "");
	sellDO->setFrame(dto->frame ? dto->frame->c_str() : "");
	sellDO->setCustomer(dto->customer ? dto->customer->c_str() : "");
	sellDO->setTime(dto->time ? dto->time->c_str() : "2025-1-1");
	sellDO->setNumber(dto->number ? dto->source->c_str() : "xxxx");

	sellDO->setTotal(totalMoney);
	sellDO->setActual(actual);
	sellDO->setMoney(dto->money ? *dto->money : 0.0);
	sellDO->setCost(dto->cost ? *dto->cost : 0.0);

	sellDO->setAccount(dto->account ? dto->account->c_str() : "");
	sellDO->setPeople(dto->people ? dto->people->c_str() : "");
	sellDO->setLogistics(dto->logistics ? dto->logistics->c_str() : "");
	sellDO->setFile(dto->file ? dto->file->c_str() : "");
	sellDO->setData(dto->data ? dto->data->c_str() : "");
	sellDO->setMore(dto->more ? dto->more->c_str() : "");
	sellDO->setUser(dto->user ? dto->user->c_str() : "");

	sellDO->setExamine(dto->examine ? *dto->examine : 0);
	sellDO->setNucleus(dto->nucleus ? *dto->nucleus : 0);
	sellDO->setCse(dto->cse ? *dto->cse : 0);
	sellDO->setInvoice(dto->invoice ? *dto->invoice : 0);
	sellDO->setCheck(dto->check ? *dto->check : 0);
	SellDAO sellDAO;
	BaseDAO bs;
	try {
		sellDAO.insert(*sellDO);
	}
	catch (const exception& e) {
		OATPP_LOGE("SellService", "addList sellDO Failed:%s", e.what());
		return "";
	}

	//获取SellBillDO并插入
	auto sellbillDO = std::make_shared<SellbillDO>();
	sellbillDO->setId(uf.genUuid());
	sellbillDO->setPid(sellid);
	sellbillDO->setType("");		//不清楚什么叫做核销类型
	sellbillDO->setSource(dto->source ? dto->source->c_str() : "");
	sellbillDO->setTime(dto->time ? dto->time->c_str() : "2025-1-1");
	sellbillDO->setMoney(0);		//默认核销金额为0
	SellbillDAO billDAO;
	try {
		billDAO.insert(*sellbillDO);
	}
	catch (const exception& e) {
		OATPP_LOGE("SellService", "addList SellbillDO Failed %s", e.what());
		return "";
	}
	return sellDO->getId();
}

SellGenerateReturnDTO::Wrapper SellService::getSellGenerateReturn(const oatpp::String& number)
{
	SellDAO selldao;
	SellInfoDAO sellinfodao;
    auto res = selldao.selectByNumber(number);
    if (res.empty())return SellGenerateReturnDTO::Wrapper();
	auto& selldo = res.front();//不知道这算不算移动构造会不会半路销毁
	//SellDO selldo;
	auto sellinfodos = sellinfodao.selectByPid(selldo.getId());
	auto dto = SellGenerateReturnDTO::createShared();
    dto->items = {};
    dto->source = selldo.getSource();//存疑
    dto->frame = selldo.getFrame();
    dto->customer = selldo.getCustomer();
    dto->time = selldo.getTime();
    dto->number = selldo.getNumber();
    dto->total = selldo.getTotal();
    dto->actual = selldo.getActual();
    dto->money = selldo.getMoney();
    dto->cost = selldo.getCost();
    dto->account = selldo.getAccount();
    dto->people = selldo.getPeople();
    dto->logistics = selldo.getLogistics();
    dto->file = selldo.getFile();
    dto->data = selldo.getData();
    dto->more = selldo.getMore();
    dto->examine = selldo.getExamine();
    dto->nucleus = selldo.getNucleus();
    dto->cse = selldo.getCse();
    dto->invoice = selldo.getInvoice();
    dto->check = selldo.getCheck();
    dto->user = selldo.getUser();
    for (auto& tmp : sellinfodos) {
        auto sellinfodto = SellToSreInfoDTO::createShared();
        sellinfodto->source = tmp.getSource();
        sellinfodto->goods = tmp.getGoods();
        sellinfodto->attr = tmp.getAttr();
        sellinfodto->unit = tmp.getUnit();
        sellinfodto->warehouse = tmp.getWarehouse();
        sellinfodto->batch = tmp.getBatch();
        sellinfodto->mfd = tmp.getMfd();
        sellinfodto->price = tmp.getPrice();
        sellinfodto->nums = tmp.getNums();
        sellinfodto->serial = tmp.getSerial();
        sellinfodto->discount = tmp.getDiscount();
        sellinfodto->dsc = tmp.getDsc();
        sellinfodto->total = tmp.getTotal();
        sellinfodto->tax = tmp.getTax();
        sellinfodto->tat = tmp.getTat();
        sellinfodto->tpt = tmp.getTpt();
        sellinfodto->data = tmp.getData();
        dto->items->push_back(sellinfodto);
    }
	return dto;
}
bool  SellService::updateData(const SellUpdateDTO::Wrapper& dto) {
	// 组装DO数据
	SellDO selldata;
	if (dto->id) selldata.setId(dto->id.getValue({})); if (dto->source) selldata.setSource(dto->source.getValue({})); if (dto->frame) selldata.setFrame(dto->frame.getValue({})); if (dto->customer) selldata.setCustomer(dto->customer.getValue({})); if (dto->time) selldata.setTime(dto->time.getValue({})); if (dto->number) selldata.setNumber(dto->number.getValue({})); if (dto->total) selldata.setTotal(dto->total.getValue({})); if (dto->actual) selldata.setActual(dto->actual.getValue({})); if (dto->money) selldata.setMoney(dto->money.getValue({})); if (dto->cost) selldata.setCost(dto->cost.getValue({})); if (dto->account) selldata.setAccount(dto->account.getValue({})); if (dto->people) selldata.setPeople(dto->people.getValue({})); if (dto->logistics) selldata.setLogistics(dto->logistics.getValue({})); if (dto->file) selldata.setFile(dto->file.getValue({}));;
	if (dto->data) selldata.setData(dto->data.getValue({})); if (dto->more) selldata.setMore(dto->more.getValue({})); if (dto->examine) selldata.setExamine(dto->examine.getValue({})); if (dto->nucleus) selldata.setNucleus(dto->nucleus.getValue({})); if (dto->cse) selldata.setCse(dto->cse.getValue({})); if (dto->invoice) selldata.setInvoice(dto->invoice.getValue({})); if (dto->check) selldata.setCheck(dto->check.getValue({})); if (dto->user) selldata.setUser(dto->user.getValue({}));;
	// 执行数据修改
	SellDAO dao;
	return dao.update(selldata) == 1;
}
SellUpdatePageDTO::Wrapper SellService::listAll(const  SellListQuery::Wrapper& query) {
	// 构建返回对象
	auto pages = SellUpdatePageDTO::createShared();

	// 查询数据总条数
	SellDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	std::list<PtrSellViewDO> result = dao.selectWithPage(query);
	// 将DO转换成DTO
	for (auto& sub : result)
	{
		auto dto = SellUpdateDTO::createShared();
		dto->id = sub->getId(); dto->time = sub->getTime(); dto->number = sub->getNumber(); dto->total = sub->getTotal(); dto->frame = sub->getFrame(); dto->customer = sub->getCustomer(); dto->user = sub->getUser(); dto->actual = sub->getActual(); dto->money = sub->getMoney(); dto->cost = sub->getCost(); dto->examine = sub->getExamine(); dto->nucleus = sub->getNucleus(); dto->cse = sub->getCse(); dto->invoice = sub->getInvoice(); dto->check = sub->getCheck();;
		pages->addData(dto);
	}
	return pages;
}



SalenoteDeleteResultVO::Wrapper SellService::batchDelete(const SalenoteDeleteDTO::Wrapper& dto)
{
    auto result = SalenoteDeleteResultVO::createShared();
    result->successCount = 0;
    result->failureCount = 0;
    result->failedOrderIds = oatpp::List<oatpp::String>::createShared();

    if (!dto || !dto->orderIds) {
        return result;
    }

    for (const auto& id : *dto->orderIds) {
        if (!id) {
            result->failureCount = result->failureCount + 1;
            result->failedOrderIds->push_back(id);
            continue;
        }

        if (id->empty()) {
            result->failureCount = result->failureCount + 1;
            result->failedOrderIds->push_back(id);
            continue;
        }

        try {
            std::string idStr = id->c_str();
            if (sellDAO.deleteById(idStr)) {
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

bool SellService::importData(const PayloadDTO& payload, const SellImportDTO::Wrapper& dto) {
	// TODO: 参数校验（必填项、取值范围、时间格式等）
	SellDAO dao;
	std::string sell_uuid;
	return dao.importData(payload, dto, sell_uuid);
}

SellAuditResultVO::Wrapper
SellService::batchApprove(const SellAuditDTO::Wrapper& dto) {
	auto result = SellAuditResultVO::createShared();
	result->successCount = 0;
	result->failureCount = 0;
	result->failedOrderIds = oatpp::List<oatpp::String>::createShared();

	if (!dto || !dto->orderIds) return result;

	SellDAO dao;
	for (const auto& id : *dto->orderIds) {
		if (!id || id->empty()) {
			result->failureCount = result->failureCount + 1;
			result->failedOrderIds->push_back(id);
			continue;
		}
		try {
			// 已审核则直接算失败（也可算成功，看你业务口径）
			if (dao.isOrderApproved(id)) {
				result->failureCount = result->failureCount + 1;
				result->failedOrderIds->push_back(id);
				continue;
			}
			if (dao.approveById(id)) {
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

SellAuditResultVO::Wrapper
SellService::batchUnapprove(const SellAuditDTO::Wrapper& dto) {
	auto result = SellAuditResultVO::createShared();
	result->successCount = 0;
	result->failureCount = 0;
	result->failedOrderIds = oatpp::List<oatpp::String>::createShared();

	if (!dto || !dto->orderIds) return result;

	SellDAO dao;
	for (const auto& id : *dto->orderIds) {
		if (!id || id->empty()) {
			result->failureCount = result->failureCount + 1;
			result->failedOrderIds->push_back(id);
			continue;
		}
		try {
			// 未审核则无法反审核（业务口径同上）
			if (!dao.isOrderApproved(id)) {
				result->failureCount = result->failureCount + 1;
				result->failedOrderIds->push_back(id);
				continue;
			}
			if (dao.unapproveById(id)) {
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