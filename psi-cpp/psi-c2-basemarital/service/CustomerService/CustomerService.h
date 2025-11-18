
#ifndef _CUSTOMERSERVICE_H
#define _CUSTOMERSERVICE_H


#include "domain/dto/CustomerDTO/CustomerDTO.h"
#include "oatpp/web/mime/multipart/Part.hpp"
#include"domain/do/CustomerDO.h"
#include <memory>
#include"dao/CustomerDAO/CustomerDAO.h"
#include"domain/vo/CustomerVO/CustomerVO.h"
#include"domain/query/CustomerQuery/CustomerQuery.h"
using namespace oatpp::web::mime::multipart;

/**
 * 客户服务接口
 */
class CustomerService
{
public:
	/**
	 * 新增客户
	 * @param dto 客户信息
	 * @return 响应结果
	 */
	std::shared_ptr<CustomerAddResponseVO> addCustomer(const CustomerDTO::Wrapper& dto);

	/**
	 * 获取客户信息
	 * @param dto 查询条件
	 * @return 响应结果
	 */
	std::shared_ptr<CustomerGetResponseVO> getCustomerInfo(const CustomerGetDTO::Wrapper& dto);

	/**
	 * 修改客户
	 * @param dto 客户信息
	 * @return 修改的客户id
	 */

	std::string modifyCustomer(const CustomerModifyDTO::Wrapper& dto);
	/**
	 * 删除客户（支持批量）
	 * @param ids 客户id
	 * @return 删除行数
	 */
	uint64_t deleteCustomer(const oatpp::List<oatpp::String>& ids);

	/**
	* 获取客户列表
	* @param dto 客户信息
	* @return 响应结果
	 */
	CustomerListPageDTO::Wrapper listAll(const CustomerQuery::Wrapper& query);

	/**
	* 导入文件新增客户@c2-快乐五香蛋
	* @param datas excel表格的数据
	* @return 响应结果
	 */
	bool Import(const std::vector<std::vector<std::string>>& datas);
	/**
	* 导出客户文件@c2-快乐五香蛋
	* @param query 客户id
	* @return 响应结果
	 */
	CusFileAddFormFileDTO::Wrapper execExport(const CustomerQuery::Wrapper& query);
};




#endif // !_CUSTOMERSERVICE_H