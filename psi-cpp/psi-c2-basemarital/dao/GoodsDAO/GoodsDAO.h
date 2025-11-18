#ifndef GOODSDAO_H
#define GOODSDAO_H
#include "BaseDAO.h"
#include "domain/do/GoodsDO.h"
#include "domain/query/GoodsQuery/GoodsQuery.h"

class GoodsDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const GoodsQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const GoodsQuery::Wrapper& query);
	// 分页查询数据
	std::list<GoodsDO> selectWithPage(const GoodsQuery::Wrapper& query);
	//查询详细信息
	PtrGoodsDO selectById(std::string id);
	//查询商品选择列表
	

};
#endif // !GOODSDAO_H
