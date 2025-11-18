#pragma once

#ifndef _SORDO_H_
#define _SORDO_H_

#include "DoInclude.h"
#include "AnnexDO.h"

class SorDO : public BaseDO {
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, frame, Frame);
	MYSQL_SYNTHESIZE(string, customer, Customer);
	MYSQL_SYNTHESIZE(string, time, Time);
	MYSQL_SYNTHESIZE(string, number, Number);
	MYSQL_SYNTHESIZE(double, total, Total);
	MYSQL_SYNTHESIZE(double, actual, Actual);
	MYSQL_SYNTHESIZE(string, people, People);
	MYSQL_SYNTHESIZE(string, arrival, Arrival);
	MYSQL_SYNTHESIZE(string, logistics, Logistics);
	MYSQL_SYNTHESIZE(string, file, File);
	MYSQL_SYNTHESIZE(string, data, Data);
	MYSQL_SYNTHESIZE(string, more, More);
	MYSQL_SYNTHESIZE(int, examine, Examine);
	MYSQL_SYNTHESIZE(int, state, State);
	MYSQL_SYNTHESIZE(string, user, User);
	CC_SYNTHESIZE(PtrAnnexDO, annex, Annex);
	SorDO() : BaseDO("sor") {
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("frame", "s", frame, false);
		MYSQL_ADD_FIELD_NULLABLE("customer", "s", customer, false);
		MYSQL_ADD_FIELD_NULLABLE("`time`", "s", time, false);
		MYSQL_ADD_FIELD_NULLABLE("number", "s", number, false);
		MYSQL_ADD_FIELD_NULLABLE("total", "d", total, false);
		MYSQL_ADD_FIELD_NULLABLE("actual", "d", actual, false);
		MYSQL_ADD_FIELD_NULLABLE("people", "s", people, true);
		MYSQL_ADD_FIELD_NULLABLE("arrival", "s", arrival, false);
		MYSQL_ADD_FIELD_NULLABLE("logistics", "s", logistics, true);
		MYSQL_ADD_FIELD_NULLABLE("data", "s", this->data, true);
		MYSQL_ADD_FIELD_NULLABLE("more", "s", more, true);
		MYSQL_ADD_FIELD_NULLABLE("examine", "i", examine, false);
		MYSQL_ADD_FIELD_NULLABLE("state", "i", state, false);
		MYSQL_ADD_FIELD_NULLABLE("user", "s", user, false);
		MYSQL_ADD_FIELD_NULLABLE("file", "s", file, true);
	}
};

typedef std::shared_ptr<SorDO> PtrSorDO;

#endif