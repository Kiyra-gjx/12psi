#pragma once 

#ifndef _GETRETURNLISTDETAIL_H_ 
#define _GETRETURNLISTDETAIL_H_ 

#include "domain/query/PageQuery.h" 
#include "domain/GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO) 

/**
 * 采购退货单详情查询数据传输模型
 */
class getreturndetail : public PageQuery
{
	// 初始化 
	DTO_INIT(getreturndetail, PageQuery);
	// 编号 
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("purchasereturnorder.detail-field.id"));
	// 所属ID 
	API_DTO_FIELD_DEFAULT(String, pid, ZH_WORDS_GETTER("purchasereturnorder.detail-field.pid"));
	// 所属商品 
	API_DTO_FIELD_DEFAULT(String, source, ZH_WORDS_GETTER("purchasereturnorder.detail-field.source"));
	// 所属商品 
	API_DTO_FIELD_DEFAULT(String, goods, ZH_WORDS_GETTER("purchasereturnorder.detail-field.goods"));
	// 辅助属性 
	API_DTO_FIELD_DEFAULT(String, attr, ZH_WORDS_GETTER("purchasereturnorder.detail-field.attr"));
	// 单位 
	API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("purchasereturnorder.detail-field.unit"));
	// 仓库 
	API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("purchasereturnorder.detail-field.warehouse"));
	// 批次号 
	API_DTO_FIELD_DEFAULT(String, batch, ZH_WORDS_GETTER("purchasereturnorder.detail-field.batch"));
	// 生产日期 
	API_DTO_FIELD_DEFAULT(String, mfd, ZH_WORDS_GETTER("purchasereturnorder.detail-field.mfd"));
	// 单价 
	API_DTO_FIELD_DEFAULT(String, mfrd, ZH_WORDS_GETTER("purchasereturnorder.detail-field.mfrd"));
	// 数量 
	API_DTO_FIELD_DEFAULT(String, nums, ZH_WORDS_GETTER("purchasereturnorder.detail-field.nums"));
	// 序列号 
	API_DTO_FIELD_DEFAULT(String, serial, ZH_WORDS_GETTER("purchasereturnorder.detail-field.serial"));
	// 折扣 
	API_DTO_FIELD_DEFAULT(String, discount, ZH_WORDS_GETTER("purchasereturnorder.detail-field.discount"));
	// 折扣额 
	API_DTO_FIELD_DEFAULT(String, disc, ZH_WORDS_GETTER("purchasereturnorder.detail-field.disc"));
	// 金额 
	API_DTO_FIELD_DEFAULT(String, total, ZH_WORDS_GETTER("purchasereturnorder.detail-field.total"));
	// 税率 
	API_DTO_FIELD_DEFAULT(String, tax, ZH_WORDS_GETTER("purchasereturnorder.detail-field.tax"));
	// 税额 
	API_DTO_FIELD_DEFAULT(String, tpt, ZH_WORDS_GETTER("purchasereturnorder.detail-field.tpt"));
	// 备注信息 
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("purchasereturnorder.detail-field.data"));
};

#include OATPP_CODEGEN_END(DTO) 
#endif // !_GETRETURNLISTDETAIL_H_