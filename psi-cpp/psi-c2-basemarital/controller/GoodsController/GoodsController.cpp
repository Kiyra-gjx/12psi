 #include "stdafx.h"
#include "GoodsController.h"
#include "../../service/GoodsService/GoodsService.h"
#include "../ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
// FastDFS需要导入的头
#include "ServerInfo.h"
#include "NacosClient.h"
#include "FastDfsClient.h"


static bool is_goods_notnull(const GoodsAddDTO::Wrapper& dto) {
	return dto->name && dto->py && dto->number && dto->spec && dto->category && dto->brand
		&& dto->unit && dto->buy && dto->sell && dto->code && dto->location && dto->stock
		&& dto->type && dto->data && dto->imgs && dto->details && dto->units && dto->strategy
		&& dto->serial && dto->batch && dto->validity && dto->protect && dto->threshold && dto->more;
}

static bool is_goods_valid(const GoodsAddDTO::Wrapper& dto) {
	if (dto->name->empty() || dto->name->size() > 32) return false;
	if (dto->py->empty() || dto->py->size() > 32) return false;
	if (dto->number->empty() || dto->number->size() > 32) return false;
	if (dto->spec->size() > 32) return false;
	if (dto->category->empty() || dto->category->size() > 32) return false;
	if (dto->brand->size() > 32) return false;
	if (dto->unit->empty() || dto->unit->size() > 32) return false;
	if (dto->code->size() > 64) return false;
	if (dto->location->size() > 64) return false;
	if (dto->data->size() > 64) return false;
	if (dto->imgs->size() > 65535) return false;
	if (dto->details->size() > 65535) return false;
	if (dto->units->size() > 65535) return false;
	if (dto->strategy->size() > 65535) return false;
	if (dto->more->empty() || dto->unit->size() > 65535) return false;
	return true;
}

StringJsonVO::Wrapper GoodsController::executeAdd(const GoodsAddDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	// 非空校验
	if (!is_goods_notnull(dto)) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
	}
	// 有效值校验
	if (!is_goods_valid(dto)) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 服务
	GoodsService gs;
	// 执行新增商品
	auto id = gs.saveGoods(dto);
	if (id != "")
		jvo->success(id);
	else
		jvo->fail("Add goods failed");
	return jvo;
}

StringJsonVO::Wrapper GoodsController::executeModify(const GoodsDetailDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	// 非空校验
	if (!dto->id) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	if (!is_goods_notnull(dto)) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
	}
	// 有效值校验
	if (!is_goods_valid(dto)) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 服务
	GoodsService gs;
	// 执行修改商品
	if (gs.updateGoods(dto)) {
		jvo->success(dto->id);
	} else {
		jvo->fail(dto->id);
	}
	return jvo;
}

//删除商品（批量）
ListJsonVO<String>::Wrapper GoodsController::execRemoveGood(const List<String>& ids)
{
	//创建返回体
	auto jvo = ListJsonVO<String>::createShared();

	if (ids->empty()) {
		//如果传来的参数为空
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	//创建服务对象
	GoodsService service;

	//执行删除命令
	if (service.removeGoodsData(ids)) {
		//删除成功
		jvo->success(ids);
	}
	else {
		//没有全部删除就返回失败
		jvo->fail(ids);
	}

	return jvo;
}


//判断字符是否不符合长度
bool isStrOutRange(int minSize, int maxSize, const std::string& str) {
	return str.length() > maxSize || str.length() < minSize;
}

//判断是否全是大写
bool isNotAllSupper(const std::string& str) {
	try {
		if (str.empty()) return false;
		for (unsigned char i : str) {
			if (!std::isupper(i)) return true;
		}
		return false;
	}
	catch (...) {
		return true;
	}

}

//判断是否全是数字
bool isNotAllDigital(const std::string& str) {
	try {
		if (str.empty()) return false;
		for (auto i : str) {
			if (!std::isdigit(static_cast<unsigned char>(i))) return true;
		}
		return false;
	}
	catch (...) {
		return true;
	}

}

//判断是否是正数或0
bool isNegNumber(const std::string& str) {
	try {
		if (str.empty()) return false;
		double number = std::stod(str);
		return number < 0;
	}
	catch (...) {
		return true;
	}

}


//判断double decimal类型数据长度
bool isOutDecimalRange(int precision, int scale, const std::string& str) {
	try {
		size_t pos;
		double value = std::stod(str, &pos);

		// 检查是否完全转换
		if (pos != str.length()) return true;

		// 检查整数部分位数
		std::string integerPart = str.substr(0, str.find('.'));
		if (integerPart.length() > (precision - scale)) return true;

		// 检查小数部分位数
		size_t dotPos = str.find('.');
		if (dotPos != std::string::npos) {
			std::string decimalPart = str.substr(dotPos + 1);
			if (decimalPart.length() > scale) return true;
		}

		return false;
	}
	catch (...) {
		return true;
	}
}

StringJsonVO::Wrapper rResult(const StringJsonVO::Wrapper & jvo,const vector<vector<std::string>>& goodsV, int row, int col) {
	std::string result = "The row " + std::to_string(row) + " and col " + std::to_string(col) + " " + goodsV[0][col] + " is wrong!!";
	jvo->fail(result);
	return jvo;
}

//导入商品xlsx
StringJsonVO::Wrapper GoodsController::execUploadOne(const std::shared_ptr<IncomingRequest>& request) {
	//创建返回对象
	auto jvo = StringJsonVO::createShared();

	//1.创建读取xlsx的工具,并初始化
	API_MULTIPART_INIT(container, reader);

	//2.配置读取器
	API_MULTIPART_CONFIG_MEMO_DEFAULT(reader, -1);

	//3.读取数据
	request->transferBody(&reader);

	API_MULTIPART_PARSE_FILE_FIELD(container, "file", file);

	//将binary excel转为const char*
	/*auto str = *file.get()*/;
	auto str = file->data();
	std::string Result;
	vector<vector<std::string>> goodsV;

	if (file != nullptr) {
		const char* exceldata = str;
		size_t xlen = file->size();

		goodsV = ExcelComponent::readIntoVector(exceldata, xlen, ZH_WORDS_GETTER("goodsfile.download.summary"));

		int count = 1, row = 1, col = 0;

		//使用遍历两遍的方法
		//1.校验数据
		for (auto i : goodsV) {
			if (count == 1) {
				count++;
				continue;
			}
			col = 0;
			//商品名称
			if (i[col].empty() || isStrOutRange(1, 32, i[col])) {
				
				return jvo;
			}
			col++;
			//拼音信息
			if (i[col].empty() || isStrOutRange(1, 32, i[col]) || isNotAllSupper(i[col])) {
				return rResult(jvo, goodsV, row, col);
			}
			col++;
			//商品编号
			if (i[col].empty() || isStrOutRange(1, 32, i[col])) {
				return rResult(jvo, goodsV, row, col);
			}
			col++;
			//商品型号
			if (isStrOutRange(0, 32, i[col])) {
				return rResult(jvo, goodsV, row, col);
			}
			col++;
			//商品类别
			if (i[col].empty() || isStrOutRange(1, 32, i[col])) {
				return rResult(jvo, goodsV, row, col);
			}
			col++;
			//return col要减1！！！！！！！！！！！！！！！！！！
			//商品品牌
			if (isStrOutRange(0, 32, i[col])) {
				return rResult(jvo, goodsV, row, col);
			}
			col++;
			//商品单位
			if (isStrOutRange(1, 32, i[col])) {
				return rResult(jvo, goodsV, row, col);
			}
			col++;
			//商品条码
			if (isStrOutRange(0, 64, i[col])) {
				return rResult(jvo, goodsV, row, col);
			}
			col++;
			//采购价格 double(12,4)
			if (i[col].empty() || isNegNumber(i[col]) || isOutDecimalRange(8, 4, i[col])) {
				return rResult(jvo, goodsV, row, col);
			}
			col++;
			//销售价格 double(12,4)
			if (i[col].empty() || isNegNumber(i[col]) || isOutDecimalRange(8, 4, i[col])) {
				return rResult(jvo, goodsV, row, col);
			}
			col++;
			//库存阈值 double(12,4)
			if (i[col].empty() || isNegNumber(i[col]) || isOutDecimalRange(8, 4, i[col])) {
				return rResult(jvo, goodsV, row, col);
			}
			col++;
			//产品类型 tinyint(1)
			if (std::stoi(i[col]) != 1 && std::stoi(i[col]) != 0) {
				return rResult(jvo, goodsV, row, col);
			}
			col++;
			//more 更多信息
			if (i[col].empty() || isStrOutRange(1, 65535, i[col])) {
				return rResult(jvo, goodsV, row, col);
			}
			col++;
			row++;
		}

		//创建服务对象
		GoodsService service;
		//呼唤服务层保存文件信息到数据库,并接收返回值,判断是否返回成功
		Result = service.importExcelGoods(goodsV);
	}

	jvo->fail(Result);
	if (Result == "success")
		jvo->success("");

	return jvo;

};

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> GoodsController::execExportGoods(const GoodsQuery::Wrapper& query)
{
	// 定义一个Service
	GoodsService service;
	// 查询数据
	auto result = service.listAll(query);

	// 将数据写入到Excel中
	auto buff = ExcelComponent().writeVectorToBuff("goods",
		[result](ExcelComponent* ex) {
			// 写入表头
			ex->addHeader({
				ZH_WORDS_GETTER("goods.field.name") ,  //商品名称
				ZH_WORDS_GETTER("goods.field.number") ,  //商品编号
				ZH_WORDS_GETTER("goods.field.specification_model") , //规格型号
				ZH_WORDS_GETTER("goods.field.kinds"), //商品分类
				ZH_WORDS_GETTER("goods.field.brand") , //商品品牌
				ZH_WORDS_GETTER("goods.field.unit") ,  //商品单位
				ZH_WORDS_GETTER("goods.field.code") , //商品条码
				ZH_WORDS_GETTER("goods.field.type"),  //商品类型
				ZH_WORDS_GETTER("goods.field.comment") //备注信息
				});
			// 写入数据
			int row = 2;
			int col = 1;
			for (auto item : *(result->rows.get())) {
				col = 1;
				ex->setCellValue(row, col++, item->name);
				ex->setCellValue(row, col++, item->number);
				ex->setCellValue(row, col++, item->spec);
				ex->setCellValue(row, col++, item->category);
				ex->setCellValue(row, col++, item->brand);
				ex->setCellValue(row, col++, item->unit);
				ex->setCellValue(row, col++, item->code);
				ex->setCellValue(row, col++, std::to_string(item->type));
				ex->setCellValue(row, col, item->data);
				ex->setRowProperties(row++);
			}
		});

	// 组装下发数据
	const char* charData = reinterpret_cast<const char*>(buff.data());
	auto fstring = String(charData, buff.size());

	//// 测试将报表上传到fastdfs
	ZO_CREATE_DFS_CLIENT_URL(dfs, urlPrefix);
	string filepath = dfs.uploadFile(charData, buff.size(), "xlsx");
	// 打印文件上传成功后的下载地址
	string downloadUrl = urlPrefix + filepath;
	OATPP_LOGD("Multipart", "download url='%s'", downloadUrl.c_str());

	// 创建响应头
	auto response = createResponse(Status::CODE_200, fstring);

	// 设置响应头信息
	std::string filename = "rp-goods-" + SimpleDateTimeFormat::format() + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename=" + filename);
	response->putHeader(Header::CONTENT_TYPE, " application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");

	// 影响成功结果
	return response;
}

GoodsListPageJsonVO::Wrapper GoodsController::executeQueryAll(const GoodsQuery::Wrapper& query) {
	// 定义一个Service
	GoodsService service;
	// 查询数据
	auto result = service.listAll(query);
	// 响应结果
	auto jvo = GoodsListPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
	
}


GoodsDetailJsonVO::Wrapper GoodsController::executeQueryOne(const oatpp::String& id) {
	// 定义返回数据对象
	auto jvo = GoodsDetailJsonVO::createShared();

	// 参数校验
	// 非空校验
	if (!id)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 定义一个Service
	GoodsService service;
	// 执行数据新增
	auto res = service.getById(id.getValue({}));
	jvo->success(res);

	//响应结果
	return jvo;
}

GoodsSpecJsonVO::Wrapper GoodsController::executeGetSpecs(const GoodsQuery::Wrapper& query) {

	auto jvo = GoodsSpecJsonVO::createShared();
	GoodsService service;
	auto res = service.getSpec(query);
	jvo->success(res);
	return jvo;
}