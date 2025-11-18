#ifndef _SOR_MAPPER_H_
#define _SOR_MAPPER_H_

#include "Mapper.h"
#include "domain/do/SorDO.h"
#include "domain/do/SorInfoDO.h"

/*
实现mapper的映射，将resultSet映射为一个智能指针的对象SorDO
*/
class SorMapper : public Mapper<PtrSorDO> {
public:
	PtrSorDO mapper(ResultSet* resultSet) const override {
		PtrSorDO sorDO = std::make_shared<SorDO>();
		sorDO->setId(resultSet->getString("id"));
		sorDO->setFrame(resultSet->getString("frame"));
		sorDO->setCustomer(resultSet->getString("customer"));
		sorDO->setTime(resultSet->getString("time"));
		sorDO->setNumber(resultSet->getString("number"));
		sorDO->setTotal(resultSet->getDouble("total"));
		sorDO->setActual(resultSet->getDouble("actual"));
		sorDO->setPeople(resultSet->getString("people"));
		sorDO->setArrival(resultSet->getString("arrival"));
		sorDO->setLogistics(resultSet->getString("logistics"));
		sorDO->setData(resultSet->getString("data"));
		sorDO->setMore(resultSet->getString("more"));
		sorDO->setExamine(resultSet->getInt("examine"));
		sorDO->setState(resultSet->getInt("state"));
		sorDO->setUser(resultSet->getString("user"));
        sorDO->setFile(resultSet->getString("file"));
		//附件
		if (sorDO->getFile() != "") {
			PtrAnnexDO fd = std::make_shared<AnnexDO>();
			fd->setId(sorDO->getFile());
			fd->setName(resultSet->getString("name"));
			fd->setSavePath(resultSet->getString("save_path"));
			sorDO->setAnnex(fd);
		}
		return sorDO;
	}
};

class SorSimpleReportMapper : public Mapper<PtrSorDO> {
public:
	PtrSorDO mapper(ResultSet* resultSet) const override {
		auto sorDO = std::make_shared<SorDO>();
		sorDO->setFrame(resultSet->getString("frame")); // 所属组织
		sorDO->setCustomer(resultSet->getString("customer")); // 客户
		sorDO->setTime(resultSet->getString("time")); // 单据时间
		sorDO->setNumber(resultSet->getString("number")); // 单据编号
		sorDO->setTotal(resultSet->getDouble("total")); // 单据金额
		sorDO->setActual(resultSet->getDouble("actual")); // 实际金额
		sorDO->setArrival(resultSet->getString("arrival")); // 到货日期
		sorDO->setPeople(resultSet->getString("people")); // 关联人员
		sorDO->setExamine(resultSet->getInt("examine")); // 审核状态
		sorDO->setState(resultSet->getInt("state")); // 出库状态
		sorDO->setUser(resultSet->getString("user")); // 制单人
		sorDO->setData(resultSet->getString("data")); // 备注信息
		return sorDO;
	}
};


class SorSimpleMapper : public Mapper<PtrSorDO> {
public:
	PtrSorDO mapper(ResultSet* resultSet) const override {
		cout << endl << "mapper" << endl;
		PtrSorDO sorDO = std::make_shared<SorDO>();
		sorDO->setId(resultSet->getString("id"));
		sorDO->setFrame(resultSet->getString("frame"));
		sorDO->setCustomer(resultSet->getString("customer"));
		sorDO->setTime(resultSet->getString("time"));
		sorDO->setNumber(resultSet->getString("number"));
		sorDO->setTotal(resultSet->getDouble("total"));
		sorDO->setActual(resultSet->getDouble("actual"));
		sorDO->setArrival(resultSet->getString("arrival"));
		sorDO->setPeople(resultSet->getString("people"));
		sorDO->setExamine(resultSet->getInt("examine"));
		sorDO->setState(resultSet->getInt("state"));
		sorDO->setUser(resultSet->getString("user"));
		sorDO->setData(resultSet->getString("data"));
		cout << "mapper" << endl;
		return sorDO;
	}
};

class SorDetailReportMapper : public Mapper<PtrSorDO> {
public:
		PtrSorDO mapper(ResultSet* resultSet) const override {
			auto sorDO = std::make_shared<SorDO>();
			sorDO->setId(resultSet->getString("id"));
			sorDO->setCustomer(resultSet->getString("customer"));
			sorDO->setTime(resultSet->getString("time"));
			sorDO->setNumber(resultSet->getString("number"));
			sorDO->setTotal(resultSet->getDouble("total"));
			sorDO->setActual(resultSet->getDouble("actual"));
			sorDO->setPeople(resultSet->getString("people"));
			sorDO->setArrival(resultSet->getString("arrival"));
			sorDO->setLogistics(resultSet->getString("logistics"));
			sorDO->setData(resultSet->getString("data"));
			return sorDO;
		}
};

class SorInfoDAOMapper : public Mapper<PtrSorInfoDO> {
public:
	PtrSorInfoDO mapper(ResultSet* resultSet) const override {
		auto infoDO = std::make_shared<SorInfoDO>();
		infoDO->setGoodsName(resultSet->getString("goodsName"));
		infoDO->setSpec(resultSet->getString("spec"));
		infoDO->setAttr(resultSet->getString("attr"));
		infoDO->setUnit(resultSet->getString("unit"));
		infoDO->setWarehouse(resultSet->getString("warehouse"));
		infoDO->setPrice(resultSet->getDouble("price"));
		infoDO->setNums(resultSet->getInt("nums"));
		infoDO->setHandle(resultSet->getDouble("handle"));
		infoDO->setDiscount(resultSet->getDouble("discount"));
		infoDO->setDsc(resultSet->getDouble("dsc"));
		infoDO->setTotal(resultSet->getDouble("total"));
		infoDO->setData(resultSet->getString("data"));
		return infoDO;
	}
};
#endif