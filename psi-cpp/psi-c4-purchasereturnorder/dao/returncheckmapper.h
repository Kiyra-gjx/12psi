#ifndef _RETURNCHECKMAPPER_H_
#define _RETURNCHECKMAPPER_H_

#include "Mapper.h"
#include "../domain/do/getreturnlistDO.h"

/**
 * 采购退货单核对/反核对字段匹配映射
 */
class BrecheckMapper : public Mapper<BreDO>
{
public:
	BreDO mapper(ResultSet* resultSet) const override
	{
		BreDO DATA;
		DATA.setId(resultSet->getString("id"));
		DATA.setSource(resultSet->getString("source"));
		DATA.setFrame(resultSet->getString("frame"));
		DATA.setSupplier(resultSet->getString("supplier"));
		DATA.setTime(resultSet->getString("time"));
		DATA.setNumber(resultSet->getString("number"));
		DATA.setTotal(resultSet->getDouble("total"));
		DATA.setActual(resultSet->getDouble("actual"));
		DATA.setMoney(resultSet->getDouble("money"));
		DATA.setCost(resultSet->getDouble("cost"));
		DATA.setAccount(resultSet->getString("account"));
		DATA.setPeople(resultSet->getString("people"));
		DATA.setLogistics(resultSet->getString("logistics"));
		DATA.setFile(resultSet->getString("file"));
		DATA.setData(resultSet->getString("data"));
		DATA.setMore(resultSet->getString("more"));
		DATA.setExamine(resultSet->getInt("examine"));
		DATA.setNucleus(resultSet->getInt("nucleus"));
		DATA.setCse(resultSet->getInt("cse"));
		DATA.setInvoice(resultSet->getInt("invoice"));
		DATA.setCheck(resultSet->getInt("check"));
		DATA.setUser(resultSet->getString("user"));
		return DATA;
	}
};
#endif // _RETURNCHECKMAPPER_H_