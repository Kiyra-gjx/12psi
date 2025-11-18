
#ifndef _SELLBILLDAO_H_
#define _SELLBILLDAO_H_

#include "BaseDAO.h"
#include "domain/do/SellbillDO.h"  

/**
 * 销售单核销详情数据访问对象（DAO）
 */
class SellbillDAO : public BaseDAO
{
public:
    /**
     * 根据ID查询销售核销单
     * @param id 销售核销单ID
     * @return 对应的 SellbillDO 对象指针
     */
    PtrSellbillDO selectById(const string& id);


};

#endif