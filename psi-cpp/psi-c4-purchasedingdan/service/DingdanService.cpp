#include <stdafx.h>
#include "DingdanService.h"
#include "id/UuidFacade.h"
#include "../dao/BorDAO.h"
#include "domain/dto/DingdanDTO.h"
#include "SimpleDateTimeFormat.h"
#include "Mapper.h"

using oatpp::List;
using oatpp::String;

std::string DingdanService::getDfsServerAddrssUrl()
{
	/** 定义一个Nacos客户端对象，用于获取配置 */
	NacosClient _ns(ServerInfo::getInstance().getNacosAddr(), ServerInfo::getInstance().getNacosNs());
#ifdef LINUX
	/** 读取配置数据节点 */
	auto _thirdServerConfig = _ns.getConfig("third-services.yaml");
#else
	/** 读取配置数据节点 */
	auto _thirdServerConfig = _ns.getConfig("./conf/third-services.yaml");
#endif
	return "http://" + YamlHelper().getString(&_thirdServerConfig, "fastdfs.nginx-servers") + "/";
}

bool DingdanService::modifyDingdanMultiTable(const DingdanDetailDTO::Wrapper& dto)
{
	// 开始事务
	BorDAO dao;
	dao.getSqlSession()->beginTransaction();

	try {
		// 1. 将DTO转换为多个DO对象
		PtrBorDO borDO;
		PtrBorInfoDO borInfoDO;
		PtrGoodsDO goodsDO;

		if (!convertDtoToDos(dto, borDO, borInfoDO, goodsDO)) {
			dao.getSqlSession()->rollbackTransaction();
			return false;
		}

		// 2. 更新各个表
		bool borResult = true;
		bool borInfoResult = true;
		bool goodsResult = true;

		// 更新bor表（仅当有相关字段时）
		if (borDO) {
			BorDAO borDao;
			borResult = borDao.updateBor(borDO);
		}

		// 更新bor_info表
		if (borInfoDO) {
			BorInfoDAO borInfoDao;
			borInfoResult = borInfoDao.updateBorInfo(borInfoDO);
		}

		// 更新goods表（仅当有商品信息时）
		if (goodsDO) {
			GoodsDAO goodsDao;
			goodsResult = goodsDao.updateGoods(goodsDO);
		}

		// 3. 检查更新结果
		if (!borResult || !borInfoResult || !goodsResult) {
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
		log.setInfo("修改采购订单详情，ID: " + dto->id.getValue("") +
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

bool DingdanService::convertDtoToDos(const DingdanDetailDTO::Wrapper& dto,
	PtrBorDO& borDO,
	PtrBorInfoDO& borInfoDO,
	PtrGoodsDO& goodsDO)
{
	if (!dto || !dto->id) {
		return false;
	}

	std::string orderId = dto->id->c_str();

	// 1. 创建BorDO对象（订单主表）
	borDO = std::make_shared<BorDO>();
	borDO->setId(orderId);

	// 仅当DTO中有相关字段时才设置
	if (!dto->supplier.getValue("").empty()) {
		borDO->setSupplier(dto->supplier->c_str());
	}
	if (!dto->time.getValue("").empty()) {
		borDO->setTime(dto->time->c_str());
	}
	if (!dto->number.getValue("").empty()) {
		borDO->setNumber(dto->number->c_str());
	}
	if (!dto->arrivalDate.getValue("").empty()) {
		borDO->setArrival(dto->arrivalDate->c_str());
	}
	if (!dto->logisticsInfo.getValue("").empty()) {
		borDO->setLogistics(dto->logisticsInfo->c_str());
	}
	if (!dto->relatedPerson.getValue("").empty()) {
		borDO->setPeople(dto->relatedPerson->c_str());
	}
	if (!dto->file.getValue("").empty()) {
		borDO->setFile(dto->file->c_str());
	}

	// 2. 创建BorInfoDO对象（订单详情表）
	borInfoDO = std::make_shared<BorInfoDO>();
	borInfoDO->setPid(orderId);

	// 首先根据订单ID查找对应的商品ID
	BorInfoDAO tempBorInfoDao;
	auto existingBorInfo = tempBorInfoDao.selectByPid(orderId);
	if (existingBorInfo) {
		borInfoDO->setGoods(existingBorInfo->getGoods());
	}

	// 设置详情字段
	if (!dto->attr.getValue("").empty()) {
		borInfoDO->setAttr(dto->attr->c_str());
	}
	if (!dto->unit.getValue("").empty()) {
		borInfoDO->setUnit(dto->unit->c_str());
	}
	if (!dto->warehouse.getValue("").empty()) {
		borInfoDO->setWarehouse(dto->warehouse->c_str());
	}
	if (dto->price > 0) {
		borInfoDO->setPrice(dto->price);
	}
	if (dto->qty > 0) {
		borInfoDO->setNums(dto->qty);
	}
	if (dto->docAmount > 0) {
		borInfoDO->setTotal(dto->docAmount);
	}
	if (dto->actualAmount > 0) {
		borInfoDO->setTat(dto->actualAmount);
	}
	if (!dto->remark.getValue("").empty()) {
		borInfoDO->setData(dto->remark->c_str());
	}
	if (dto->inQty > 0) {
		borInfoDO->setHandle(dto->inQty);
	}

	// 3. 创建GoodsDO对象（商品表）
	if (!dto->goodsName.getValue("").empty() ||
		!dto->goodsNo.getValue("").empty() ||
		!dto->specModel.getValue("").empty()) {

		goodsDO = std::make_shared<GoodsDO>();

		// 获取商品ID
		if (borInfoDO && !borInfoDO->getGoods().empty()) {
			goodsDO->setId(borInfoDO->getGoods());
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

StringJsonVO::Wrapper DingdanService::examineDingdan(const DingdanExamineDTO::Wrapper& dto)
{
	// 定义返回对象
	auto jvo = StringJsonVO::createShared();

	// 执行批量审核/反审核
	BorDAO dao;
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
			std::string checkSql = "SELECT state FROM bor WHERE id = ?";
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
