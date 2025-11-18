#ifndef GOODSDAO_H
#define GOODSDAO_H
#include "BaseDAO.h"
#include "domain/do/GoodsDO.h"

class GoodsDAO : public BaseDAO
{
public:
	//≤È—ØœÍœ∏–≈œ¢
	PtrGoodsDO selectById(std::string id);
};
#endif // !GOODSDAO_H
