#include "GoodsService.h"
#include "../../Macros.h"
#include <set>
#include <string>
#include "id/UuidFacade.h"

// 分页查询所有数据
GoodsListPageDTO::Wrapper GoodsService::listAll(const GoodsQuery::Wrapper& query) {
	// 构建返回对象
	auto pages = GoodsListPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	GoodsDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<GoodsDO> result = dao.selectWithPage(query);
	// 将DO转换成DTO
	for (GoodsDO& sub : result)
	{
		auto dto = GoodsListDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,name,Name,number,Number,spec,Spec,
			category, Category, brand,Brand, unit, Unit,
			code,Code,data,Data,type,Type);
		pages->addData(dto);
	}
	return pages;
	
}

// 通过ID查询详细数据
GoodsDetailDTO::Wrapper GoodsService::getById(std::string ids) {
	// 查询数据
	GoodsDAO dao;
	auto res = dao.selectById(ids);

	// 没有查询到数据
	if (!res)
		return nullptr;

	// 查询到数据转换成DTO
	auto dto = GoodsDetailDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res, id, Id,name,Name,py,Py,
		number,Number,spec,Spec,category,Category,brand,Brand,unit,Unit
	,buy,Buy,sell,Sell,code,Code,location,Location,stock,Stock,type,Type
	,data,Data,imgs,Imgs,details,Details,units,Units, strategy, Strategy
	,serial,Serial,batch,Batch,validity, Validity,protect,Protect, threshold,
		Threshold,more,More);
	return dto;
}

GoodsSpecDTO::Wrapper GoodsService::getSpec(const GoodsQuery::Wrapper& query) {
	GoodsDAO dao;
	std::list<GoodsDO> result = dao.selectWithPage(query);

	auto dto = GoodsSpecDTO::createShared();

	// 初始化列表
	if (!dto->specs) {
		dto->specs = oatpp::List<GoodsSpecItemDTO::Wrapper>::createShared();
	}

	// 去重 key： id|type|code
	std::set<std::string> seen;
	for (const auto &g : result) {
		std::string sid = g.getId();
		int type = g.getType();
		std::string code = g.getCode();

		std::string key = sid + "|" + std::to_string(type) + "|" + code;
		if (seen.find(key) != seen.end()) continue;
		seen.insert(key);

		auto item = GoodsSpecItemDTO::createShared();
		item->id = oatpp::String(sid);   
		item->type = type;
		item->code = oatpp::String(code);
		dto->specs->push_back(item);
	}

	return dto;
}

//商品删除(批量)
bool GoodsService::removeGoodsData(const oatpp::List<oatpp::String>& ids) {
	//创建数据库操作对象
	GoodsDAO dao;

	//转换std到oat
	std::list<std::string> datas;
	//数据换到datas里去
	for (auto one : *ids.get()) {
		datas.emplace_back(one.getValue({}));
	}
	//删除数据，返回的是操作行数
	int rows = dao.deleteByIds<GoodsDO>(datas);

	if (rows == ids->size()) {
		return true;
	}
	return false;
}




//商品导入
//将文件信息插入数据库goods
std::string GoodsService::importExcelGoods(const vector<vector<std::string>>& data) {
	//获取商品数量
	int size = data.size() - 1;

	int rows = 0;

	int count = 1;

	count = 1;
	//2.创建对象插入数据
	for (auto i : data) {
		if (count != 1) {
			// 使用智能指针创建对象
			auto goodsdo = std::make_shared<GoodsDO>();
			int goodsIndex = 0;
			UuidFacade uf;

			goodsdo->setId(uf.genUuid());
			goodsdo->setName(i[goodsIndex++]);

			goodsdo->setPy(i[goodsIndex++]);
			goodsdo->setNumber(i[goodsIndex++]);

			//商品型号
			goodsdo->setSpec(i[goodsIndex++]);

			goodsdo->setCategory(i[goodsIndex++]);

			//商品品牌
			goodsdo->setBrand(i[goodsIndex++]);

			goodsdo->setUnit(i[goodsIndex++]);

			//商品条码
			goodsdo->setCode(i[goodsIndex++]);

			double buy = std::stod(i[goodsIndex++]);
			goodsdo->setBuy(buy);

			double sell = std::stod(i[goodsIndex++]);
			goodsdo->setSell(sell);

			double stock = std::stod(i[goodsIndex++]);
			goodsdo->setStock(stock);

			int type = std::stoi(i[goodsIndex++]);
			goodsdo->setType(type);

			goodsdo->setMore(i[goodsIndex++]);
			//创建操作对象
			GoodsDAO dao;

			//插入数据
			rows += dao.insert(*goodsdo);
		}
		else {
			count++;
		}
	}

	if (rows != size)
		return "fail";
	return "success";
}

std::string GoodsService::saveGoods(const GoodsAddDTO::Wrapper& dto)
{
	// 组装DO数据
	GoodsDO goods;
	ZO_STAR_DOMAIN_DTO_TO_DO(goods, dto, Name, name, Py, py, Number, number, Spec, spec,
		Category, category, Brand, brand, Unit, unit, Buy, buy, Sell, sell, Code, code,
		Location, location, Stock, stock, Type, type, Data, data, Imgs, imgs, Details, details,
		Units, units, Strategy, strategy, Serial, serial, Batch, batch, Validity, validity,
		Protect, protect, Threshold, threshold, More, more);
	// 生成ID
	UuidFacade uf;
	goods.setId(uf.genUuid());
	// 执行数据添加
	GoodsDAO dao;
	return dao.insert(goods) == 1 ? goods.getId() : "";
}

bool GoodsService::updateGoods(const GoodsDetailDTO::Wrapper& dto)
{
	// 组装DO数据
	GoodsDO goodsDetail;
	ZO_STAR_DOMAIN_DTO_TO_DO(goodsDetail, dto, Name, name, Py, py, Number, number, Spec, spec,
		Category, category, Brand, brand, Unit, unit, Buy, buy, Sell, sell, Code, code,
		Location, location, Stock, stock, Type, type, Data, data, Imgs, imgs, Details, details,
		Units, units, Strategy, strategy, Serial, serial, Batch, batch, Validity, validity,
		Protect, protect, Threshold, threshold, More, more, Id, id);
	// 执行数据添加
	GoodsDAO dao;
	return dao.update(goodsDetail) == 1;
}
