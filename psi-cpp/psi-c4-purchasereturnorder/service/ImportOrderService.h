#pragma once

#ifndef _FILESERVICE_H_
#define _FILESERVICE_H_
#include "../domain/dto/ImportDTO.h"
#include"domain/do/BreInfoDO.h"
#include"domain/do/getreturnlistDO.h"

/**
 * 导入文件业务操作类
 */
class ImportOrderService
{
	// 处理单据信息
	bool setBreDO(vector<string>& cnt, BreDO& BreData, string& id);

	// 处理商品信息
	bool setBreInfoDO(const vector<string>& cnt, BreInfoDO& BreInfoData, const string& pid);
public:
	// 导入数据
	vector<pair<bool, string>> ImportData(oatpp::String file);
};

#endif // !_FILESERVICE_H_