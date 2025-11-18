#include "stdafx.h"
#include "ExamineController.h"
#include"../service/ExamineService.h"
#include <algorithm> // 包含 std::all_of
#include <cctype>

StringJsonVO::Wrapper ExamineController::execExamine(const ExamineDTO::Wrapper& dto)
{
	// 定义返回值
	auto jvo = StringJsonVO::createShared();

	// 参数校验
	// 非空校验
	if (!dto->id || !dto->source)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 有效值校验

	// 检查是否只包含字母和数字的函数
	auto check = [&](const string& s)
		{
			return std::all_of(s.begin(), s.end(), [](const char& c) {
				return std::isalnum(static_cast<unsigned char>(c));
				});
		};

	if (!check(dto->id) || !check(dto->source))
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}


	// 定义执行service
	ExamineService ser;
	auto is_pair = ser.examineOrder(dto);

	// 构建响应正文
	string res = "id:" + dto->id;


	// 执行处理
	if (is_pair.first == 0)
	{// 处理失败
		res += "," + is_pair.second;
		jvo->fail(res);
	}
	else
	{
		jvo->success(res);
	}


	return jvo;
}

