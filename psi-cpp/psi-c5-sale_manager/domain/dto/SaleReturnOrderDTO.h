#pragma once

//销售退货单

#ifndef _SALERETURNORDERDTO_H_
#define _SALERETURNORDERDTO_H_

#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 获取销售退货单列表（条件+分页）
class SreListDTO : public oatpp::DTO {

	DTO_INIT(SreListDTO, DTO);

	//退货单id
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("saleReturnOrder.field.listid"), true);
	//关联单据|SELL
	API_DTO_FIELD_DEFAULT(String, source, ZH_WORDS_GETTER("saleReturnOrder.field.source"));
	//所属组织
	API_DTO_FIELD_REQUIRE(String, frame, ZH_WORDS_GETTER("saleReturnOrder.field.frame"), true);
	//客户
	API_DTO_FIELD_REQUIRE(String, customer, ZH_WORDS_GETTER("saleReturnOrder.field.customer"), true);
	//单据时间
	API_DTO_FIELD_REQUIRE(String, time, ZH_WORDS_GETTER("saleReturnOrder.field.time"), true);
	//单据编号
	API_DTO_FIELD_REQUIRE(String, number, ZH_WORDS_GETTER("saleReturnOrder.field.number"), true);
	//单据金额
	API_DTO_FIELD_REQUIRE(Float64, totalMoney, ZH_WORDS_GETTER("saleReturnOrder.field.total"), true);//String改为Float64
	//实际金额
	API_DTO_FIELD_REQUIRE(Float64, actual, ZH_WORDS_GETTER("saleReturnOrder.field.actual"), true);
	//实付金额
	API_DTO_FIELD_REQUIRE(Float64, money, ZH_WORDS_GETTER("saleReturnOrder.field.money"), true);
	//单据费用
	API_DTO_FIELD_REQUIRE(Float64, cost, ZH_WORDS_GETTER("saleReturnOrder.field.cost"), true);
	//结算账户
	API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("saleReturnOrder.field.account"));
	//关联人员
	API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("saleReturnOrder.field.people"));
	//物流信息
	API_DTO_FIELD_REQUIRE(String, logistics, ZH_WORDS_GETTER("saleReturnOrder.field.logitics"), false);
	//单据附件
	API_DTO_FIELD_REQUIRE(String, file, ZH_WORDS_GETTER("saleReturnOrder.field.file"), false);
	//备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("saleReturnOrder.field.data"));
	//扩展信息
	API_DTO_FIELD_REQUIRE(String, more, ZH_WORDS_GETTER("saleReturnOrder.field.more"), false);
	//审核状态[0:未审核|1:已审核]
	API_DTO_FIELD_REQUIRE(Int32, examine, ZH_WORDS_GETTER("saleReturnOrder.field.examine"), true);
	//核销状态[0:未核销|1:部分核销|2:已核销]
	API_DTO_FIELD_REQUIRE(Int32, nucleus, ZH_WORDS_GETTER("saleReturnOrder.field.nucleus"), true);
	//费用状态[0:未结算|1:部分解释|2:已结算|3:无需结算]
	API_DTO_FIELD_REQUIRE(Int32, cse, ZH_WORDS_GETTER("saleReturnOrder.field.cse"), true);
	//发票状态[0:未开票|1:部分开票|2:已开票|3:无需开票]
	API_DTO_FIELD_REQUIRE(Int32, invoice, ZH_WORDS_GETTER("saleReturnOrder.field.invoice"), true);
	//核对状态[0:未核对|1:已核对]
	API_DTO_FIELD_REQUIRE(Int32, check, ZH_WORDS_GETTER("saleReturnOrder.field.check"), true);
	//制单人
	API_DTO_FIELD_REQUIRE(String, user, ZH_WORDS_GETTER("saleReturnOrder.field.user"), true);

};

class SreInfoDTO : public oatpp::DTO {
	DTO_INIT(SreInfoDTO, DTO);
	//关联单据|SELL
	API_DTO_FIELD_DEFAULT(String, source, ZH_WORDS_GETTER("saleReturnOrder.field.source"));
	//辅助属性
	API_DTO_FIELD_DEFAULT(String, attr, ZH_WORDS_GETTER("goods.field.attr"));
	//单位
	API_DTO_FIELD_REQUIRE(String, unit, ZH_WORDS_GETTER("goods.field.unit"), true);
	//仓库
	API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("goods.field.warehouse"));
	//批次号
	API_DTO_FIELD_DEFAULT(String, batch, ZH_WORDS_GETTER("goods.field.batch"));
	//生产日期
	API_DTO_FIELD_DEFAULT(String, mfd, ZH_WORDS_GETTER("goods.field.mfd"));
	//单价
	API_DTO_FIELD_REQUIRE(Float64, price, ZH_WORDS_GETTER("goods.field.price"), true);
	//数量
	API_DTO_FIELD_REQUIRE(Float64, nums, ZH_WORDS_GETTER("goods.field.nums"), true);
	//折扣率
	API_DTO_FIELD_REQUIRE(Float64, discount, ZH_WORDS_GETTER("goods.field.discount"), true);
	//折扣额
	API_DTO_FIELD_REQUIRE(Float64, dsc, ZH_WORDS_GETTER("goods.field.dsc"), true);
	//金额
	API_DTO_FIELD_REQUIRE(Float64, total, ZH_WORDS_GETTER("saleReturnOrder.field.total"), true);
	//备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("saleReturnOrder.field.data"));
};

//获取前端传入的单项退货商品信息
class SingleInfoDTO : public SreInfoDTO {

	DTO_INIT(SingleInfoDTO, SreInfoDTO);
	//商品id
	API_DTO_FIELD_REQUIRE(String, goods, ZH_WORDS_GETTER("goods.field.goods"), true);
};

//获取数据库传出的单项退货商品信息
class SreSingleInfoDTO : public SreInfoDTO {

	DTO_INIT(SreSingleInfoDTO, SreInfoDTO);

	//商品名称
	API_DTO_FIELD_DEFAULT(String, goodsName, ZH_WORDS_GETTER("goods.field.name"));
	//商品编号
	API_DTO_FIELD_DEFAULT(String, goodsNumber, ZH_WORDS_GETTER("goods.field.numebr"));
	//规格型号
	API_DTO_FIELD_DEFAULT(String, goodsSpec, ZH_WORDS_GETTER("goods.field.spec"));
};

// 获取指定销售退货单详情
class SreDetailDTO : public SreListDTO {

	DTO_INIT(SreDetailDTO, SreListDTO);

	//出库数量
	API_DTO_FIELD_DEFAULT(Int64, handle, ZH_WORDS_GETTER("saleReturnOrder.field.handle"));

	//传出的退货单商品信息
	API_DTO_FIELD_REQUIRE(List<SreSingleInfoDTO::Wrapper>, sreinfos, ZH_WORDS_GETTER("saleReturnOrder.field.outgoods"), true);
};

// 新增销售退货单
class SreAddDTO : public SreListDTO {

	DTO_INIT(SreAddDTO, SreListDTO);

	//传入的退货单商品信息
	API_DTO_FIELD_REQUIRE(List<SingleInfoDTO::Wrapper>, infos, ZH_WORDS_GETTER("saleReturnOrder.field.ingoods"), true);
};

// 分页传输销售退货单列表
class SrePageDTO : public PageDTO<SreListDTO::Wrapper>
{
	DTO_INIT(SrePageDTO, PageDTO<SreListDTO::Wrapper>);
};

// 销售退货单详情（sre_info）的商品级明细子 DTO
class SreInfoItemDTO : public oatpp::DTO {

	DTO_INIT(SreInfoItemDTO, DTO)
	API_DTO_FIELD_DEFAULT(String, goods, ZH_WORDS_GETTER("SreInfoItem.field.goods")); // 所属商品
	API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("SreInfoItem.field.unit"));   // 单位
	API_DTO_FIELD_DEFAULT(String, price, ZH_WORDS_GETTER("SreInfoItem.field.price")); // 单价
	API_DTO_FIELD_DEFAULT(String, nums, ZH_WORDS_GETTER("SreInfoItem.field.nums"));   // 数量
	API_DTO_FIELD_DEFAULT(Int32, total, ZH_WORDS_GETTER("SreInfoItem.field.total")); // 金额（单价×数量）
	API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("SreInfoItem.field.warehouse")); // 仓库
	API_DTO_FIELD_DEFAULT(String, batch, ZH_WORDS_GETTER("SreInfoItem.field.batch"));   // 批次号
};

// 修改销售退货单
class SreUpdateDTO : public oatpp::DTO {

	DTO_INIT(SreUpdateDTO, DTO)
	// 销售退货单主表（sre）关键可修改字段
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("saleReturnOrder.field.listid"), true);         // 退货单ID（必选，定位要修改的单据）
	API_DTO_FIELD_DEFAULT(String, customer, ZH_WORDS_GETTER("saleReturnOrder.field.customer")); // 客户ID（可选修改）
	API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("saleReturnOrder.field.time"));   // 单据时间（可选修改，对应数据库 datetime）
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("saleReturnOrder.field.data"));     // 备注信息（可选修改）
	API_DTO_FIELD_DEFAULT(String, logistics, ZH_WORDS_GETTER("saleReturnOrder.field.logistics")); // 物流信息（可选修改）
	API_DTO_FIELD_DEFAULT(String, file, ZH_WORDS_GETTER("saleReturnOrder.field.file"));     // 单据附件（可选修改）
	API_DTO_FIELD_DEFAULT(String, more, ZH_WORDS_GETTER("saleReturnOrder.field.more"));     // 扩展信息（可选修改）
	API_DTO_FIELD_REQUIRE(Int8, examine, ZH_WORDS_GETTER("saleReturnOrder.field.examine"), true);
};

// 简单报表的查询DTO
class SreExportSimpleQuery : public oatpp::DTO {

	DTO_INIT(SreExportSimpleQuery, DTO)
	API_DTO_FIELD_DEFAULT(String, startDate, ZH_WORDS_GETTER("summary.saleReturnOrder.field.begintime")); // 开始日期
	API_DTO_FIELD_DEFAULT(String, endDate, ZH_WORDS_GETTER("summary.saleReturnOrder.field.endtime"));     // 结束日期
	API_DTO_FIELD_DEFAULT(Int32, examineStatus, ZH_WORDS_GETTER("summary.saleReturnOrder.field.examine")); // 审核状态
};
// 简单报表的响应 DTO
class SreExportSimpleDTO : public oatpp::DTO {
	DTO_INIT(SreExportSimpleDTO, DTO)
		// 字段与销售退货单主表（sre）核心信息对齐
		//所属组织
		API_DTO_FIELD_REQUIRE(String, frame, ZH_WORDS_GETTER("saleReturnOrder.field.frame"), true);
	//客户
	API_DTO_FIELD_REQUIRE(String, customer, ZH_WORDS_GETTER("saleReturnOrder.field.customer"), true);
	//单据时间
	API_DTO_FIELD_REQUIRE(String, time, ZH_WORDS_GETTER("saleReturnOrder.field.time"), true);
	//单据编号
	API_DTO_FIELD_REQUIRE(String, number, ZH_WORDS_GETTER("saleReturnOrder.field.number"), true);
	//单据金额
	API_DTO_FIELD_REQUIRE(Float64, total, ZH_WORDS_GETTER("saleReturnOrder.field.total"), true);
	//实际金额
	API_DTO_FIELD_REQUIRE(Float64, actual, ZH_WORDS_GETTER("saleReturnOrder.field.actual"), true);
	//实付金额
	API_DTO_FIELD_REQUIRE(Float64, money, ZH_WORDS_GETTER("saleReturnOrder.field.money"), true);
	//单据费用
	API_DTO_FIELD_REQUIRE(Float64, cost, ZH_WORDS_GETTER("saleReturnOrder.field.cost"), true);
	//关联人员
	API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("saleReturnOrder.field.people"));
	//审核状态[0:未审核|1:已审核]
	API_DTO_FIELD_REQUIRE(Int8, examine, ZH_WORDS_GETTER("saleReturnOrder.field.examine"), true);
	//核销状态[0:未核销|1:部分核销|2:已核销]
	API_DTO_FIELD_REQUIRE(Int8, nucleus, ZH_WORDS_GETTER("saleReturnOrder.field.nucleus"), true);
	//费用状态[0:未结算|1:部分解释|2:已结算|3:无需结算]
	API_DTO_FIELD_REQUIRE(Int8, cse, ZH_WORDS_GETTER("saleReturnOrder.field.cse"), true);
	//发票状态[0:未开票|1:部分开票|2:已开票|3:无需开票]
	API_DTO_FIELD_REQUIRE(Int8, invoice, ZH_WORDS_GETTER("saleReturnOrder.field.invoice"), true);
	//核对状态[0:未核对|1:已核对]
	API_DTO_FIELD_REQUIRE(Int8, check, ZH_WORDS_GETTER("saleReturnOrder.field.check"), true);
	//制单人
	API_DTO_FIELD_REQUIRE(String, user, ZH_WORDS_GETTER("saleReturnOrder.field.user"), true);
	//备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("saleReturnOrder.field.data"));
};

// 详细报表的查询DTO
class SreExportDetailQuery : public oatpp::DTO {

	DTO_INIT(SreExportDetailQuery, DTO)
	API_DTO_FIELD_REQUIRE(String, orderNoLike, ZH_WORDS_GETTER("saleReturnOrder.field.listid"), true); // 退货单id
	API_DTO_FIELD_REQUIRE(String, customer, ZH_WORDS_GETTER("saleReturnOrder.field.customer"), true);   // 客户

};
//详细报表的响应DTO的明细行
class SreDetailItemDTO : public oatpp::DTO {
	DTO_INIT(SreDetailItemDTO, DTO)
		API_DTO_FIELD_DEFAULT(String, goodsName, ZH_WORDS_GETTER("goods.field.name"));      // 商品名称
	API_DTO_FIELD_DEFAULT(String, spec, ZH_WORDS_GETTER("goods.field.spec"));          // 规格型号
	API_DTO_FIELD_DEFAULT(String, attr, ZH_WORDS_GETTER("goods.field.attr"));          // 辅助属性
	API_DTO_FIELD_REQUIRE(String, unit, ZH_WORDS_GETTER("goods.field.unit"), true);    // 单位
	API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("goods.field.warehouse"));// 仓库
	API_DTO_FIELD_REQUIRE(Float64, price, ZH_WORDS_GETTER("goods.field.sell"), true); // 单价
	API_DTO_FIELD_REQUIRE(Float64, nums, ZH_WORDS_GETTER("goods.field.nums"), true);   // 数量
	API_DTO_FIELD_REQUIRE(Float64, discountRate, ZH_WORDS_GETTER("goods.field.discount"), true); // 折扣率
	API_DTO_FIELD_REQUIRE(Float64, discountAmount, ZH_WORDS_GETTER("goods.field.dsc"), true);    // 折扣额
	API_DTO_FIELD_REQUIRE(Float64, amount, ZH_WORDS_GETTER("saleReturnOrder.field.total"), true); // 金额
	API_DTO_FIELD_REQUIRE(Float64, taxRate, ZH_WORDS_GETTER("saleReturnOrder.field.tax"), true);   // 税率
	API_DTO_FIELD_REQUIRE(Float64, taxAmount, ZH_WORDS_GETTER("saleReturnOrder.field.tat"), true); // 税额
	API_DTO_FIELD_REQUIRE(Float64, taxIncludedAmount, ZH_WORDS_GETTER("saleReturnOrder.field.tpt"), true); // 价税合计
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("saleReturnOrder.field.data")); // 备注信息
};
// 详细报表的响应 DTO
class SreExportDetailDTO : public oatpp::DTO {
	DTO_INIT(SreExportDetailDTO, DTO)
		API_DTO_FIELD_DEFAULT(String, customer, ZH_WORDS_GETTER("saleReturnOrder.field.customer")); // 客户
	API_DTO_FIELD_DEFAULT(String, billDate, ZH_WORDS_GETTER("saleReturnOrder.field.time"));     // 单据日期
	API_DTO_FIELD_DEFAULT(String, billNo, ZH_WORDS_GETTER("saleReturnOrder.field.number"));     // 单据编号
	API_DTO_FIELD_REQUIRE(Float64, billAmount, ZH_WORDS_GETTER("saleReturnOrder.field.total"), true);   // 单据金额
	API_DTO_FIELD_REQUIRE(Float64, billCost, ZH_WORDS_GETTER("saleReturnOrder.field.cost"), true);     // 单据费用
	API_DTO_FIELD_REQUIRE(Float64, actualAmount, ZH_WORDS_GETTER("saleReturnOrder.field.actual"), true); // 实际金额
	API_DTO_FIELD_REQUIRE(Float64, writeOffAmount, ZH_WORDS_GETTER("saleReturnOrder.field.nucleus"), true); // 核销金额
	API_DTO_FIELD_REQUIRE(String, settlementAccount, ZH_WORDS_GETTER("saleReturnOrder.field.account"), true); // 结算账户
	API_DTO_FIELD_REQUIRE(Int32, invoiceInfo, ZH_WORDS_GETTER("saleReturnOrder.field.invoice"), true);   // 发票信息
	API_DTO_FIELD_DEFAULT(String, relatedPerson, ZH_WORDS_GETTER("saleReturnOrder.field.people"));     // 关联人员
	API_DTO_FIELD_DEFAULT(String, logisticsInfo, ZH_WORDS_GETTER("saleReturnOrder.field.logistics"));   // 物流信息
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("saleReturnOrder.field.data"));               // 备注信息
	API_DTO_FIELD_DEFAULT(Vector<SreDetailItemDTO::Wrapper>, items, ZH_WORDS_GETTER("saleReturnOrder.field.items")); // 明细列表
};

// 核对/反核对DTO
class SreCheckDTO : public oatpp::DTO {
	DTO_INIT(SreCheckDTO, DTO);
	// 退货单ID列表
	API_DTO_FIELD_DEFAULT(Vector<String>, ids, ZH_WORDS_GETTER("Sre.field.ids"));
	// 核对状态（true-核对 false-反核对）
	API_DTO_FIELD_DEFAULT(Boolean, checkStatus, ZH_WORDS_GETTER("Sre.field.checkStatus"));
	// 核对备注
	API_DTO_FIELD_DEFAULT(String, checkRemark, ZH_WORDS_GETTER("Sre.field.checkRemark"));
};


//jinyang
// 导入数据DTO
class SaleReturnDataImportDTO : public oatpp::DTO {
	DTO_INIT(SaleReturnDataImportDTO, DTO);
	// 文件路径
	API_DTO_FIELD_DEFAULT(String, filePath, ZH_WORDS_GETTER("SaleReturn.field.filePath"));
	// 文件名
	API_DTO_FIELD_DEFAULT(String, fileName, ZH_WORDS_GETTER("SaleReturn.field.fileName"));
};

// 审核/反审核DTO
class SaleReturnAuditDTO : public oatpp::DTO {
	DTO_INIT(SaleReturnAuditDTO, DTO);
	// 退货单ID列表
	API_DTO_FIELD_DEFAULT(Vector<String>, ids, ZH_WORDS_GETTER("SaleReturn.field.ids"));
	// 审核状态：true-审核 false-反审核
	API_DTO_FIELD_DEFAULT(Boolean, auditStatus, ZH_WORDS_GETTER("SaleReturn.field.auditStatus"));
	// 审核备注
	API_DTO_FIELD_DEFAULT(String, auditRemark, ZH_WORDS_GETTER("SaleReturn.field.auditRemark"));
};

//jinyang

// ============ 数据导入相关 DTO ============

// 导入单个退货商品DTO
class SaleReturnItemImportDTO : public oatpp::DTO {
	DTO_INIT(SaleReturnItemImportDTO, DTO);
	// 商品名称/编号
	API_DTO_FIELD_DEFAULT(String, goods, ZH_WORDS_GETTER("goods.field.goods"));
	// 辅助属性
	API_DTO_FIELD_DEFAULT(String, attr, ZH_WORDS_GETTER("goods.field.attr"));
	// 单位
	API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("goods.field.unit"));
	// 仓库
	API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("goods.field.warehouse"));
	// 单价
	API_DTO_FIELD_DEFAULT(Float64, price, ZH_WORDS_GETTER("goods.field.price"));
	// 数量
	API_DTO_FIELD_DEFAULT(Float64, nums, ZH_WORDS_GETTER("goods.field.nums"));
	// 金额
	API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("saleReturnOrder.field.total"));
	// 备注
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("saleReturnOrder.field.data"));
};

// 导入单个退货单DTO
class SaleReturnOrderImportDTO : public oatpp::DTO {
	DTO_INIT(SaleReturnOrderImportDTO, DTO);
	// 单据编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("saleReturnOrder.field.number"));
	// 客户
	API_DTO_FIELD_DEFAULT(String, customer, ZH_WORDS_GETTER("saleReturnOrder.field.customer"));
	// 单据时间
	API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("saleReturnOrder.field.time"));
	// 单据金额
	API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("saleReturnOrder.field.total"));
	// 实际金额
	API_DTO_FIELD_DEFAULT(Float64, actual, ZH_WORDS_GETTER("saleReturnOrder.field.actual"));
	// 实付金额
	API_DTO_FIELD_DEFAULT(Float64, money, ZH_WORDS_GETTER("saleReturnOrder.field.money"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("saleReturnOrder.field.data"));
	// 物流信息
	API_DTO_FIELD_DEFAULT(String, logistics, ZH_WORDS_GETTER("saleReturnOrder.field.logistics"));
	// 关联人员
	API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("saleReturnOrder.field.people"));
	// 商品明细列表
	API_DTO_FIELD_DEFAULT(List<Object<SaleReturnItemImportDTO>>, items, ZH_WORDS_GETTER("saleReturnOrder.field.items"));
};

// 批量导入DTO
class SaleReturnBatchImportDTO : public oatpp::DTO {
	DTO_INIT(SaleReturnBatchImportDTO, DTO);
	// 导入数据列表
	API_DTO_FIELD_DEFAULT(List<Object<SaleReturnOrderImportDTO>>, importData, ZH_WORDS_GETTER("import.field.data"));
	// 操作人
	API_DTO_FIELD_DEFAULT(String, username, ZH_WORDS_GETTER("import.field.username"));
};

// 导入错误信息DTO
class ImportErrorDTO : public oatpp::DTO {
	DTO_INIT(ImportErrorDTO, DTO);
	// 行号
	API_DTO_FIELD_DEFAULT(Int32, rowIndex, ZH_WORDS_GETTER("import.field.rowIndex"));
	// 单号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("saleReturnOrder.field.number"));
	// 错误信息
	API_DTO_FIELD_DEFAULT(String, message, ZH_WORDS_GETTER("import.field.message"));
};

// 导入结果DTO
class ImportResultDTO : public oatpp::DTO {
	DTO_INIT(ImportResultDTO, DTO);
	// 总条数
	API_DTO_FIELD_DEFAULT(Int32, totalCount, ZH_WORDS_GETTER("import.field.totalCount"));
	// 成功条数
	API_DTO_FIELD_DEFAULT(Int32, successCount, ZH_WORDS_GETTER("import.field.successCount"));
	// 失败条数
	API_DTO_FIELD_DEFAULT(Int32, failCount, ZH_WORDS_GETTER("import.field.failCount"));
	// 错误详情
	API_DTO_FIELD_DEFAULT(List<Object<ImportErrorDTO>>, errors, ZH_WORDS_GETTER("import.field.errors"));
};

// 删除销售退货单 DTO
class DelSaleReturnDTO : public oatpp::DTO {
	DTO_INIT(DelSaleReturnDTO, DTO);

	// 退货单ID列表
	DTO_FIELD(List<String>, returnIds);
	DTO_FIELD_INFO(returnIds) {
		info->required = true;
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif 