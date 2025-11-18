#ifndef _ATTACHMENTQUERY_H_
#define _ATTACHMENTQUERY_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/attachment/AttachmentQuery.h"
#include "domain/dto/attachment/AttachmentDTO.h"
#include "domain/vo/attachment/AttachmentVO.h"

// 0 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen
#include "../ApiDeclarativeServicesHelper.h"
#include OATPP_CODEGEN_BEGIN(DTO)
#define API_TAG ZH_WORDS_GETTER("attachment.tags.t1")

/**
 * 附件控制器，处理附件的增删改查操作
 */
class AttachmentController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
	API_ACCESS_DECLARE(AttachmentController);

public:  //定义接口
	// 定义修改附件描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("attachment.modify.summary"), modifyAttachment, ModifyJsonVO::Wrapper, API_TAG);
	// 定义修改附件处理
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/attachment", modifyAttachment, BODY_DTO(AttachmentDTO::Wrapper, dto), execModifyAttachment(dto, authObject->getPayload()));

	// 定义删除附件描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("attachment.remove.summary"), removeAttachment, RemoveJsonVO::Wrapper, API_TAG);
	// 定义删除附件处理
	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/attachment", removeAttachment, BODY_DTO(AttachmentRemoveDTO::Wrapper, id), execRemoveAttachment(id));

	// 
	API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("attachment.add.summary"), addAttachment, AttachmentAddDTO::Wrapper, StringJsonVO::Wrapper, API_TAG);
	//
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/attachment", addAttachment, REQUEST(std::shared_ptr<IncomingRequest>, request), execAddAttachment(request));

	// 
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("attachment.query.summary"), queryAttachment, AttachmentQuery, QueryJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/attachment", queryAttachment, AttachmentQuery, execQueryAttachment(query));

private:  //定义接口执行函数
	// 修改数据
	ModifyJsonVO::Wrapper execModifyAttachment(const AttachmentDTO::Wrapper& dto, const PayloadDTO& payload);
	// 删除数据
	RemoveJsonVO::Wrapper execRemoveAttachment(const AttachmentRemoveDTO::Wrapper& id);
	// 添加数据
	StringJsonVO::Wrapper execAddAttachment(std::shared_ptr<IncomingRequest> request);
	// 鏌ヨ鏁版嵁
	QueryJsonVO::Wrapper execQueryAttachment(const AttachmentQuery::Wrapper& query);
};
#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)
#include OATPP_CODEGEN_END(DTO)
#endif

