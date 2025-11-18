#pragma once
#ifndef _BARCODE_DAO_
#define _BARCODE_DAO_
#include "BaseDAO.h"
#include "../../domain/do/barcode/BarcodeDO.h"
#include "BarcodeMapper.h"
#include "../../domain/query/barcode/BarcodeQuery.h"

class BarcodeDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const BarcodeClassPageQuery::Wrapper& query, SqlParams& params);
public:
	uint64_t count(const BarcodeClassPageQuery::Wrapper& query);
	std::list<BarcodeDO> selectWithClassAndPage(const BarcodeClassPageQuery::Wrapper& query);
	PtrBarcodeDO selectById(const string& id);
};
#endif 
