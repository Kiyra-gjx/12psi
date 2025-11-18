#ifndef _PURCHASEDETAIL_DAO_
#define _PURCHASEDETAIL_DAO_
#include "BaseDAO.h"
#include "../domain/do/PurchaseDetailViewDO.h" 
#include "../domain/query/PurchaseDetailQuery.h"

class PurchaseDetailDAO : public BaseDAO
{
private:
    // 构建查询条件
    inline std::string queryConditionBuilder(const PurchaseDetailQuery::Wrapper& query, SqlParams& params);

public:
    // 获取数据条数
    uint64_t count(const PurchaseDetailQuery::Wrapper& query);
    // 分页查询
    std::list<PurchaseDetailViewDO> selectPurchaseDetail(const PurchaseDetailQuery::Wrapper& query);

};  
#endif // !_PURCHASEDETAIL_DAO_