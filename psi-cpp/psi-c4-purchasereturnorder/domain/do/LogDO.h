#pragma once

#ifndef _LOG_DO_
#define _LOG_DO_
#include "DoInclude.h"
#include "../../lib-common/include/id/UuidFacade.h"

/**
 * 操作日志数据库实体类
 */
class LogDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 操作时间
	MYSQL_SYNTHESIZE(string, time, Time);
	// 所属用户
	MYSQL_SYNTHESIZE(string, user, User);
	// 操作内容
	MYSQL_SYNTHESIZE(string, info, Info);

public:
	LogDO() : BaseDO("log")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("time", "s", time);
		MYSQL_ADD_FIELD("user", "s", user);
		MYSQL_ADD_FIELD("info", "s", info);
	}

	// 获取指定格式的当前时间
	static std::string format(const std::string& fmt = "%Y-%m-%d %H:%M:%S")
	{
		// 获取当前时间
		auto now = std::chrono::system_clock::now();

		// 格式时间
		std::stringstream ss;
		auto tNow = std::chrono::system_clock::to_time_t(now);
		ss << std::put_time(std::localtime(&tNow), fmt.c_str());
		return ss.str();
	}

	// 记录日志
	// data 日志内容，需手动转成UTF-8编码
	// user 创建者
	static bool write_log(const std::string data, const std::string user)
	{
		LogDO LogData;
		// 生成ID
		UuidFacade uf;
		LogData.setId(uf.genUuid());
		// 设置创建者
		LogData.setUser(user);
		// 设置创建时间
		LogData.setTime(LogDO::format());

		// 设置日志内容
		LogData.setInfo(data);

		BaseDAO dao;
		return dao.insert(LogData);
	}
};

// 给LogDO智能指针设定一个别名方便使用
typedef std::shared_ptr<LogDO> PtrLogDO;
#endif // !_LOG_DO_