/**
 * 示例分页显示JsonVO，用于响应给客户端的Json对象
 */
#ifndef _DELETERETURNORDERSVO_H_
#define _DELETERETURNORDERSVO_H_

#include "..\GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class DeleteReturnOrdersJsonVO : public JsonVO<DeleteReturnOrdersDTO::Wrapper> {
    DTO_INIT(DeleteReturnOrdersJsonVO, JsonVO<DeleteReturnOrdersDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)

#endif  // !_DELETERETURNORDERSVO_H_