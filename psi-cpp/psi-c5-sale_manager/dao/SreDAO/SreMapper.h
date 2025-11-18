#pragma once
#include "Mapper.h"
#include "domain/do/SreDO.h"
#include "domain/do/SreInfoDO.h"

class SreMapper : public Mapper<SreViewDO> {
public:
	SreViewDO mapper(ResultSet* resultSet) const override {
		SreViewDO data;
		//DO本身的数据
		//属性
		data.setId(resultSet->getString("id"));
		data.setFrame(resultSet->getString("frame"));
		data.setCustomer(resultSet->getString("customer"));
		data.setTime(resultSet->getString("time"));
		data.setNumber(resultSet->getString("number"));
		data.setPeople(resultSet->getString("people"));
		data.setData(resultSet->getString("data"));
		data.setUser(resultSet->getString("user"));

		//费用相关
		data.setTotal(resultSet->getDouble("total"));
		data.setActual(resultSet->getDouble("actual"));
		data.setMoney(resultSet->getDouble("sre_money"));
		data.setCost(resultSet->getDouble("cost"));

		//状态
		data.setExamine(resultSet->getInt("examine"));
		data.setNucleus(resultSet->getInt("nucleus"));
		data.setCse(resultSet->getInt("cse"));
		data.setInvoice(resultSet->getInt("invoice"));
		data.setCheck(resultSet->getInt("check"));

		//联表数据
		data.setWriteOffMoney(resultSet->getDouble("bill_money"));
		return data;
	}

};
//导出简单报表独有的字段映射！
class SreSimpleReportMapper : public Mapper<PtrSreDO> {
public:
	PtrSreDO mapper(ResultSet* resultSet) const override {
		auto sreDO = std::make_shared<SreDO>();
		//导出简单报表的字段映射
		sreDO->setFrame(resultSet->getString("frame"));
		sreDO->setCustomer(resultSet->getString("customer"));
		sreDO->setTime(resultSet->getString("time"));
		sreDO->setNumber(resultSet->getString("number"));
		sreDO->setTotal(resultSet->getDouble("total")); // 类型：double
		sreDO->setActual(resultSet->getDouble("actual"));
		sreDO->setMoney(resultSet->getDouble("money"));
		sreDO->setCost(resultSet->getDouble("cost"));
		sreDO->setPeople(resultSet->getString("people"));
		sreDO->setExamine(static_cast<char>(resultSet->getInt("examine"))); // tinyint→char
		sreDO->setNucleus(static_cast<char>(resultSet->getInt("nucleus")));
		sreDO->setCse(static_cast<char>(resultSet->getInt("cse")));
		sreDO->setInvoice(static_cast<char>(resultSet->getInt("invoice")));
		sreDO->setCheck(static_cast<char>(resultSet->getInt("check")));
		sreDO->setUser(resultSet->getString("user"));
		sreDO->setData(resultSet->getString("data"));
		return sreDO;
	}
};

//导出详细报表独有的字段映射！
class SreDetailReportMapper : public Mapper<PtrSreDO> {
public:
	PtrSreDO mapper(ResultSet* resultSet) const override {
		auto sreDO = std::make_shared<SreDO>();
		///导出详细报表的字段映射
		sreDO->setId(resultSet->getString("id"));             // 追加：详细报表独有
		sreDO->setCustomer(resultSet->getString("customer")); // 主表字段
		sreDO->setTime(resultSet->getString("time"));         // 主表字段
		sreDO->setNumber(resultSet->getString("number"));     // 主表字段
		sreDO->setTotal(resultSet->getDouble("total"));       // 主表字段
		sreDO->setActual(resultSet->getDouble("actual"));     // 主表字段
		sreDO->setCost(resultSet->getDouble("cost"));         // 主表字段
		sreDO->setPeople(resultSet->getString("people"));     // 主表字段
		sreDO->setExamine(static_cast<char>(resultSet->getInt("examine"))); // 主表字段
		sreDO->setNucleus(static_cast<char>(resultSet->getInt("nucleus"))); // 主表字段
		sreDO->setAccount(resultSet->getString("account"));   // 追加：详细报表独有
		sreDO->setInvoice(static_cast<char>(resultSet->getInt("invoice"))); // 主表字段
		sreDO->setLogistics(resultSet->getString("logistics")); // 追加：详细报表独有
		sreDO->setData(resultSet->getString("data"));         // 主表字段
		return sreDO;
	}
};
// 明细表SreInfoMapper
class SreInfoMapper : public Mapper<PtrSreInfoDO> {
public:
	PtrSreInfoDO mapper(ResultSet* resultSet) const override {
		auto infoDO = std::make_shared<SreInfoDO>();
		infoDO->setGoods(resultSet->getString("goods"));
		infoDO->setAttr(resultSet->getString("attr"));
		infoDO->setUnit(resultSet->getString("unit"));
		infoDO->setWarehouse(resultSet->getString("warehouse"));
		infoDO->setPrice(resultSet->getDouble("price"));
		infoDO->setNums(resultSet->getDouble("nums"));
		infoDO->setDiscount(resultSet->getDouble("discount"));
		infoDO->setDsc(resultSet->getDouble("dsc"));
		infoDO->setTotal(resultSet->getDouble("total"));
		infoDO->setTax(resultSet->getDouble("tax"));
		infoDO->setTat(resultSet->getDouble("tat"));
		infoDO->setTpt(resultSet->getDouble("tpt"));
		infoDO->setData(resultSet->getString("data"));
		// 补充缺失字段映射
		infoDO->setId(resultSet->getString("id"));
		infoDO->setPid(resultSet->getString("pid"));
		infoDO->setSource(resultSet->getString("source"));
		infoDO->setBatch(resultSet->getString("batch"));
		infoDO->setMfd(resultSet->getString("mfd"));
		infoDO->setSerial(resultSet->getString("serial"));
		infoDO->setGoodsName(resultSet->getString("goodsName"));
		infoDO->setSpec(resultSet->getString("spec"));
		return infoDO;
	}

};

