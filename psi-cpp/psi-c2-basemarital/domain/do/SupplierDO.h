#ifndef SUPPLIERDO_H
#define SUPPLIERDO_H
#include "DoInclude.h"

class SupplierDO : public BaseDO
{
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(string, py, Py);
	MYSQL_SYNTHESIZE(string, number, Number);
	MYSQL_SYNTHESIZE(string, frame, Frame);
	MYSQL_SYNTHESIZE(string, user, User);
	MYSQL_SYNTHESIZE(string, category, Category);
	MYSQL_SYNTHESIZE(double, rate, Rate);
	MYSQL_SYNTHESIZE(string, bank, Bank);
	MYSQL_SYNTHESIZE(string, account, Account);
	MYSQL_SYNTHESIZE(string, tax, Tax);
	MYSQL_SYNTHESIZE(string, data, Data);
	MYSQL_SYNTHESIZE(string, contacts, Contacts);
	MYSQL_SYNTHESIZE(double, balance, Balance);
	MYSQL_SYNTHESIZE(string, more, More);

public:
	SupplierDO() : BaseDO("supplier")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
		MYSQL_ADD_FIELD_NULLABLE("py", "s", py, false);
		MYSQL_ADD_FIELD_NULLABLE("number", "s", number, false);
		MYSQL_ADD_FIELD_NULLABLE("frame", "s", frame, false);
		MYSQL_ADD_FIELD_NULLABLE("user", "s", user, false);
		MYSQL_ADD_FIELD_NULLABLE("category", "s", category, false);
		MYSQL_ADD_FIELD_NULLABLE("rate", "d", rate, false);
		MYSQL_ADD_FIELD("bank", "s", bank);
		MYSQL_ADD_FIELD("account", "s", account);
		MYSQL_ADD_FIELD("tax", "s", tax);
		MYSQL_ADD_FIELD("data", "s", this->data);
		MYSQL_ADD_FIELD("contacts", "s", contacts);
		MYSQL_ADD_FIELD("balance", "d", balance);
		MYSQL_ADD_FIELD("more", "s", more);
	}

};

typedef std::shared_ptr<SupplierDO> PtrSupplierDO;

#endif // !SUPPLIERDO_H