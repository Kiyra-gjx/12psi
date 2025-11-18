#pragma once
#ifndef _BARCODE_DO_
#define _BARCODE_DO_
#include "../DoInclude.h"

class BarcodeDO : public BaseDO
{
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(v_int64, type, Type);
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(string, content, Content);
	MYSQL_SYNTHESIZE(string, notes, Notes);
public:
	BarcodeDO() : BaseDO("barcode")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("type", "i", type);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("content", "s", content);
		MYSQL_ADD_FIELD("notes", "s", notes);
	}
};
using PtrBarcodeDO = std::shared_ptr<BarcodeDO>;
#endif