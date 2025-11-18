#ifndef GOODSDTO_H
#define GOODSDTO_H
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)
class GoodsListDTO : public oatpp::DTO
{
	DTO_INIT(GoodsListDTO, DTO);
	//商品名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("goods.field.name"));
	//商品编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("goods.field.number"));
	//商品型号
	API_DTO_FIELD_DEFAULT(String, spec, ZH_WORDS_GETTER("goods.field.spec"));
	//商品类别
	API_DTO_FIELD_DEFAULT(String, category, ZH_WORDS_GETTER("goods.field.category"));
	//商品品牌
	API_DTO_FIELD_DEFAULT(String, brand, ZH_WORDS_GETTER("goods.field.brand"));
	//商品单位
	API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("goods.field.unit"));
	//商品条码
	API_DTO_FIELD_DEFAULT(String, code, ZH_WORDS_GETTER("goods.field.code"));
	//商品类型
	API_DTO_FIELD_DEFAULT(Int32, type, ZH_WORDS_GETTER("goods.field.type"));
	//备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("goods.field.data"));
};
//分页查询
class GoodsListPageDTO : public PageDTO<GoodsListDTO::Wrapper>
{
	DTO_INIT(GoodsListPageDTO, PageDTO<GoodsListDTO::Wrapper>);
	
};
//新增
class GoodsAddDTO : public oatpp::DTO
{
	DTO_INIT(GoodsAddDTO, DTO);
	//商品名称  
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("goods.field.name"));
	//拼音信息
	API_DTO_FIELD_DEFAULT(String, py, ZH_WORDS_GETTER("goods.field.py"));
	//商品编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("goods.field.number"));
	//商品型号
	API_DTO_FIELD_DEFAULT(String, spec, ZH_WORDS_GETTER("goods.field.spec"));
	//商品类别
	API_DTO_FIELD_DEFAULT(String, category, ZH_WORDS_GETTER("goods.field.category"));
	//商品品牌
	API_DTO_FIELD_DEFAULT(String, brand, ZH_WORDS_GETTER("goods.field.brand"));
	//商品单位
	API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("goods.field.unit"));
	//采购价格
	API_DTO_FIELD_DEFAULT(Float64, buy, ZH_WORDS_GETTER("goods.field.buy"));
	//销售价格
	API_DTO_FIELD_DEFAULT(Float64, sell, ZH_WORDS_GETTER("goods.field.sell"));
	//商品条码
	API_DTO_FIELD_DEFAULT(String, code, ZH_WORDS_GETTER("goods.field.code"));
	//商品货位
	API_DTO_FIELD_DEFAULT(String, location, ZH_WORDS_GETTER("goods.field.location"));
	//库存阈值
	API_DTO_FIELD_DEFAULT(Float64, stock, ZH_WORDS_GETTER("goods.field.stock"));
	//商品类型
	API_DTO_FIELD_DEFAULT(Int32, type, ZH_WORDS_GETTER("goods.field.type"));
	//备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("goods.field.data"));
	//商品图像
	API_DTO_FIELD_DEFAULT(String, imgs, ZH_WORDS_GETTER("goods.field.imgs"));
	//图文详细
	API_DTO_FIELD_DEFAULT(String, details, ZH_WORDS_GETTER("goods.field.details"));
	//多单位配置
	API_DTO_FIELD_DEFAULT(String, units, ZH_WORDS_GETTER("goods.field.units"));
	//折扣策略
	API_DTO_FIELD_DEFAULT(String, strategy, ZH_WORDS_GETTER("goods.field.strategy"));
	//序列产品
	API_DTO_FIELD_DEFAULT(Int32, serial, ZH_WORDS_GETTER("goods.field.serial"));
	//批次产品
	API_DTO_FIELD_DEFAULT(Int32, batch, ZH_WORDS_GETTER("goods.field.batch"));
	//有效期
	API_DTO_FIELD_DEFAULT(Int32, validity, ZH_WORDS_GETTER("goods.field.validity"));
	//保质期
	API_DTO_FIELD_DEFAULT(Int32, protect, ZH_WORDS_GETTER("goods.field.protect"));
	//预警阈值
	API_DTO_FIELD_DEFAULT(Int32, threshold, ZH_WORDS_GETTER("goods.field.threshold"));
	//扩展信息
	API_DTO_FIELD_DEFAULT(String, more, ZH_WORDS_GETTER("goods.field.more"));
};
//详情
class GoodsDetailDTO : public GoodsAddDTO
{
	DTO_INIT(GoodsDetailDTO, GoodsAddDTO);
	//商品ID
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("goods.field.id"));

};
//class GoodsSpecDTO : public oatpp::DTO {
//	DTO_INIT(GoodsSpecDTO, DTO);
//	API_DTO_FIELD_DEFAULT(Int32, id, ZH_WORDS_GETTER("goods.field.id"));
//	API_DTO_FIELD_DEFAULT(Int32, type, ZH_WORDS_GETTER("goods.field.type"));
//	API_DTO_FIELD_DEFAULT(String, code, ZH_WORDS_GETTER("goods.field.code"));
//	API_DTO_FIELD_DEFAULT(List<String>, specs, ZH_WORDS_GETTER("goods.field.spec"));
//};
class GoodsSpecItemDTO : public oatpp::DTO {
	DTO_INIT(GoodsSpecItemDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("goods.field.id"));
	API_DTO_FIELD_DEFAULT(Int32, type, ZH_WORDS_GETTER("goods.field.type"));
	API_DTO_FIELD_DEFAULT(String, code, ZH_WORDS_GETTER("goods.field.code"));
};

class GoodsSpecDTO : public oatpp::DTO {
	DTO_INIT(GoodsSpecDTO, DTO);
	API_DTO_FIELD_DEFAULT(List<GoodsSpecItemDTO::Wrapper>, specs, ZH_WORDS_GETTER("goods.field.spec"));
};

/**
 * 添加文件表单数据
 */
class FileAddFormDTO : public oatpp::DTO
{
	DTO_INIT(FileAddFormDTO, DTO);
	// 文件名
	API_DTO_FIELD_DEFAULT(String, filename, ZH_WORDS_GETTER("goodsfile.field.filename"));
	// 文件类型编码
	API_DTO_FIELD_REQUIRE(String, fileType, ZH_WORDS_GETTER("goodsfile.field.ft"), true);
	// 文件存储类型编码
	API_DTO_FIELD_REQUIRE(String, saveType, ZH_WORDS_GETTER("goodsfile.field.st"), true);
	// 备注
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("goodsfile.field.remark"));
};

/**
 * 添加文件数据模型
 */
class FileAddDTO : public FileAddFormDTO
{
	DTO_INIT(FileAddDTO, FileAddFormDTO);
	// 文件数据
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, file, ZH_WORDS_GETTER("goodsfile.field.file"), true);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_CUSTOMERDTO_H_