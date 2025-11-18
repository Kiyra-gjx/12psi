#pragma once
#ifndef _RETURNORDERDTO_H_
#define _RETURNORDERDTO_H_
#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 采购退货单详情传输模型
 */
class returnorderDetailDTO : public oatpp::DTO {
	DTO_INIT(returnorderDetailDTO, DTO);

	// ID
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("returnorder.detail.id"));
	// pid 所属ID
	API_DTO_FIELD_DEFAULT(String, pid, ZH_WORDS_GETTER("returnorder.detail.pid"));
	// 关联详情|BUY
	API_DTO_FIELD_DEFAULT(String, source, ZH_WORDS_GETTER("returnorder.detail.source"));
	// 所属商品
	API_DTO_FIELD_DEFAULT(String, goods, ZH_WORDS_GETTER("returnorder.detail.goods"));
	// 辅助属性
	API_DTO_FIELD_DEFAULT(String, attr, ZH_WORDS_GETTER("returnorder.detail.attr"));
	// 单位
	API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("returnorder.detail.unit"));
	// 仓库
	API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("returnorder.detail.warehouse"));
	// 批次号
	API_DTO_FIELD_DEFAULT(String, batch, ZH_WORDS_GETTER("returnorder.detail.batch"));
	// 生产日期
	API_DTO_FIELD_DEFAULT(String, mfd, ZH_WORDS_GETTER("returnorder.detail.mfd"));
	// 单价
	API_DTO_FIELD_DEFAULT(Float64, price, ZH_WORDS_GETTER("returnorder.detail.price"));
	// 数量
	API_DTO_FIELD_DEFAULT(Float64, nums, ZH_WORDS_GETTER("returnorder.detail.nums"));
	// 序列号
	API_DTO_FIELD_DEFAULT(String, serial, ZH_WORDS_GETTER("returnorder.detail.serial"));
	// 折扣率
	API_DTO_FIELD_DEFAULT(Float64, discount, ZH_WORDS_GETTER("returnorder.detail.discount"));
	// 折扣额
	API_DTO_FIELD_DEFAULT(Float64, dsc, ZH_WORDS_GETTER("returnorder.detail.dsc"));
	// 金额
	API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("returnorder.detail.total"));
	// 税率
	API_DTO_FIELD_DEFAULT(Float64, tax, ZH_WORDS_GETTER("returnorder.detail.tax"));
	// 税额
	API_DTO_FIELD_DEFAULT(Float64, tat, ZH_WORDS_GETTER("returnorder.detail.tat"));
	// 价税合计
	API_DTO_FIELD_DEFAULT(Float64, tpt, ZH_WORDS_GETTER("returnorder.detail.tpt"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("returnorder.detail.data"));

};


#include OATPP_CODEGEN_END(DTO)

#endif // !_DINGDANDTO_H_
