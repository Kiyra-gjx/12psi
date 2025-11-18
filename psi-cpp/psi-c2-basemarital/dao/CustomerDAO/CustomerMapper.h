#ifndef _CUSTOMER_MAPPER_
#define _CUSTOMER_MAPPER_

#include "Mapper.h"
#include "../../domain/do/CustomerDO.h"

/**
 * 客户表字段匹配映射
 */
class CustomerMapper : public Mapper<CustomerDO>
{
public:
	CustomerDO mapper(ResultSet* result) const override
	{
		CustomerDO customer;
		customer.setId(result->getString("id"));
		customer.setName(result->getString("name"));
		customer.setPy(result->getString("py"));
		customer.setNumber(result->getString("number"));
		customer.setFrame(result->getString("frame"));
		customer.setUser(result->getString("user"));
		customer.setCategory(result->getString("category"));
		customer.setGrade(result->getString("grade"));
		customer.setBank(result->getString("bank"));
		customer.setAccount(result->getString("account"));
		customer.setTax(result->getString("tax"));
		customer.setData_(result->getString("data"));
		customer.setContacts(result->getString("contacts"));
		customer.setBalance(result->getDouble("balance"));
		customer.setMore(result->getString("more"));
		return customer;
	}
};

/**
 * 客户表字段匹配映射-创建智能指针对象
 */
class PtrCustomerMapper : public Mapper<CustomerDOPtr>
{
public:
	CustomerDOPtr mapper(ResultSet* result) const override
	{

		auto customer = std::make_shared<CustomerDO>();
		customer->setId(result->getString("id"));
		customer->setName(result->getString("name"));
		customer->setPy(result->getString("py"));
		customer->setNumber(result->getString("number"));
		customer->setFrame(result->getString("frame"));
		customer->setUser(result->getString("user"));
		customer->setCategory(result->getString("category"));
		customer->setGrade(result->getString("grade"));
		customer->setBank(result->getString("bank"));
		customer->setAccount(result->getString("account"));
		customer->setTax(result->getString("tax"));
		customer->setData_(result->getString("data"));
		customer->setContacts(result->getString("contacts"));
		customer->setBalance(result->getDouble("balance"));
		customer->setMore(result->getString("more"));
		
		
		return customer;
	}
};

#endif // !_SAMPLE_MAPPER_