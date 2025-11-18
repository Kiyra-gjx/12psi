#ifndef  GOODSSERVICE_H
#define GOODSSERVICE_H
#include "domain/dto/GoodsDTO/GoodsDTO.h"
#include "domain/query/GoodsQuery/GoodsQuery.h"
#include "dao/GoodsDAO/GoodsDAO.h"
#include "domain/do/GoodsDO.h"
class GoodsService {
public:
	// 分页查询所有数据
	GoodsListPageDTO::Wrapper listAll(const GoodsQuery::Wrapper& query);
	// 通过ID查询详细数据
	GoodsDetailDTO::Wrapper getById(std::string id);
	GoodsSpecDTO::Wrapper getSpec(const GoodsQuery::Wrapper& query);
	//商品删除(批量)
	bool removeGoodsData(const oatpp::List<oatpp::String>& ids);
	//商品导入
	std::string importExcelGoods(const vector<vector<std::string>>& data);
	// 保存商品
	std::string saveGoods(const GoodsAddDTO::Wrapper& dto);
	// 修改商品
	bool updateGoods(const GoodsDetailDTO::Wrapper& dto);

};

#endif 
