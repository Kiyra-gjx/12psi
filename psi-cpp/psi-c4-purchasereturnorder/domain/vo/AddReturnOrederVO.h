/**
 * 示例分页显示JsonVO，用于响应给客户端的Json对象
 */
#ifndef _ADDRETURNOrderVO_H_
#define _ADDRETURNOrderVO_H_

#include "..\GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class AddReturnOrderJsonVO : public JsonVO<AddReturnOrderDTO::Wrapper> {
    DTO_INIT(AddReturnOrderJsonVO, JsonVO<AddReturnOrderDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)

#endif  // !_ADDRETURNOrderVO_H_