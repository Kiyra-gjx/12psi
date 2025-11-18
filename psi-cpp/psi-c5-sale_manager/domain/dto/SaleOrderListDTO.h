#pragma once

#ifndef _SALEORDERLISTDTO_H_
#define _SALEORDERLISTDTO_H_

#include "../GlobalInclude.h"
#include "GoodsDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

//商品与销售订单详情的联表类型
class SaleInfoGoodsDTO : public oatpp::DTO {
	DTO_INIT(SaleInfoGoodsDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("goods.field.name"));
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("goods.field.number"));
	API_DTO_FIELD_DEFAULT(String, spec, ZH_WORDS_GETTER("goods.field.spec"));

	API_DTO_FIELD_DEFAULT(String, goods, ZH_WORDS_GETTER("saleOrder.field.goods"));
	API_DTO_FIELD_DEFAULT(String, attr, ZH_WORDS_GETTER("saleOrder.field.attr"));
	API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("saleOrder.field.unit"));
	API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("saleOrder.field.warehouse"));
	API_DTO_FIELD_DEFAULT(Float64, price, ZH_WORDS_GETTER("saleOrder.field.price"));
	API_DTO_FIELD_DEFAULT(Int32, nums, ZH_WORDS_GETTER("saleOrder.field.nums"));
	API_DTO_FIELD_DEFAULT(Float64, discount, ZH_WORDS_GETTER("saleOrder.field.discount"));
	API_DTO_FIELD_DEFAULT(Float64, dsc, ZH_WORDS_GETTER("saleOrder.field.dsc"));
	API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("saleOrder.field.total"));
	API_DTO_FIELD_DEFAULT(Float64, tat, ZH_WORDS_GETTER("saleOrder.field.tat"));
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("saleOrder.field.data"));
	//没有出库数量
};


//销售订单列表数据传输模型
class SaleOrderListDTO : public oatpp::DTO {
	DTO_INIT(SaleOrderListDTO, DTO);
	//
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("saleOrder.field.frame"));
	//
	API_DTO_FIELD_DEFAULT(String, customer, ZH_WORDS_GETTER("saleOrder.field.customer"));
	//
	API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("saleOrder.field.time"));
	//
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("saleOrder.field.number"));
	//
	API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("saleOrder.field.total"));
	//
	API_DTO_FIELD_DEFAULT(Float64, actual, ZH_WORDS_GETTER("saleOrder.field.actual"));
	//
	API_DTO_FIELD_DEFAULT(String, arrival, ZH_WORDS_GETTER("saleOrder.field.arrival"));
	//
	API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("saleOrder.field.people"));
	//
	//API_DTO_FIELD_DEFAULT(String, file, ZH_WORDS_GETTER("saleOrder.field.file"));
	//
	API_DTO_FIELD_DEFAULT(Int8, examine, ZH_WORDS_GETTER("saleOrder.field.examine"));
	//
	API_DTO_FIELD_DEFAULT(Int8, state, ZH_WORDS_GETTER("saleOrder.field.state"));
	//
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("saleOrder.field.user"));
    //
    API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("saleOrder.field.data"));
	//
	API_DTO_FIELD_DEFAULT(String, fileUrl, ZH_WORDS_GETTER("salOrder.field.file"));
};

//销售订单列表分页数据传输模型
class SaleOrderListPageDTO : public PageDTO< SaleOrderListDTO::Wrapper>{
	DTO_INIT(SaleOrderListPageDTO, PageDTO< SaleOrderListDTO::Wrapper>)
};

//销售订单新增数据传输模型
class SaleOrderAddDTO : public oatpp::DTO {
	DTO_INIT(SaleOrderAddDTO, DTO);
	//
	API_DTO_FIELD_DEFAULT(String, customer, ZH_WORDS_GETTER("saleOrder.field.customer"));
	//
	API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("saleOrder.field.time"));
	//
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("saleOrder.field.number"));
	//
	API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("saleOrder.field.total"));
	//
	API_DTO_FIELD_DEFAULT(Float64, actual, ZH_WORDS_GETTER("saleOrder.field.actual"));
	//
	API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("saleOrder.field.people"));
	//
	API_DTO_FIELD_DEFAULT(String, arrival, ZH_WORDS_GETTER("saleOrder.field.arrival"));
	//
	API_DTO_FIELD_DEFAULT(String, logistics, ZH_WORDS_GETTER("saleOrder.field.logistics"));
	//
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("saleOrder.field.data"));

	API_DTO_FIELD_DEFAULT(Int32, examine, ZH_WORDS_GETTER("saleOrder.field.examine"));

	API_DTO_FIELD_DEFAULT(Int32, state, ZH_WORDS_GETTER("saleOrder.field.state"));

	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("saleOrder.field.user"));
	//销售订单详情与商品联表字段
	API_DTO_FIELD_DEFAULT(oatpp::List<SaleInfoGoodsDTO::Wrapper>, goodses, ZH_WORDS_GETTER("saleOrder.field.goodses"));
};


//销售订单详情数据传输模型
class SaleOrderDetailDTO : public SaleOrderListDTO {
	DTO_INIT(SaleOrderDetailDTO, SaleOrderListDTO);
	//销售订单字段
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("saleOrder.field.id"));
	//销售订单详情与商品联表字段
	API_DTO_FIELD_DEFAULT(oatpp::List<SaleInfoGoodsDTO::Wrapper>, goodses, ZH_WORDS_GETTER("saleOrder.field.goodses"));
	//
	
public:
	SaleOrderDetailDTO() {
		goodses = {};
	}
};

/*
	通过现有销售订单生成销售单的模型
*/
class SellGenerateDTO : public oatpp::DTO
{
	DTO_INIT(SellGenerateDTO, DTO);
	/*
		这个功能并不需要完整的销售订单，因为生成的也不是完整销售单
		输入的是销售订单详情表数据（在前端展示的数据）
	*/
	// PID
	API_DTO_FIELD_DEFAULT(String, pid, ZH_WORDS_GETTER("SorInfo.field.pid"));
	// 所属商品
	API_DTO_FIELD_DEFAULT(String, goods, ZH_WORDS_GETTER("SorInfo.field.goods"));
	// 单位
	API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("SorInfo.field.unit"));
	// 仓库
	API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("SorInfo.field.warehouse"));
	// 单价
	API_DTO_FIELD_DEFAULT(Float64, price, ZH_WORDS_GETTER("SorInfo.field.price"));
	// 数量
	API_DTO_FIELD_DEFAULT(Float64, nums, ZH_WORDS_GETTER("SorInfo.field.nums"));
	// 金额
	API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("SorInfo.field.total"));
	//
	
};

/*
	通过现有销售订单生成采购订单的模型
*/
class PurchaseGenerateDTO : public oatpp::DTO
{
	DTO_INIT(PurchaseGenerateDTO, DTO);

	/*
		这个功能并不需要完整的销售订单，因为生成的也不是完整销售单
		输入的是销售订单详情表数据（在前端展示的数据）
	*/
	// PID
	API_DTO_FIELD_DEFAULT(String, pid, ZH_WORDS_GETTER("SorInfo.field.pid"));
	// 所属商品
	API_DTO_FIELD_DEFAULT(String, goods, ZH_WORDS_GETTER("SorInfo.field.goods"));
	// 单位
	API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("SorInfo.field.unit"));
	// 仓库
	API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("SorInfo.field.warehouse"));
	// 单价
	API_DTO_FIELD_DEFAULT(Float64, price, ZH_WORDS_GETTER("SorInfo.field.price"));
	// 数量
	API_DTO_FIELD_DEFAULT(Float64, nums, ZH_WORDS_GETTER("SorInfo.field.nums"));
	// 金额
	API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("SorInfo.field.total"));
};

// 删除销售订单（支持批量）
class SorDeleteDTO :public oatpp::DTO {
	DTO_INIT(SorDeleteDTO, DTO);

	// 订单ID列表
	DTO_FIELD(List<String>, orderIds);
	DTO_FIELD_INFO(orderIds) {
		//	info->description = "要删除的订单ID列表";
		info->required = true;
	}
};

// 审核/反审核（支持批量）
class SorAuditDTO :public oatpp::DTO {
	DTO_INIT(SorAuditDTO, DTO);
	// 订单ID列表
	DTO_FIELD(List<String>, orderIds);

};

// 修改销售订单
class SorUpdateDTO : public oatpp::DTO {
	DTO_INIT(SorUpdateDTO, DTO);
	// 销售订单编号
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("saleOrder.field.id"));
	API_DTO_FIELD_DEFAULT(String, customer, ZH_WORDS_GETTER("saleOrder.field.customer"));
	API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("saleOrder.field.time"));
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("saleOrder.field.data"));     // 备注信息（可选修改）
	API_DTO_FIELD_DEFAULT(String, logistics, ZH_WORDS_GETTER("saleOrder.field.logistics")); // 物流信息（可选修改）
	API_DTO_FIELD_DEFAULT(String, file, ZH_WORDS_GETTER("saleOrder.field.file"));
	API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("saleOrder.field.people"));
	API_DTO_FIELD_DEFAULT(Float64, actual, ZH_WORDS_GETTER("saleOrder.field.actual"));
	API_DTO_FIELD_DEFAULT(String, arrival, ZH_WORDS_GETTER("saleOrder.field.arrival"));
};

// 简单报表的查询DTO
class SorExportSimpleQuery : public oatpp::DTO {
	DTO_INIT(SorExportSimpleQuery, DTO);
	DTO_FIELD(String, startDate);
	DTO_FIELD(String, endDate);
};

// 导出简单报表（可选，有时直接用文件流）
class SorExportSimpleDTO : public oatpp::DTO {
	DTO_INIT(SorExportSimpleDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("saleOrder.field.frame"));
	API_DTO_FIELD_DEFAULT(String, customer, ZH_WORDS_GETTER("saleOrder.field.customer"));
	API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("saleOrder.field.time"));
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("saleOrder.field.number"));
	API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("saleOrder.field.total"));
	API_DTO_FIELD_DEFAULT(Float64, actual, ZH_WORDS_GETTER("saleOrder.field.actual"));
	API_DTO_FIELD_DEFAULT(String, arrival, ZH_WORDS_GETTER("saleOrder.field.arrival"));
	API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("saleOrder.field.people"));
	API_DTO_FIELD_DEFAULT(Int32, examine, ZH_WORDS_GETTER("saleOrder.field.examine"));
	API_DTO_FIELD_DEFAULT(Int32, state, ZH_WORDS_GETTER("saleOrder.field.state"));
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("saleOrder.field.user"));
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("saleOrder.field.data"));
};

class SorExportDetailQuery : public oatpp::DTO {
	DTO_INIT(SorExportDetailQuery, DTO);
	API_DTO_FIELD_REQUIRE(String, orderNoLike, ZH_WORDS_GETTER("saleOrder.field.id"), true);
};

// 详细报表的每一项DTO
class SorExportDetailItemDTO : public oatpp::DTO {
	DTO_INIT(SorExportDetailItemDTO, DTO);
	DTO_FIELD(String, goodsName);
	DTO_FIELD(String, spec);
	DTO_FIELD(String, attr);
	DTO_FIELD(String, unit);
	DTO_FIELD(String, warehouse);
	DTO_FIELD(Float64, price);
	DTO_FIELD(Int32, nums);
	DTO_FIELD(Float64, handle);
	DTO_FIELD(Float64, discount);
	DTO_FIELD(Float64, dsc);
	DTO_FIELD(Float64, total);
	DTO_FIELD(String, data);
};

// 导出详细报表（可选，有时直接用文件流）
class SorExportDetailDTO : public oatpp::DTO {
	DTO_INIT(SorExportDetailDTO, DTO);
	DTO_FIELD(String, customer);
	DTO_FIELD(String, time);
	DTO_FIELD(String, number);
	DTO_FIELD(Float64, total);
	DTO_FIELD(Float64, actual);
	DTO_FIELD(String, people);
	DTO_FIELD(String, arrival);
	DTO_FIELD(String, logistics);
	DTO_FIELD(String, data);
	DTO_FIELD(Vector<SorExportDetailItemDTO::Wrapper>, items);
};
//bor_info
//class BorInfoDTO : public oatpp::DTO {
//	DTO_INIT(BorInfoDTO, DTO)
//
//		API_DTO_FIELD_DEFAULT(Int32, goods, ZH_WORDS_GETTER("borInfo.field.name"), true);      // 所属商品 必要
//	API_DTO_FIELD_DEFAULT(String, attr, ZH_WORDS_GETTER("borInfo.field.attr"), false);      // 辅助属性
//	API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("borInfo.field.unit"), false);      // 单位
//	API_DTO_FIELD_DEFAULT(Int32, warehouse, ZH_WORDS_GETTER("borInfo.field.warehouse"), true); // 仓库 必要
//	API_DTO_FIELD_DEFAULT(Float64, price, ZH_WORDS_GETTER("borInfo.field.price"), true);    // 单价 必要
//	API_DTO_FIELD_DEFAULT(Float64, nums, ZH_WORDS_GETTER("borInfo.field.nums"), true);      // 数量 必要
//	API_DTO_FIELD_DEFAULT(Float64, discount, ZH_WORDS_GETTER("borInfo.field.discount"), true); // 折扣率 必要
//	API_DTO_FIELD_DEFAULT(Float64, dsc, ZH_WORDS_GETTER("borInfo.field.dsc"), false);       // 折扣额
//	API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("borInfo.field.total"), false);   // 金额
//	API_DTO_FIELD_DEFAULT(Float64, tax, ZH_WORDS_GETTER("borInfo.field.tax"), true);        // 税率 必要
//	API_DTO_FIELD_DEFAULT(Float64, tat, ZH_WORDS_GETTER("borInfo.field.tat"), false);       // 税额
//	API_DTO_FIELD_DEFAULT(Float64, tpt, ZH_WORDS_GETTER("borInfo.field.tpt"), false);       // 价税合计
//	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("borInfo.field.data"), false);      // 备注信息
//};
// 导入数据
//class SorImportDTO : public oatpp::DTO {
//	DTO_INIT(SorImportDTO, DTO)
//
//	API_DTO_FIELD_DEFAULT(Int32, frame, ZH_WORDS_GETTER("saleOrder.field.frame"), true);     // 所属组织 必要
//	API_DTO_FIELD_DEFAULT(Int32, customer, ZH_WORDS_GETTER("saleOrder.field.customer"), false); // 客户
//	API_DTO_FIELD_DEFAULT(Int32, time, ZH_WORDS_GETTER("saleOrder.field.time"), true);      // 单据时间 必要
//	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("saleOrder.field.number"), true); // 单据编号 必要
//	API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("saleOrder.field.total"), false); // 单据金额 
//	API_DTO_FIELD_DEFAULT(Float64, actual, ZH_WORDS_GETTER("saleOrder.field.actual"), true); // 实际金额 必要
//	API_DTO_FIELD_DEFAULT(Int32, people, ZH_WORDS_GETTER("saleOrder.field.people"), false); // 关联人员
//	API_DTO_FIELD_DEFAULT(Int32, arrival, ZH_WORDS_GETTER("saleOrder.field.arrival"), false); // 到货日期
//	API_DTO_FIELD_DEFAULT(String, logistics, ZH_WORDS_GETTER("saleOrder.field.logistics"), false); // 物流信息
//	API_DTO_FIELD_DEFAULT(String, file, ZH_WORDS_GETTER("saleOrder.field.file"), false);    // 单据附件
//	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("saleOrder.field.data"), false);    // 备注信息
//	API_DTO_FIELD_DEFAULT(List<BorInfoDTO::Wrapper>, BorInfos, ZH_WORDS_GETTER("saleOrder.field.borInfos"), true); // 商品详情 必要
//};

// 采购订单商品明细
class SorInfoDTO : public oatpp::DTO {
	DTO_INIT(SorInfoDTO, DTO)

	API_DTO_FIELD_REQUIRE(String, goods, ZH_WORDS_GETTER("borInfo.field.goods"), true);      // 所属商品 必要
	API_DTO_FIELD_REQUIRE(String, attr, ZH_WORDS_GETTER("borInfo.field.attr"), false);      // 辅助属性
	API_DTO_FIELD_REQUIRE(String, unit, ZH_WORDS_GETTER("borInfo.field.unit"), false);      // 单位
	API_DTO_FIELD_REQUIRE(String, warehouse, ZH_WORDS_GETTER("borInfo.field.warehouse"), true); // 仓库 必要
	API_DTO_FIELD_REQUIRE(Float64, price, ZH_WORDS_GETTER("borInfo.field.price"), true);    // 单价 必要
	API_DTO_FIELD_REQUIRE(Float64, nums, ZH_WORDS_GETTER("borInfo.field.nums"), true);      // 数量 必要
	API_DTO_FIELD_REQUIRE(Float64, discount, ZH_WORDS_GETTER("borInfo.field.discount"), true); // 折扣率 必要
	API_DTO_FIELD_REQUIRE(Float64, dsc, ZH_WORDS_GETTER("borInfo.field.dsc"), false);       // 折扣额
	API_DTO_FIELD_REQUIRE(Float64, total, ZH_WORDS_GETTER("borInfo.field.total"), false);   // 金额
	API_DTO_FIELD_REQUIRE(Float64, tax, ZH_WORDS_GETTER("borInfo.field.tax"), true);        // 税率 必要
	API_DTO_FIELD_REQUIRE(Float64, tat, ZH_WORDS_GETTER("borInfo.field.tat"), false);       // 税额
	API_DTO_FIELD_REQUIRE(Float64, tpt, ZH_WORDS_GETTER("borInfo.field.tpt"), false);       // 价税合计
	API_DTO_FIELD_REQUIRE(String, data, ZH_WORDS_GETTER("borInfo.field.data"), false);      // 备注信息
};

// 销售订单导入数据
class SorImportDTO : public oatpp::DTO {
	DTO_INIT(SorImportDTO, DTO)

	API_DTO_FIELD_REQUIRE(String, frame, ZH_WORDS_GETTER("saleOrder.field.frame"), false);   // 所属组织
	API_DTO_FIELD_REQUIRE(String, customer, ZH_WORDS_GETTER("saleOrder.field.customer"), true); // 客户 必要
	API_DTO_FIELD_REQUIRE(String, time, ZH_WORDS_GETTER("saleOrder.field.time"), true);     // 单据时间 必要
	API_DTO_FIELD_REQUIRE(String, number, ZH_WORDS_GETTER("saleOrder.field.number"), true); // 单据编号 必要
	API_DTO_FIELD_REQUIRE(Float64, total, ZH_WORDS_GETTER("saleOrder.field.total"), false);  // 单据金额
	API_DTO_FIELD_REQUIRE(Float64, actual, ZH_WORDS_GETTER("saleOrder.field.actual"), true); // 实际金额 必要
	API_DTO_FIELD_REQUIRE(String, people, ZH_WORDS_GETTER("saleOrder.field.people"), false); // 关联人员
	API_DTO_FIELD_REQUIRE(String, arrival, ZH_WORDS_GETTER("saleOrder.field.arrival"), false); // 到货日期 false
	API_DTO_FIELD_REQUIRE(String, logistics, ZH_WORDS_GETTER("saleOrder.field.logistics"), false); // 物流信息
	API_DTO_FIELD_REQUIRE(String, file, ZH_WORDS_GETTER("saleOrder.field.file"), false);    // 单据附件
	API_DTO_FIELD_REQUIRE(String, data, ZH_WORDS_GETTER("saleOrder.field.data"), false);    // 备注信息
	API_DTO_FIELD_REQUIRE(List<Object<SorInfoDTO>>, items, ZH_WORDS_GETTER("saleOrder.field.items"), false); // 商品明细
};



#include OATPP_CODEGEN_END(DTO)

#endif