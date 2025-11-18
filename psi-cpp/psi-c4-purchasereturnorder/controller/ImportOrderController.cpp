#include"ImportOrderController.h"
#include "stdafx.h"
#include <iostream>

#include "ServerInfo.h"
#include "NacosClient.h"
#include "FastDfsClient.h"
#include "SimpleDateTimeFormat.h"
#include"../service/ImportOrderService.h"

// 文件下载地址前缀
#define DISK_FILE_SERVER_ADDR "http://127.0.0.1:"+ServerInfo::getInstance().getServerPort()+"/file/download?filename="

// 将保存文件到磁盘测试逻辑
#define SAVE_FILE_TO_DISK(file, newFileName) \
/* 获取文件后缀名 */ \
string filename = part##file->getFilename().getValue(""); \
string suffix = ""; \
size_t pos = filename.rfind("."); \
if (pos != string::npos) \
{ \
	suffix = filename.substr(pos + 1); \
} \
/* 将文件保存到磁盘上面 */ \
std::string newFileName = SimpleDateTimeFormat::formatWithMilli("%Y%m%d%H%M%S", "") + "." + suffix; \
string fullPath = "public/static/file/" + newFileName; \
file.saveToFile(fullPath.c_str())

ListJsonVO<String>::Wrapper ImportOrderController::execImportOne(std::shared_ptr<IncomingRequest> request)
{
	// 返回体
	auto jvo = ListJsonVO<String>::createShared();
	auto list = List<String>::createShared();

	// 1 初始化
	API_MULTIPART_INIT(container, reader);

	// 2 配置读取器
	API_MULTIPART_CONFIG_MEMO_DEFAULT(reader, -1);

	// 3 读取数据
	request->transferBody(&reader);

	/* 打印上传总部分数 */
	OATPP_LOGD("Multipart", "parts_count=%d", container->count());


	/* 获取文件数据 */
	API_MULTIPART_PARSE_FILE_FIELD(container, "file", file);

	if (!file)
	{// 读取失败
		list->push_back("Failed to read the file");
		jvo->fail(list);
		return jvo;
	}

	// 获取文件后缀名
	string pfn = partfile->getFilename().getValue("");
	string suffix = "";
	size_t pos = pfn.rfind(".");
	if (pos != string::npos)
		suffix = pfn.substr(pos + 1);

	if (suffix != "xlsx")
	{// 文件类型错误
		list->push_back("The file type is not xlsx");
		jvo->fail(list);
		return jvo;
	}

	// 调用service处理数据的导入
	ImportOrderService ser;
	auto vec_pr = ser.ImportData(file);

	for (const auto& pr : vec_pr)
	{
		list->push_back(pr.second);
	}

	jvo->success(list);
	return jvo;
}

