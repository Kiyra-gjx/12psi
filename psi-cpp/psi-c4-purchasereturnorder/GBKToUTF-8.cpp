#include "GBKToUTF-8.h"

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
std::string gbk_to_utf8(const std::string& gbk_str) {
#ifdef _WIN32
	// Windows平台：使用WideCharToMultiByte
	// 1. GBK转宽字符（UTF-16）
	int wcs_len = MultiByteToWideChar(CP_ACP, 0, gbk_str.c_str(), -1, nullptr, 0);
	if (wcs_len <= 0) return "";

	wchar_t* wcs_buf = new wchar_t[wcs_len];
	MultiByteToWideChar(CP_ACP, 0, gbk_str.c_str(), -1, wcs_buf, wcs_len);

	// 2. 宽字符转UTF-8
	int utf8_len = WideCharToMultiByte(CP_UTF8, 0, wcs_buf, -1, nullptr, 0, nullptr, nullptr);
	if (utf8_len <= 0) {
		delete[] wcs_buf;
		return "";
	}

	char* utf8_buf = new char[utf8_len];
	WideCharToMultiByte(CP_UTF8, 0, wcs_buf, -1, utf8_buf, utf8_len, nullptr, nullptr);

	std::string utf8_str(utf8_buf);
	delete[] wcs_buf;
	delete[] utf8_buf;
	return utf8_str;
#else
	// Linux平台：使用iconv库
	iconv_t cd = iconv_open("UTF-8", "GBK");
	if (cd == (iconv_t)-1) return "";

	const char* in_buf = gbk_str.c_str();
	size_t in_len = gbk_str.size();
	size_t out_len = in_len * 4; // 预留足够空间（UTF-8最多4字节/字符）
	char* out_buf = new char[out_len];
	char* out_ptr = out_buf;

	// 执行转换
	if (iconv(cd, const_cast<char**>(&in_buf), &in_len, &out_ptr, &out_len) == (size_t)-1) {
		delete[] out_buf;
		iconv_close(cd);
		return "";
	}

	std::string utf8_str(out_buf, out_ptr - out_buf);
	delete[] out_buf;
	iconv_close(cd);
	return utf8_str;
#endif
}