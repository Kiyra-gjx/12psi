#pragma once


// 实现一个 GBK 转 UTF-8 的方法
// 代码里不能直接使用中文

#include <string>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#else
#include <iconv.h>
#include <cstring>
#endif

// GBK转UTF-8（跨平台实现）
std::string gbk_to_utf8(const std::string& gbk_str);