#ifndef _PURCHASELIST_DAO_
#define _PURCHASELIST_DAO_
#include "BaseDAO.h"
#include "../domain/do/PurchaseDingDanDO.h"
#include "../domain/query/PurchaseListQuery.h"

/**
 * 示例表数据库操作实现
 */
class PurchaseListDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const PurchaseListQuery::Wrapper& query, SqlParams& params);
public:
	// 获取数据条数
	uint64_t count(const PurchaseListQuery::Wrapper& query);
	// 分页查询数据
	std::list<PurchaseDingDanDO> selectWithPage(const PurchaseListQuery::Wrapper& query);
};
#endif // !_PURCHASELIST_DAO_
