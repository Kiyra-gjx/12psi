#pragma once
#ifndef _ORDERDTO_H_
#define _ORDERDTO_H_
#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 采购单列表数据传输模型
 */
class OrderDTO : public oatpp::DTO {
	DTO_INIT(OrderDTO, DTO);

	// ID
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("dingdan.field.id"));
	// 关联单据
	API_DTO_FIELD_DEFAULT(String, source, ZH_WORDS_GETTER("dingdan.field.source"));
	// 所属组织
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("dingdan.field.frame"));
	// 供应商
	API_DTO_FIELD_DEFAULT(String, supplier, ZH_WORDS_GETTER("dingdan.field.supplier"));
	// 单据时间
	API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("dingdan.field.time"));
	// 单据编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("dingdan.field.number"));
	// 单据金额
	API_DTO_FIELD_DEFAULT(String, total, ZH_WORDS_GETTER("dingdan.field.total"));
	// 实际金额
	API_DTO_FIELD_DEFAULT(String, actual, ZH_WORDS_GETTER("dingdan.field.actual"));
	// 实付金额
	API_DTO_FIELD_DEFAULT(String, money, ZH_WORDS_GETTER("dingdan.field.money"));
	// 单据费用
	API_DTO_FIELD_DEFAULT(String, cost, ZH_WORDS_GETTER("dingdan.field.cost"));
	// 结算账户
	API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("dingdan.field.account"));
	// 关联人员
	API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("dingdan.field.people"));
	// 物流信息
	API_DTO_FIELD_DEFAULT(String, logistics, ZH_WORDS_GETTER("dingdan.field.logistics"));
	// 单据附件
	API_DTO_FIELD_DEFAULT(String, file, ZH_WORDS_GETTER("dingdan.field.file"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("dingdan.field.data"));
	// 扩展信息
	API_DTO_FIELD_DEFAULT(String, more, ZH_WORDS_GETTER("dingdan.field.more"));
	// 审核状态
	API_DTO_FIELD_DEFAULT(Int32, examine, ZH_WORDS_GETTER("dingdan.field.examine"));
	// 核销状态
	API_DTO_FIELD_DEFAULT(Int32, nucleus, ZH_WORDS_GETTER("dingdan.field.nucleus"));
	// 费用状态
	API_DTO_FIELD_DEFAULT(Int32,cse, ZH_WORDS_GETTER("dingdan.field.cse"));
	// 发票状态
	API_DTO_FIELD_DEFAULT(Int32, invoice, ZH_WORDS_GETTER("dingdan.field.invoice"));
	// 核对状态
	API_DTO_FIELD_DEFAULT(Int32, check, ZH_WORDS_GETTER("dingdan.field.check"));
	// 制单人
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("dingdan.field.user"));

};


/**
 * 采购单列表分页数据传输模型
 */
class OrderListPageDTO : public PageDTO<OrderDTO::Wrapper> {
	DTO_INIT(OrderListPageDTO, PageDTO<OrderDTO::Wrapper>);
};

/**
 * 采购订单详情数据传输模型
 */
class OrderDetailDTO : public oatpp::DTO {
	DTO_INIT(OrderDetailDTO, DTO);

	// ID
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("dingdan.detail.id"));
	// 供应商
	API_DTO_FIELD_DEFAULT(String, supplier, ZH_WORDS_GETTER("dingdan.field.supplier"));
	// 单据日期
	API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("dingdan.field.time"));
	// 单据编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("dingdan.field.number"));
	// 商品名称
	API_DTO_FIELD_DEFAULT(String, goodsName, ZH_WORDS_GETTER("dingdan.detail.goodsName"));
	// 商品编号
	API_DTO_FIELD_DEFAULT(String, goodsNo, ZH_WORDS_GETTER("dingdan.detail.goodsNo"));
	// 规格型号
	API_DTO_FIELD_DEFAULT(String, specModel, ZH_WORDS_GETTER("dingdan.detail.specModel"));
	// 辅助属性
	API_DTO_FIELD_DEFAULT(String, attr, ZH_WORDS_GETTER("dingdan.detail.attr"));
	// 单位
	API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("dingdan.detail.unit"));
	// 仓库
	API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("dingdan.detail.warehouse"));
	// 单价
	API_DTO_FIELD_DEFAULT(Float64, price, ZH_WORDS_GETTER("dingdan.detail.price"));
	// 数量
	API_DTO_FIELD_DEFAULT(Float64, qty, ZH_WORDS_GETTER("dingdan.detail.qty"));
	// 入库数量
	API_DTO_FIELD_DEFAULT(Float64, inQty, ZH_WORDS_GETTER("dingdan.detail.inQty"));
	// 单据金额
	API_DTO_FIELD_DEFAULT(Float64, docAmount, ZH_WORDS_GETTER("dingdan.detail.docAmount"));
	// 实际金额
	API_DTO_FIELD_DEFAULT(Float64, actualAmount, ZH_WORDS_GETTER("dingdan.detail.actualAmount"));
	// 关联人员
	API_DTO_FIELD_DEFAULT(String, relatedPerson, ZH_WORDS_GETTER("dingdan.detail.relatedPerson"));
	// 到货日期
	API_DTO_FIELD_DEFAULT(String, arrivalDate, ZH_WORDS_GETTER("dingdan.detail.arrivalDate"));
	// 物流信息
	API_DTO_FIELD_DEFAULT(String, logisticsInfo, ZH_WORDS_GETTER("dingdan.detail.logisticsInfo"));
	// 单据附件
	API_DTO_FIELD_DEFAULT(String, file, ZH_WORDS_GETTER("dingdan.field.file"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("dingdan.detail.remark"));

	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_DINGDANDTO_H_
