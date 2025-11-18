#ifndef _CustomerDTO_H_
#define _CustomerDTO_H_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//修改客户数据定义
class CustomerModifyDTO : public oatpp::DTO {
public:
    DTO_INIT(CustomerModifyDTO, DTO);
    //ID
    API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("cus.field.id"));

    //客户名称
    API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("cus.field.name"));

    //拼音信息
    API_DTO_FIELD_DEFAULT(String, py, ZH_WORDS_GETTER("cus.field.py"));

    //客户编号
    API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("cus.field.number"));

    //所属组织
    API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("cus.field.frame"));

    //所属用户
    API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("cus.field.user"));

    //客户类别
    API_DTO_FIELD_DEFAULT(String, category, ZH_WORDS_GETTER("cus.field.category"));

    //客户等级
    API_DTO_FIELD_DEFAULT(String, grade, ZH_WORDS_GETTER("cus.field.grade"));

    //开户银行
    API_DTO_FIELD_DEFAULT(String, bank, ZH_WORDS_GETTER("cus.field.bank"));

    //银行账号
    API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("cus.field.account"));

	//纳税号码
	API_DTO_FIELD_DEFAULT(String, tax, ZH_WORDS_GETTER("cus.field.tax"));

	//备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("cus.field.data"));

    //联系资料
    API_DTO_FIELD_DEFAULT(String, contacts, ZH_WORDS_GETTER("cus.field.contacts"));

    //应收款余额
    API_DTO_FIELD_DEFAULT(Float64, balance, ZH_WORDS_GETTER("cus.field.balance"));

    //扩展信息
    API_DTO_FIELD_DEFAULT(String, more, ZH_WORDS_GETTER("cus.field.more"));

};

/**
 * 客户列表数据传输模型
 */
class CustomerListDTO : public oatpp::DTO
{
	DTO_INIT(CustomerListDTO, DTO);
	// 自增ID
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("cus.field.id"));
	// 客户编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("cus.field.number"));
	// 客户名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("cus.field.name"));
	// 客户类别
	API_DTO_FIELD_DEFAULT(String, category, ZH_WORDS_GETTER("cus.field.category"));
	// 客户等级
	API_DTO_FIELD_DEFAULT(String, grade, ZH_WORDS_GETTER("cus.field.grade"));
	// 开户银行
	API_DTO_FIELD_DEFAULT(String, bank, ZH_WORDS_GETTER("cus.field.bank"));
	// 银行账号
	API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("cus.field.account"));

	// 联系人员
	API_DTO_FIELD_DEFAULT(String, contact_person, ZH_WORDS_GETTER("cus.field.contact_person"));
	// 联系电话
	API_DTO_FIELD_DEFAULT(String, telephone, ZH_WORDS_GETTER("cus.field.telephone"));
	
	// 应收款余额
	API_DTO_FIELD_DEFAULT(String, balance, ZH_WORDS_GETTER("cus.field.balance"));
	// 所属组织
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("cus.field.frame"));
	// 所属用户
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("cus.field.user"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data_, ZH_WORDS_GETTER("cus.field.memo"));
};

/**
 * 客户列表分页数据传输模型
 */
class CustomerListPageDTO : public PageDTO<CustomerListDTO::Wrapper>
{
	DTO_INIT(CustomerListPageDTO, PageDTO<CustomerListDTO::Wrapper>);
};





/**
 * 新增客户传输模型,@快乐五香蛋
 */
class CustomerAddDTO : public oatpp::DTO
{
	DTO_INIT(CustomerAddDTO, DTO);
	/// 客户名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("cus.field.name"));
	/// 客户编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("cus.field.number"));
	//所属组织
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("cus.field.frame"));
	/// 客户类别
	API_DTO_FIELD_DEFAULT(String, category, ZH_WORDS_GETTER("cus.field.category"));
	//客户等级
	API_DTO_FIELD_DEFAULT(String, grade, ZH_WORDS_GETTER("cus.field.grade"));
	//开户银行
	API_DTO_FIELD_DEFAULT(String, bank, ZH_WORDS_GETTER("cus.field.bank"));
	//银行账号
	API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("cus.field.account"));
	//纳税号码
	API_DTO_FIELD_DEFAULT(String, tax, ZH_WORDS_GETTER("cus.field.tax"));
	//备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("cus.field.data"));
	//联系资料
	API_DTO_FIELD_DEFAULT(String, contacts, ZH_WORDS_GETTER("cus.field.contact"));
	//应收款余额
	API_DTO_FIELD_DEFAULT(Float64, balance, ZH_WORDS_GETTER("cus.field.balance"));
	// 所属用户
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("cus.field.user"));
};

/**
 * 客户列表分页数据传输模型
 */
class CusFileAddFormFileDTO : public PageDTO<CustomerAddDTO::Wrapper>
{
	DTO_INIT(CusFileAddFormFileDTO, PageDTO<CustomerAddDTO::Wrapper>);
};


/**
 * 客户详情数据传输模型
 */
class CustomerDetailDTO : public CustomerAddDTO
{
	DTO_INIT(CustomerDetailDTO, CustomerAddDTO);
	// 客户ID
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("cus.field.id"));
};

/**
 * 添加文件表单数据@快乐五香蛋
 */
class CusFileAddFormDTO : public oatpp::DTO
{
	DTO_INIT(CusFileAddFormDTO, DTO);

};




/**
 * 添加文件数据模型@快乐五香蛋
 */
class CusFileAddDTO : public CusFileAddFormDTO
{
	DTO_INIT(CusFileAddDTO, CusFileAddFormDTO);
	// 文件数据
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, file, ZH_WORDS_GETTER("file.field.file"), true);
};


/**
* 客户DTO - 用于接口数据传输
*/
class CustomerDTO : public oatpp::DTO
{
	DTO_INIT(CustomerDTO, DTO);
	//自增序号(可选)
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("Customer.field.id"));
	// 客户编号  
	API_DTO_FIELD_REQUIRE(String, number, ZH_WORDS_GETTER("Customer.field.number"), true);
	// 客户名称  
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("Customer.field.name"), true);
	// 所属组织  
	API_DTO_FIELD_REQUIRE(String, frame, ZH_WORDS_GETTER("Customer.field.frame"), true);
	// 所属用户群  
	API_DTO_FIELD_REQUIRE(String, user, ZH_WORDS_GETTER("Customer.field.user"), true);
	// 客户类别
	API_DTO_FIELD_REQUIRE(String, category, ZH_WORDS_GETTER("Customer.field.category"), true);
	// 客户等级  
	API_DTO_FIELD_REQUIRE(String, grade, ZH_WORDS_GETTER("Customer.field.grade"), true);
	// 开户银行（可选）  
	API_DTO_FIELD_DEFAULT(String, bank, ZH_WORDS_GETTER("Customer.field.bank"));
	// 银行账号（可选）  
	API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("Customer.field.account"));
	// 纳税号码（可选）  
	API_DTO_FIELD_DEFAULT(String, tax, ZH_WORDS_GETTER("Customer.field.tax"));
	// 备注信息（可选）  
	API_DTO_FIELD_DEFAULT(String, data_, ZH_WORDS_GETTER("Customer.field.data"));
	// 联系资料（可选，JSON格式字符串）  
	API_DTO_FIELD_DEFAULT(String, contacts, ZH_WORDS_GETTER("Customer.field.contacts"));
	// 账户余额（可选）
	API_DTO_FIELD_DEFAULT(oatpp::Float64, balance, ZH_WORDS_GETTER("Customer.field.balance"));
	// 扩展信息（可选）
	API_DTO_FIELD_DEFAULT(String, more, ZH_WORDS_GETTER("Customer.field.more"));
	// 拼音简写（可选）
	API_DTO_FIELD_DEFAULT(String, py, ZH_WORDS_GETTER("Customer.field.py"));


};

/**
* 客户新增响应DTO
*/
class CustomerAddResponseDTO : public oatpp::DTO
{
	DTO_INIT(CustomerAddResponseDTO, DTO);

	DTO_FIELD(String, Id);
	DTO_FIELD_INFO(Id) {
		info->description = ZH_WORDS_GETTER("Customer.field.id");
		info->required = true;
	}

	//// 是否成功  
	//DTO_FIELD(Boolean, success);  
	//// 消息  
	//DTO_FIELD(String, message);  
};

/**
* 客户修改响应DTO
*/
class CustomerUpdateResponseDTO : public oatpp::DTO
{
	DTO_INIT(CustomerUpdateResponseDTO, DTO);

	//// 是否成功  
	//DTO_FIELD(Boolean, success);  
	//// 消息  
	//DTO_FIELD(String, message);  
};
class CustomerGetDTO : public oatpp::DTO {
	DTO_INIT(CustomerGetDTO, DTO);
	// 客户ID  
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("Customer.field.id"), true);
};
class CustomerGetResponseDTO : public oatpp::DTO {
	DTO_INIT(CustomerGetResponseDTO, DTO);
	// 客户ID  
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("Customer.field.id"), true);
	// 客户编号  
	API_DTO_FIELD_REQUIRE(String, number, ZH_WORDS_GETTER("Customer.field.number"), true);
	// 客户名称  
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("Customer.field.name"), true);
	// 所属组织  
	API_DTO_FIELD_REQUIRE(String, frame, ZH_WORDS_GETTER("Customer.field.frame"), true);
	// 所属用户群  
	API_DTO_FIELD_REQUIRE(String, user, ZH_WORDS_GETTER("Customer.field.user"), true);
	// 客户类别
	API_DTO_FIELD_REQUIRE(String, category, ZH_WORDS_GETTER("Customer.field.category"), true);
	// 客户等级  
	API_DTO_FIELD_REQUIRE(String, grade, ZH_WORDS_GETTER("Customer.field.grade"), true);
	// 开户银行（可选）  
	API_DTO_FIELD_DEFAULT(String, bank, ZH_WORDS_GETTER("Customer.field.bank"));
	// 银行账号（可选）  
	API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("Customer.field.account"));
	// 纳税号码（可选）  
	API_DTO_FIELD_DEFAULT(String, tax, ZH_WORDS_GETTER("Customer.field.tax"));
	// 备注信息（可选）  
	API_DTO_FIELD_DEFAULT(String, data_, ZH_WORDS_GETTER("Customer.field.data"));
	// 联系资料（可选，JSON格式字符串）  
	API_DTO_FIELD_DEFAULT(String, contacts, ZH_WORDS_GETTER("Customer.field.contacts"));
	// 账户余额（可选）
	API_DTO_FIELD_DEFAULT(oatpp::Float64, balance, ZH_WORDS_GETTER("Customer.field.balance"));
	// 扩展信息（可选）
	API_DTO_FIELD_DEFAULT(String, more, ZH_WORDS_GETTER("Customer.field.more"));
	// 拼音简写（可选）
	API_DTO_FIELD_DEFAULT(String, py, ZH_WORDS_GETTER("Customer.field.py"));
};
#include OATPP_CODEGEN_END(DTO)  
#endif // !_CUSTOMER_DTO

