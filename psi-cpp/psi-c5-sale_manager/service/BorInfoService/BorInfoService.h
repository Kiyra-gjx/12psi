#pragma once
#ifndef _BORINFO_SERVICE_
#define _BORINFO_SERVICE_

#include "domain/do/BorInfoDO.h"

class BorInfoService
{
public:
	// 查找指定的数据
	PtrBorInfoDO queryByPid(const string& pid);
};

#endif // !_BORINFO_SERVICE_
