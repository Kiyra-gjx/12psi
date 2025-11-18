#pragma once
#ifndef _DINGDANMAPPER_H_
#define _DINGDANMAPPER_H_

#include "Mapper.h"
#include "domain/do/DingdanDO.h"

/**
 * Bor±íÊý¾ÝÓ³ÉäÆ÷
 */
class BorMapper : public Mapper<PtrBorDO> {
public:
	PtrBorDO mapper(ResultSet* resultSet) const override
	{

		PtrBorDO dingdanDO = std::make_shared<BorDO>();
		dingdanDO->setId(resultSet->getString("id"));
		dingdanDO->setSource(resultSet->getString("source"));
		dingdanDO->setFrame(resultSet->getString("frame"));
		dingdanDO->setSupplier(resultSet->getString("supplier"));
		dingdanDO->setTime(resultSet->getString("time"));
		dingdanDO->setNumber(resultSet->getString("number"));
		dingdanDO->setTotal(resultSet->getDouble("total"));
		dingdanDO->setActual(resultSet->getDouble("actual"));
		dingdanDO->setPeople(resultSet->getString("people"));
		dingdanDO->setArrival(resultSet->getString("arrival"));
		dingdanDO->setLogistics(resultSet->getString("logistics"));
		dingdanDO->setFile(resultSet->getString("file"));
		dingdanDO->setData(resultSet->getString("data"));
		dingdanDO->setMore(resultSet->getString("more"));
		dingdanDO->setExamine(resultSet->getInt("examine"));
		dingdanDO->setState(resultSet->getInt("state"));
		dingdanDO->setUser(resultSet->getString("user"));


		if (dingdanDO->getFile() != "")
		{
			PtrFileDO fd = std::make_shared<FileDO>();
			fd->setId(dingdanDO->getFile());
			fd->setName(resultSet->getString("name"));
			fd->setSavePath(resultSet->getString("save_path"));
			dingdanDO->setFileUrl(fd);
		}

		return dingdanDO;

	}
};






#endif // !_DINGDANMAPPER_H_