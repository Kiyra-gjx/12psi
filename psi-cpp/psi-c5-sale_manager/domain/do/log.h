#pragma once
#ifndef _LOGDO_H_
#define _LOGDO_H_
#include "DoInclude.h"
class LogDO :public BaseDO
{
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, user, User);
	MYSQL_SYNTHESIZE(string, time, Time);
	MYSQL_SYNTHESIZE(string, info, Info);
public:
	LogDO() :BaseDO("sample_address") {
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("user", "s", user);
		MYSQL_ADD_FIELD("datetime", "s", time);
		MYSQL_ADD_FIELD("info", "s", info);
	}
};
//定义一个智能指针别名方便使用
typedef std::shared_ptr<LogDO>  PtrlogDO;
#endif