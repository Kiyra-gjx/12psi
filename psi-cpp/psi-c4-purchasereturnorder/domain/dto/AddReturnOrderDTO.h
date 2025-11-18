#ifndef _ADDRETURNORDERDTO_H_
#define _ADDRETURNORDERDTO_H_

#include "../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 采购退货单 - 新增DTO
 */
class AddReturnOrderDTO : public oatpp::DTO {
	DTO_INIT(AddReturnOrderDTO, DTO)

		// 主键ID
		API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("xin.bre.id"));

	// 关联单据（如采购单）
	API_DTO_FIELD_DEFAULT(String, source, ZH_WORDS_GETTER("xin.bre.source"));

	// 所属组织
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("xin.bre.frame"));

	// 供应商
	API_DTO_FIELD_DEFAULT(String, supplier, ZH_WORDS_GETTER("xin.bre.supplier"));

	// 单据时间
	API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("xin.bre.time"));

	// 单据编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("xin.bre.number"));

	// 单据金额
	API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("xin.bre.total"));

	// 实际金额
	API_DTO_FIELD_DEFAULT(Float64, actual, ZH_WORDS_GETTER("xin.bre.actual"));

	// 实收金额
	API_DTO_FIELD_DEFAULT(Float64, money, ZH_WORDS_GETTER("xin.bre.money"));

	// 单据费用
	API_DTO_FIELD_DEFAULT(Float64, cost, ZH_WORDS_GETTER("xin.bre.cost"));

	// 结算账户
	API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("xin.bre.account"));

	// 关联人员
	API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("xin.bre.people"));

	// 物流信息（JSON字符串）
	API_DTO_FIELD_DEFAULT(String, logistics, ZH_WORDS_GETTER("xin.bre.logistics"));

	// 单据附件（JSON字符串）
	API_DTO_FIELD_DEFAULT(String, file, ZH_WORDS_GETTER("xin.bre.file"));

	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("xin.bre.data"));

	// 扩展信息（JSON字符串）
	API_DTO_FIELD_DEFAULT(String, more, ZH_WORDS_GETTER("xin.bre.more"));

	// 审核状态 [0:未审核|1:已审核]
	API_DTO_FIELD_DEFAULT(Int8, examine, ZH_WORDS_GETTER("xin.bre.examine"));

	// 核销状态 [0:未核销|1:部分核销|2:已核销]
	API_DTO_FIELD_DEFAULT(Int8, nucleus, ZH_WORDS_GETTER("xin.bre.nucleus"));

	// 费用状态 [0:未结算|1:部分结算|2:已结算|3:无需结算]
	API_DTO_FIELD_DEFAULT(Int8, cse, ZH_WORDS_GETTER("xin.bre.cse"));

	// 发票状态 [0:未开票|1:部分开票|2:已开票|3:无需开具]
	API_DTO_FIELD_DEFAULT(Int8, invoice, ZH_WORDS_GETTER("xin.bre.invoice"));

	// 核对状态 [0:未核对|1:已核对]
	API_DTO_FIELD_DEFAULT(Int8, check, ZH_WORDS_GETTER("xin.bre.check"));

	// 制单人
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("xin.bre.user"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // _ADDRETURNORDERDTO_H_