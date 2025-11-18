#include "stdafx.h"
#include "OrderService.h"
#include "id/UuidFacade.h"
#include "domain/dto/OrderDTO.h"
#include "domain/dto/OrderExamineDTO.h"
#include "SimpleDateTimeFormat.h"
#include "dao/buy/BuyDAO.h"
#include "dao/buy_info/BuyInfoDAO.h"
#include "dao/goods/GoodsDAO.h"
#include "domain/do/OrderDO.h"
#include "Mapper.h"

using oatpp::List;
using oatpp::String;



// 修改采购订单主数据
bool OrderService::modifyOrder(const OrderDetailDTO::Wrapper& dto)
{
	// 开始事务
	BuyDAO dao;
	dao.getSqlSession()->beginTransaction();

	try {
		// 1. 将DTO转换为多个DO对象
		PtrBuyDO BorDO;
		PtrBuyInfoDO BorInfoDO;
		PtrGoodsDO goodsDO;

		if (!convertDtoToDos(dto, BorDO, BorInfoDO, goodsDO)) {
			dao.getSqlSession()->rollbackTransaction();
			return false;
		}

		// 2. 更新各个表
		bool buyResult = true;
		bool buyInfoResult = true;
		bool goodsResult = true;

		// 更新bor表（仅当有相关字段时）
		if (BorDO) {
			BuyDAO BuyDAO;
			buyResult = BuyDAO.updateBuy(BorDO);
		}

		// 更新bor_info表
		if (BorInfoDO) {
			BuyInfoDAO BuyInfoDAO;
			buyInfoResult = BuyInfoDAO.updateBuyInfo(BorInfoDO);
		}

		// 更新goods表（仅当有商品信息时）
		if (goodsDO) {
			GoodsDAO goodsDao;
			goodsResult = goodsDao.updateGoods(goodsDO);
		}

		// 3. 检查更新结果
		if (!buyResult || !buyInfoResult || !goodsResult) {
			dao.getSqlSession()->rollbackTransaction();
			return false;
		}

		// 4. 提交事务
		dao.getSqlSession()->commitTransaction();

		// 5. 记录操作日志
		LogDO log;
		UuidFacade uuidGen;
		log.setId(uuidGen.genUuid());
		log.setTime(SimpleDateTimeFormat::format());
		log.setUser(dto->getPayload()->getUsername());
		log.setInfo("修改采购单详情，ID: " + dto->id.getValue("") +
			", 商品: " + dto->goodsName.getValue("") +
			", 数量: " + std::to_string(dto->qty.getValue(0)) +
			", 单价: " + std::to_string(dto->price.getValue(0)));

		// 插入日志记录到log表
		std::string logSql = "INSERT INTO log (id, time, user, info) VALUES (?, ?, ?, ?)";
		SqlParams logParams;
		SQLPARAMS_PUSH(logParams, "s", std::string, log.getId());
		SQLPARAMS_PUSH(logParams, "s", std::string, log.getTime());
		SQLPARAMS_PUSH(logParams, "s", std::string, log.getUser());
		SQLPARAMS_PUSH(logParams, "s", std::string, log.getInfo());

		// 执行日志插入
		dao.getSqlSession()->executeUpdate(logSql, logParams);

		return true;

	}
	catch (const std::exception& e) {
		// 发生异常，回滚事务
		dao.getSqlSession()->rollbackTransaction();
		return false;
	}
}

// 辅助方法：将DTO转换为多个DO对象
bool OrderService::convertDtoToDos(const OrderDetailDTO::Wrapper& dto,PtrBuyDO& BorDO,PtrBuyInfoDO& BorInfoDO,PtrGoodsDO& goodsDO)
{
	if (!dto || !dto->id) {
		return false;
	}

	std::string orderId = dto->id->c_str();

	// 1. 创建BorDO对象（订单主表）
	BorDO = std::make_shared<BuyDO>();
	BorDO->setId(orderId);

	// 仅当DTO中有相关字段时才设置
	if (!dto->supplier.getValue("").empty()) {
		BorDO->setSupplier(dto->supplier->c_str());
	}
	if (!dto->time.getValue("").empty()) {
		BorDO->setTime(dto->time->c_str());
	}
	if (!dto->number.getValue("").empty()) {
		BorDO->setNumber(dto->number->c_str());
	}

	if (!dto->logisticsInfo.getValue("").empty()) {
		BorDO->setLogistics(dto->logisticsInfo->c_str());
	}
	if (!dto->relatedPerson.getValue("").empty()) {
		BorDO->setPeople(dto->relatedPerson->c_str());
	}
	if (!dto->file.getValue("").empty()) {
		BorDO->setFile(dto->file->c_str());
	}

	// 2. 创建BorInfoDO对象（订单详情表）
	BorInfoDO = std::make_shared<BuyInfoDO>();
	BorInfoDO->setPid(orderId);

	// 首先根据订单ID查找对应的商品ID
	BuyInfoDAO tempBuyInfoDAO;
	auto existingBorInfo = tempBuyInfoDAO.selectByPid(orderId);
	if (existingBorInfo) {
		BorInfoDO->setGoods(existingBorInfo->getGoods());
	}

	// 设置详情字段
	if (!dto->attr.getValue("").empty()) {
		BorInfoDO->setAttr(dto->attr->c_str());
	}
	if (!dto->unit.getValue("").empty()) {
		BorInfoDO->setUnit(dto->unit->c_str());
	}
	if (!dto->warehouse.getValue("").empty()) {
		BorInfoDO->setWarehouse(dto->warehouse->c_str());
	}
	if (dto->price > 0) {
		BorInfoDO->setPrice(dto->price);
	}
	if (dto->qty > 0) {
		BorInfoDO->setNums(dto->qty);
	}
	if (dto->docAmount > 0) {
		BorInfoDO->setTotal(dto->docAmount);
	}
	if (dto->actualAmount > 0) {
		BorInfoDO->setTat(dto->actualAmount);
	}
	if (!dto->remark.getValue("").empty()) {
		BorInfoDO->setData(dto->remark->c_str());
	}


	// 3. 创建GoodsDO对象（商品表）
	if (!dto->goodsName.getValue("").empty() ||
		!dto->goodsNo.getValue("").empty() ||
		!dto->specModel.getValue("").empty()) {

		goodsDO = std::make_shared<GoodsDO>();

		// 获取商品ID
		if (BorInfoDO && !BorInfoDO->getGoods().empty()) {
			goodsDO->setId(BorInfoDO->getGoods());
		}

		// 设置商品字段
		if (!dto->goodsName.getValue("").empty()) {
			goodsDO->setName(dto->goodsName->c_str());
		}
		if (!dto->goodsNo.getValue("").empty()) {
			goodsDO->setNumber(dto->goodsNo->c_str());
		}
		if (!dto->specModel.getValue("").empty()) {
			goodsDO->setSpec(dto->specModel->c_str());
		}
	}

	return true;
}
//审核和反审核订单
StringJsonVO::Wrapper OrderService::examineDingdan(const OrderExamineDTO::Wrapper& dto)
{
	// 定义返回对象
	auto jvo = StringJsonVO::createShared();

	// 执行批量审核/反审核
	BuyDAO dao;
	bool success;
	std::string actionDesc;
	std::string successMsg;
	std::string failMsg;

	// 根据status值判断操作类型
	if (dto->status == 1) {
		// status为1时，执行审核（将审核状态设为1-已审核）
		success = dao.batchUpdateExamineStatus(dto->ids, 1);
		actionDesc = ZH_WORDS_GETTER("dingdan.examine.detail.actionDesc1");
		successMsg = ZH_WORDS_GETTER("dingdan.examine.detail.successMsg1");
		failMsg = ZH_WORDS_GETTER("dingdan.examine.detail.failMsg1");
	}
	else if (dto->status == 0 || !dto->status) {
		// status为0或不传时，执行反审核（将审核状态设为0-未审核）

		// 直接使用DTO中的ids，不需要额外的vector
		// 查询每个订单的入库状态，分类存储
		auto canUnExamineList = List<String>::createShared();
		auto cannotUnExamineList = List<String>::createShared();

		// 创建mapper来获取state字段
		class StateMapper : public Mapper<int> {
		public:
			int mapper(ResultSet* rs) const override {
				return rs->getInt("state");
			}
		};
		StateMapper stateMapper;

		for (const auto& id : *dto->ids) {
			std::string checkSql = "SELECT state FROM buy WHERE id = ?";
			SqlParams checkParams;
			SQLPARAMS_PUSH(checkParams, "s", std::string, id);

			// 使用mapper对象来获取state字段
			auto result = dao.getSqlSession()->executeQueryOne<int>(checkSql, stateMapper, checkParams);

			// state=2或3表示已入库或关闭，不能反审核
			if (result == 2 || result == 3) {
				cannotUnExamineList->push_back(String(id));
			}
			else {
				canUnExamineList->push_back(String(id));
			}
		}

		// 如果有已入库或关闭的订单，返回错误
		if (!cannotUnExamineList->empty()) {
			std::string errorMsg = ZH_WORDS_GETTER("dingdan.examine.errmsg1");
			for (v_int32 i = 0; i < cannotUnExamineList->size(); ++i) {
				errorMsg += (*cannotUnExamineList[i]).c_str();
				if (i < cannotUnExamineList->size() - 1) {
					errorMsg += ",";
				}
			}
			auto resultMsg = String(errorMsg);
			jvo->init(resultMsg, RS_FORBIDDEN);
			return jvo;
		}

		// 执行反审核
		if (!canUnExamineList->empty()) {

			success = dao.batchUpdateExamineStatus(canUnExamineList, 0);
			actionDesc = ZH_WORDS_GETTER("dingdan.examine.detail.actionDesc2");;
			successMsg = ZH_WORDS_GETTER("dingdan.examine.detail.successMsg2");
			failMsg = ZH_WORDS_GETTER("dingdan.examine.detail.failMsg2");
		}
		else {
			// 没有可反审核的订单
			auto errorMsg = String(ZH_WORDS_GETTER("dingdan.examine.detail.nothing"));
			jvo->init(errorMsg, RS_FORBIDDEN);
			return jvo;
		}
	}
	else {
		// 其他状态值无效
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	if (success) {
		// 记录操作日志
		for (const auto& id : *dto->ids) {
			LogDO log;
			UuidFacade uuidGen;
			log.setId(uuidGen.genUuid());
			log.setTime(SimpleDateTimeFormat::format());
			log.setUser(dto->getPayload()->getUsername());
			log.setInfo("订单" + actionDesc + "，订单ID: " + id);

			// 插入日志记录到log表
			std::string logSql = "INSERT INTO log (id, time, user, info) VALUES (?, ?, ?, ?)";
			SqlParams logParams;
			SQLPARAMS_PUSH(logParams, "s", std::string, log.getId());
			SQLPARAMS_PUSH(logParams, "s", std::string, log.getTime());
			SQLPARAMS_PUSH(logParams, "s", std::string, log.getUser());
			SQLPARAMS_PUSH(logParams, "s", std::string, log.getInfo());

			dao.getSqlSession()->executeUpdate(logSql, logParams);
		}

		jvo->success(successMsg);
	}
	else {
		jvo->fail(failMsg);
	}

	return jvo;
}