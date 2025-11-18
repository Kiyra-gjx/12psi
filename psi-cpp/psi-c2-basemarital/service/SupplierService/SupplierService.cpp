#include "SupplierService.h"
#include "../../dao/SupplierDAO/SupplierDAO.h" 
#include "id/UuidFacade.h"


SupplierListPageDTO::Wrapper SupplierService::listSuppliers(const SupplierQuery::Wrapper& query)
{
	// 构建返回分页对象
	auto pages = SupplierListPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询总数
	SupplierDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询
	pages->total = count;
	pages->calcPages();
	std::list<SupplierDO> result = dao.selectWithPage(query);

	// DO -> DTO
	//for (auto& sub : result)
	//{
	//	auto dto = SupplierDTO::createShared();
	//	ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
	//		id, Id,
	//		name, Name,
	//		category, Category,
	//		rate, Rate,
	//		bank, Bank,
	//		account, Account,
	//		tax, Tax,
	//		balance, Balance,
	//		frame, Frame,
	//		user, User,
	//		data, Data,
	//		contacts, Contacts
	//	);
	//	pages->addData(dto);
	//}
	for (auto& sub : result)
	{
		auto dto = SupplierListDTO::createShared();
		dto->id = sub.getId();
		dto->name = sub.getName();
		dto->category = sub.getCategory();
		dto->rate = sub.getRate();   // 如果是double
		dto->bank = sub.getBank();
		dto->account = sub.getAccount();
		dto->tax = sub.getTax();
		dto->balance = sub.getBalance(); // 如果是double
		dto->frame = sub.getFrame();
		dto->user = sub.getUser();
		dto->data = sub.getData();
		dto->contacts = sub.getContacts();

		pages->addData(dto);
	}
	return pages;
}

SupplierDetailDTO::Wrapper SupplierService::getSupplierDetail(const oatpp::String& names)
{
   auto dto = SupplierDetailDTO::createShared();
   SupplierDAO dao;
   auto doptr = dao.selectByName(names);
   if (!doptr)
	   return nullptr;
   ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, doptr, id, Id, name, Name, py, Py, number, Number,
	   frame, Frame, user, User, category, Category, rate, Rate, bank, Bank, account, Account,
	   tax, Tax, data, Data, contacts, Contacts, balance, Balance, more, More);
   return dto;
}

bool SupplierService::Import(std::list<SupplierDTO>& dtos)  
{  
	 SupplierDAO dao;  
	 for (auto& dto : dtos)  
	 {  
		 SupplierDO sdo;  
		 if (dto.id) sdo.setId(dto.id.getValue({}));  
		 if (dto.name) sdo.setName(dto.name.getValue({}));  
		 if (dto.py) sdo.setPy(dto.py.getValue({}));  
		 if (dto.number) sdo.setNumber(dto.number.getValue({}));  
		 if (dto.frame) sdo.setFrame(dto.frame.getValue({}));  
		 if (dto.user) sdo.setUser(dto.user.getValue({}));  
		 if (dto.category) sdo.setCategory(dto.category.getValue({}));  
		 if (dto.rate) sdo.setRate(dto.rate.getValue({}));  
		 if (dto.bank) sdo.setBank(dto.bank.getValue({}));  
		 if (dto.account) sdo.setAccount(dto.account.getValue({}));  
		 if (dto.tax) sdo.setTax(dto.tax.getValue({}));  
		 if (dto.data) sdo.setData(dto.data.getValue({}));  
		 if (dto.contacts) sdo.setContacts(dto.contacts.getValue({}));  
		 if (dto.balance) sdo.setBalance(dto.balance.getValue({}));  
		 if (dto.more) sdo.setMore(dto.more.getValue({}));  
		 dao.insert(sdo);  
	 }  
	return true;  
}
//
//
std::string SupplierService::saveSupplier(const SupplierAddDTO::Wrapper& dto)
{
	// 生成uuid
	UuidFacade uf;
	auto id = uf.genUuid();

	// dto 转换成do
	SupplierDO sdo;

	sdo.setId(id);

	// 先给一个空串

	if (dto->name) sdo.setName(dto->name.getValue({}));
	if (dto->py) sdo.setPy(dto->name.getValue({}));
	if (dto->number) sdo.setNumber(dto->number.getValue({}));

	if (dto->frame) sdo.setFrame(to_string(dto->frame.getValue({})));
	if (dto->user) sdo.setUser(to_string(dto->user.getValue({})));

	if (dto->category) sdo.setCategory(dto->category.getValue({}));
	if (dto->rate) sdo.setRate(dto->rate.getValue({}));
	if (dto->bank) sdo.setBank(dto->bank.getValue({}));
	if (dto->account) sdo.setAccount(dto->account.getValue({}));
	if (dto->tax) sdo.setTax(dto->tax.getValue({}));
	if (dto->data) sdo.setData(dto->data.getValue({}));
	if (dto->contacts) sdo.setContacts(dto->contacts.getValue({}));
	// 保存数据
	SupplierDAO sd;
	if (sd.insert(sdo)) return id;
	return "";
}

bool SupplierService::updateSupplier(const SupplierUpdateDTO::Wrapper& dto)
{
	SupplierDO sdo;

	if (dto->id) sdo.setId(dto->id.getValue({}));

	// 更新数据
	if (dto->name) sdo.setName(dto->name.getValue({}));
	if (dto->py) sdo.setPy(dto->py.getValue({}));
	if (dto->number) sdo.setNumber(dto->number.getValue({}));

	if (dto->frame) sdo.setFrame(to_string(dto->frame.getValue({})));
	if (dto->user) sdo.setUser(to_string(dto->user.getValue({})));

	if (dto->category) sdo.setCategory(dto->category.getValue({}));
	if (dto->rate) sdo.setRate(dto->rate.getValue({}));
	if (dto->bank) sdo.setBank(dto->bank.getValue({}));
	if (dto->account) sdo.setAccount(dto->account.getValue({}));
	if (dto->tax) sdo.setTax(dto->tax.getValue({}));
	if (dto->data) sdo.setData(dto->data.getValue({}));
	if (dto->contacts) sdo.setContacts(dto->contacts.getValue({}));

	// 保存数据
	SupplierDAO sd;
	if (sd.update(sdo) >= 0) return true;
	return false;
}

bool SupplierService::removeData(const oatpp::List<oatpp::String>& ids)
{
	SupplierDAO dao;
	std::list<std::string> datas;
	for (auto one : *ids.get())
		datas.emplace_back(one.getValue({}));
	int rows = dao.deleteByIds<SupplierDO>(datas);
	if (rows == ids->size())
		return true;
	return false;
}

SupplierPageDTO::Wrapper SupplierService::listAll(const SupplierQuery::Wrapper& query)
{
	//构建返回对象  
	auto pages = SupplierPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	//查询数据总条数  
	SupplierDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	//分页查询数据  
	pages->total = count;
	pages->calcPages();
	list<SupplierDO> result = dao.selectWithPage(query);
	//将DO转换为DTO  
	for (SupplierDO& sub : result)
	{
		auto dto = SupplierDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id, name, Name, py, Py, number, Number,
			frame, Frame, user, User, category, Category, rate, Rate, bank, Bank, account, Account,
			tax, Tax, data, Data, contacts, Contacts, balance, Balance, more, More);
		pages->addData(dto);
	}
	return pages;
}



