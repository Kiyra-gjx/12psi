#include "stdafx.h"
#include "dao/CustomerDAO/CustomerDAO.h"
#include "CustomerService.h"
#include "id/UuidFacade.h"
#include <string>
std::shared_ptr<CustomerAddResponseVO> CustomerService::addCustomer(const CustomerDTO::Wrapper& dto)
{
	CustomerDO _do;
	ZO_STAR_DOMAIN_DTO_TO_DO(_do, dto, Name, name, Number, number, Frame, frame, User, user, Category, category, Grade, grade, Bank, bank, Account, account, Tax, tax, Data_, data_, Py, py, Balance, balance, More, more, Contacts, contacts);

	CustomerDAO dao;

	UuidFacade u(1);
	auto id = u.genUuid();
	_do.setId(id);

	dao.insert(_do);

	auto res = std::make_shared<CustomerAddResponseVO>();


	return {};
}

std::string CustomerService::modifyCustomer(const CustomerModifyDTO::Wrapper& dto)
{
	CustomerDO cus_do;
	CustomerDAO cus_dao;
	ZO_STAR_DOMAIN_DTO_TO_DO(cus_do, dto, Id, id, Name, name, Number, number, Frame, frame, User, user, Category, category, Grade, grade, Bank, bank, Account, account, Tax, tax, Data_, data, Py, py, Balance, balance, More, more, Contacts, contacts)
		int modify_rows = cus_dao.modifyCustomer(cus_do);
	if (modify_rows > 0)
	{
		return cus_do.getId();
	}
	return {};
}

uint64_t CustomerService::deleteCustomer(const oatpp::List<oatpp::String>& ids)
{
	CustomerDAO cus_dao;
	list<string> id_map;
	for (auto it{ ids->begin() }; it != ids->end(); ++it)
	{
		id_map.push_back(it->getValue(""));
	}
	//删除无效id
	id_map.remove_if([=](const string& s)-> bool
		{
			return s.empty();
		});
	return cus_dao.deleteCustomer(id_map);

}

std::shared_ptr<CustomerGetResponseVO> CustomerService::getCustomerInfo(const CustomerGetDTO::Wrapper& dto)
{
	auto res = std::make_shared<CustomerGetResponseVO>();

	res->data = CustomerGetResponseDTO::createShared();

	CustomerDAO dao;

	string id_ = dto->id;

	CustomerDO _do = dao.selectByCode(id_);

	if (_do.getIdPtr() == nullptr)
	{
		return res;
	}

	ZO_STAR_DOMAIN_DO_TO_DTO(res->data, _do, id, Id, name, Name, number, Number, frame, Frame, user, User, category, Category, grade, Grade, bank, Bank, account, Account, tax, Tax, data_, Data_, contacts, Contacts, py, Py, balance, Balance, more, More);

	return res;
}

CustomerListPageDTO::Wrapper CustomerService::listAll(const CustomerQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = CustomerListPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	CustomerDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<CustomerDO> result = dao.selectWithPage(query);
	// 将DO转换成DTO
	for (CustomerDO& sub : result)
	{
		auto dto = CustomerListDTO::createShared();
		dto->balance = std::to_string(sub.getBalance());  //balance需要把double类型转为string
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, number, Number, name, Name, category, Category, grade, Grade, frame, Frame, user, User, data_, Data_);
		pages->addData(dto);
	}
	return pages;
}

//c2-快乐五香蛋
CusFileAddFormFileDTO::Wrapper CustomerService::execExport(const CustomerQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = CusFileAddFormFileDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	CustomerDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<CustomerDO> result = dao.execExport(query);
	// 将DO转换成DTO
	for (CustomerDO& sub : result)
	{
		auto dto = CustomerAddDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, number, Number, name, Name, category, Category, grade,Grade,bank,Bank,account,Account,tax,Tax,frame, Frame, data, Data_, balance,Balance,user,User,contacts,Contacts);
		pages->addData(dto);
	}
	return pages;
}

//c2-快乐五香蛋，将解析后的导入文件插入数据库
bool CustomerService::Import(const std::vector<std::vector<std::string>>& datas)
{
	//客户如果在文件没有输入一条完整的客户信息就取消导入
	if (datas.size() < 3)
	{
		return false;
	}
	CustomerDAO customerDAO;
	bool status = true;
	for (int i=2;i<datas.size();i++)
	{
			CustomerDO CustomerDo;
			int j = 0;
			UuidFacade uf;
			CustomerDo.setId(uf.genUuid());
			CustomerDo.setName(datas[i][j++]);
			CustomerDo.setNumber(datas[i][j++]);
			CustomerDo.setFrame(datas[i][j++]);
			CustomerDo.setCategory(datas[i][j++]);
			CustomerDo.setGrade(datas[i][j++]);
			CustomerDo.setBank(datas[i][j++]);
			CustomerDo.setAccount(datas[i][j++]);
			CustomerDo.setTax(datas[i][j++]);
			CustomerDo.setData_(datas[i][j++]);
			string contactsPeople = datas[i][j++]; string contactsNumber = datas[i][j++];
			string Address = datas[i][j++]; string Remark = datas[i][j];
			//[{"联系人员":"某经理", "联系号码" : "00000000000", "联系地址" : "某某市", "备注信息" : "批量导入"}]
			string json = "[{\"contactsPeople\":\"" + contactsPeople + "\",\"contactsNumber\":\"" + contactsNumber + "\",\"contactsNumber\":\"" + Address + "\",\"Remark\":\"" + Remark + "\"}]";
			CustomerDo.setContacts(json);
			CustomerDo.setPy("NULL");
			CustomerDo.setUser("NULL");

			if (!customerDAO.BaseDAO::insert(CustomerDo))
			{
				return false;
			}
		
	}
	return status;
}
