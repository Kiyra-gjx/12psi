#include "GoodsDAO.h"
#include "GoodsMapper.h"

//²éÑ¯ÏêÏ¸ÐÅÏ¢
PtrGoodsDO GoodsDAO::selectById(std::string id) {
	string sql = "SELECT * FROM goods WHERE `id`=?";
	return sqlSession->executeQueryOne<PtrGoodsDO>(sql, PtrGoodsMapper(), "%s", id);
}