#include"CustomerDAO.h"

inline std::string CustomerDAO::queryConditionBuilder(const CustomerQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->name) {

		sqlCondition << " AND name=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	if (query->number) {

		sqlCondition << " AND number=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->number.getValue(""));
	}
	if (query->category) {

		sqlCondition << " AND category=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->category.getValue(""));
	}
	if (query->grade) {

		sqlCondition << " AND grade=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->grade.getValue(""));
	}
	if (query->contact_person) {

		sqlCondition << " AND contact_person=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->contact_person.getValue(""));
	}
	if (query->telephone) {

		sqlCondition << " AND telephone=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->telephone.getValue(""));
	}
	if (query->username) {

		sqlCondition << " AND username=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->username.getValue(""));
	}
	if (query->memo) {

		sqlCondition << " AND memo=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->memo.getValue(""));
	}

	return sqlCondition.str();
}

CustomerDO CustomerDAO::selectByCode(const string& customerCode)
{
	string sql = "SELECT id,name, py,number, frame, user, category, grade, bank, "
		"account, tax, data, contacts,balance,more "
		"FROM customer WHERE `id` = ?";

	SqlSession sqlSession;

	return sqlSession.executeQueryOne<CustomerDO>(sql, CustomerMapper(), "%s", customerCode);



}

int CustomerDAO::insert(const CustomerDO& Data)
{
	string sql = "INSERT INTO customer(name, number, frame, user, "
		"category, grade, bank, account, tax, data, contacts ,py,more,id,balance"
		") VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";

	//根据number防止重复插入--》未完成

	//怎么添加拼音数据———》未完成

	SqlSession sqlSession;

#define GET_STR(a) string a = Data.get##a##Ptr() ? Data.get##a() : ""

	GET_STR(Id);
	GET_STR(Frame);
	GET_STR(User);
	GET_STR(Py);
	GET_STR(More);
	GET_STR(Name);
	GET_STR(Number);
	GET_STR(Category);
	GET_STR(Grade);
	GET_STR(Bank);
	GET_STR(Account);
	GET_STR(Tax);
	GET_STR(Data_);
	GET_STR(Contacts);

	auto balance = std::to_string(Data.getBalancePtr() ? Data.getBalance() : 0.0);
#undef GET_STR
	// 执行插入操作
	return sqlSession.executeUpdate(sql, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
		Name, Number, Frame, User,
		Category, Grade, Bank, Account,
		Tax, Data_, Contacts, Py, More, Id, balance);


}

int CustomerDAO::modifyCustomer(const CustomerDO& data)
{

	if (data.getId().empty())
	{
		return 0;
	}
	string sql = "UPDATE customer SET";
	SqlParams params;
	string delete_param;
	if (data.getNamePtr())
	{
		delete_param.append(" name = ?,");
		SQLPARAMS_PUSH(params, "s", string, data.getName());
	}
	if (data.getPyPtr())
	{
		delete_param.append(" py = ?,");
		SQLPARAMS_PUSH(params, "s", string, data.getPy());
	}
	if (data.getNumberPtr())
	{
		delete_param.append(" number = ?,");
		SQLPARAMS_PUSH(params, "s", string, data.getNumber());
	}
	if (data.getFramePtr())
	{
		delete_param.append(" frame = ?,");
		SQLPARAMS_PUSH(params, "s", string, data.getFrame());
	}
	if (data.getUserPtr())
	{
		delete_param.append(" user = ?,");
		SQLPARAMS_PUSH(params, "s", string, data.getUser());
	}
	if (data.getCategoryPtr())
	{
		delete_param.append(" category = ?,");
		SQLPARAMS_PUSH(params, "s", string, data.getCategory());
	}
	if (data.getGradePtr())
	{
		delete_param.append(" grade = ?,");
		SQLPARAMS_PUSH(params, "s", string, data.getGrade());
	}
	if (data.getBankPtr())
	{
		delete_param.append(" bank = ?,");
		SQLPARAMS_PUSH(params, "s", string, data.getBank());
	}
	if (data.getAccountPtr())
	{
		delete_param.append(" account = ?,");
		SQLPARAMS_PUSH(params, "s", string, data.getAccount());
	}
	if (data.getTaxPtr())
	{
		delete_param.append(" tax = ?,");
		SQLPARAMS_PUSH(params, "s", string, data.getTax());
	}
	if (data.getData_Ptr())
	{
		delete_param.append(" data = ?,");
		SQLPARAMS_PUSH(params, "s", string, data.getData_());
	}
	if (data.getContactsPtr())
	{
		delete_param.append(" contacts = ?,");
		SQLPARAMS_PUSH(params, "s", string, data.getContacts());
	}
	if (data.getBalancePtr())
	{
		delete_param.append(" balance = ?,");
		SQLPARAMS_PUSH(params, "d", double, data.getBalance());
	}
	if (data.getMorePtr())
	{
		delete_param.append(" more = ?,");
		SQLPARAMS_PUSH(params, "s", string, data.getMore());
	}

	delete_param.empty() ? void() : delete_param.pop_back();
	sql = sql + delete_param;
	sql += " WHERE id = ?";
	SQLPARAMS_PUSH(params, "s", string, data.getId());
	return sqlSession->executeUpdate(sql, params);
}


int CustomerDAO::deleteCustomer(const list<string>& ids)
{
	if (ids.size() == 0)
	{
		return 0;
	}
	string sql = "DELETE FROM customer WHERE id IN ";
	string delete_customer = "(";
	SqlParams params;
	for (const auto& id : ids)
	{
		delete_customer.append(" ?,");
		SQLPARAMS_PUSH(params, "s", string, id);

	}
	ids.empty() ? void() : delete_customer.pop_back();
	delete_customer.append(" )");
	sql = sql + delete_customer;
	return sqlSession->executeUpdate(sql, params);
}

uint64_t CustomerDAO::count(const CustomerQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM customer ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<CustomerDO> CustomerDAO::selectWithPage(const CustomerQuery::Wrapper& query)
{
	SqlParams params;
	//属性 "客户积分" 没找到对应//
	string sql = "SELECT id,name,py,number,frame,user,category,grade,bank,account,tax,data,contacts,balance,more FROM customer "; 
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建排序语句
	// sql += " ORDER BY IFNULL(`update_time`, `create_time`) DESC, `id` DESC ";
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	return sqlSession->executeQuery<CustomerDO>(sql, CustomerMapper(), params);
}

//c2-快乐五香蛋
std::list<CustomerDO> CustomerDAO::execExport(const CustomerQuery::Wrapper& query)
{
	SqlParams params;
	//属性 "客户积分" 没找到对应//
	string sql = "SELECT id,name,py,number,frame,user,category,grade,bank,account,tax,data,contacts,balance,more FROM customer ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建排序语句
	// sql += " ORDER BY IFNULL(`update_time`, `create_time`) DESC, `id` DESC ";
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	return sqlSession->executeQuery<CustomerDO>(sql, CustomerMapper(), params);
}
