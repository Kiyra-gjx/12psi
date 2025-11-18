#ifndef _CUSTOMERDAO_H
#define _CUSTOMERDAO_H

#include"CustomerMapper.h"
#include "domain/do/CustomerDO.h"
#include "domain/query/CustomerQuery/CustomerQuery.h"
#include <list>
#include"BaseDAO.h"

/**
 * 客户数据访问接口
 */
class CustomerDAO : public BaseDAO
{
private:
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    CustomerDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
	// Parameter:   const CustomerQuery::Wrapper& query 查询数据对象
	// Parameter:   SqlParams& params 存放查询数据的参数对象
	// Description: 查询条件构建器，根据CustomerQuery对象动态构建查询条件相关参数
	//************************************
	inline std::string queryConditionBuilder(const CustomerQuery::Wrapper& query, SqlParams& params);
public:
	/**
	 * 通过客户编号查询客户
	 * @param customerCode 客户编号
	 * @return 客户数据对象
	 */
	CustomerDO selectByCode(const string& customerCode);

	/**
	 * 插入客户数据
	 * @param data 客户数据
	 * @return 影响行数
	 */
	int insert(const CustomerDO& data);

	/**
	 * 更新客户数据
	 * @param data 客户数据
	 * @return 影响行数
	 */
	int modifyCustomer(const CustomerDO& data);

	/**
	 * 删除客户（支持批量）
	 * @param ids 客户id
	 * @return 影响行数
	 */
	int deleteCustomer(const list<string>& ids);


	/**
	 * 统计数据条数
	 * @param query 查询对象
	 * @return 客户表中数据的条数
	 */
	uint64_t count(const CustomerQuery::Wrapper& query);

	/**
	 * 分页查询数据
	 * @param query 查询对象
	 * @return 客户表中数据构成的列表
	 */
	std::list<CustomerDO> selectWithPage(const CustomerQuery::Wrapper& query);

	/**
	 * 分页按id查询数据
	 * @c2快乐五香蛋
	 * @param query 查询对象
	 * @return 客户表中数据构成的列表
	 */
	std::list<CustomerDO> execExport(const CustomerQuery::Wrapper& query);

};



#endif // !_CUSTOMERDAO_H