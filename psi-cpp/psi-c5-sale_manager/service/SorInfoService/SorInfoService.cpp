#include "stdafx.h"
#include "dao/SellInfoDAO/SellInfoDAO.h"
#include "SorInfoService.h"
#include "dao/SorInfoDAO/SorInfoDAO.h"
#include "dao/SorDAO/SorDAO.h"
#include "service/SorService/SorService.h"
#include "dao/GoodsDAO/GoodsDAO.h"
#include "../../Macros.h"
#include "NacosClient.h"

//获取文件服务器地址
std::string SorInfoService::getDfsServerAddrssUrl() {
	/** 定义一个Nacos客户端对象，用于获取配置 */
	NacosClient _ns(ServerInfo::getInstance().getNacosAddr(), ServerInfo::getInstance().getNacosNs());
#ifdef LINUX
	/** 读取配置数据节点 */
	auto _thirdServerConfig = _ns.getConfig("third-services.yaml");
#else
	/** 读取配置数据节点 */
	auto _thirdServerConfig = _ns.getConfig("./conf/third-services.yaml");
#endif
	return "http://" + YamlHelper().getString(&_thirdServerConfig, "fastdfs.nginx-servers") + "/";
}

//获取销售订单的详情
SaleOrderDetailDTO::Wrapper SorInfoService::getSaleOrderDetail(const oatpp::String& id) {
	//详情内有多个goods，一个详情对应一个goods
	SorDAO sd;
	
	auto tmp = sd.selectById(id.getValue(""));
	if (!tmp) {
		return nullptr;
	}
	//dto的结构是有一个销售订单的属性，还有一堆销售订单详情的属性
	auto dto = SaleOrderDetailDTO::createShared();
	//在这里赋予DTO中普通字段
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, tmp, frame, Frame, customer, Customer, time, Time, number,
		Number, total, Total, actual, Actual, arrival, Arrival, people, People, examine, Examine, state,
		State, user, User, data, Data, id, Id);
	/*if (data->getAnnex()) {
		dto->fileUrl = getDfsServerAddrssUrl() + data->getAnnex()->getSavePath();
	}*/

	SorInfoDAO sid;
	//这是一个查询的原始结果，是一个列表，里面装的是info的列表
	auto sorinfo = sid.selectByOrderId(id.getValue(""));
	for (auto one : sorinfo) {
		auto sori = SaleInfoGoodsDTO::createShared();
		//在这里赋予dto中详情字段
		ZO_STAR_DOMAIN_DO_TO_DTO_1(sori, one, attr, Attr, unit, Unit,
			warehouse, Warehouse, price, Price, nums, Nums, discount, Discount, dsc, Dsc, total, Total,
			data, Data);
		//查找商品表并补充字段
		GoodsDAO gd;
		auto goodsdo = gd.selectById(one->getGoods());
		if (goodsdo) {
			ZO_STAR_DOMAIN_DO_TO_DTO_1(sori, goodsdo, name, Name, number, Number, spec, Spec);
		}
		dto->goodses->push_back(sori);
	}

	return dto;
}

