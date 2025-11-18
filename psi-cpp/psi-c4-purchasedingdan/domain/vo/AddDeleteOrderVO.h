#ifndef _ADDDELETEOrderVO_H_
#define __ADDDELETEOrderVO_H_

#include "../dto/AddDeleteOrderDTO.h"
#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class AddOrderJsonVO : public JsonVO<AddOrderDTO::Wrapper>
{
	DTO_INIT(AddOrderJsonVO, JsonVO<AddOrderDTO::Wrapper>);
};

/*class DeleteOrderJsonVO : public JsonVO<DeleteOrderDTO::Wrapper>
{
	DTO_INIT(DeleteOrderJsonVO, JsonVO<DeleteOrderDTO::Wrapper>);
}*/;


#include OATPP_CODEGEN_END(DTO)
#endif // _H_ADDDELETEOrderVO_H_
