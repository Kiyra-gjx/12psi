#ifndef _RETURNORDERCHECKMAPPER_H_
#define _RETURNORDERCHECKMAPPER_H_

#include "Mapper.h"
#include "../domain/do/ReturnorderInfoDO.h"

/**
 * ²É¹ºÍË»õµ¥ÏêÇé×Ö¶ÎÆ¥ÅäÓ³Éä
 */
class BreMapper : public Mapper<BreInfoDO>
{
public:
	BreInfoDO mapper(ResultSet* resultSet) const override
	{
		BreInfoDO DATA;
		DATA.setId(resultSet->getString("id"));
		DATA.setPid(resultSet->getString("pid"));
		DATA.setSource(resultSet->getString("source"));
		DATA.setGoods(resultSet->getString("goods"));
		DATA.setAttr(resultSet->getString("attr"));
		DATA.setUnit(resultSet->getString("unit"));
		DATA.setWarehouse(resultSet->getString("warehouse"));
		DATA.setBatch(resultSet->getString("batch"));
		DATA.setMfd(resultSet->getString("mfd"));
		DATA.setPrice(resultSet->getDouble("price"));
		DATA.setNums(resultSet->getDouble("nums"));
		DATA.setSerial(resultSet->getString("serial"));
		DATA.setDiscount(resultSet->getDouble("discount"));
		DATA.setDsc(resultSet->getDouble("dsc"));
		DATA.setTotal(resultSet->getDouble("total"));
		DATA.setTax(resultSet->getDouble("tax"));
		DATA.setTat(resultSet->getDouble("tat"));
		DATA.setTpt(resultSet->getDouble("tpt"));
		DATA.setData(resultSet->getString("data"));
		return DATA;
	}
};
#endif // _RETURNCHECKMAPPER_H_