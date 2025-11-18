#ifndef GOODSVO_H
#define GOODSVO_H
#include "../../GlobalInclude.h"
#include "domain/dto/GoodsDTO/GoodsDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class GoodsSpecJsonVO : public JsonVO<GoodsSpecDTO::Wrapper>
{
	DTO_INIT(GoodsSpecJsonVO, JsonVO<GoodsSpecDTO::Wrapper>);

};


/**
 * 客户列表分页显示JsonVO，用于响应给客户端的Json对象
 */
class GoodsListPageJsonVO : public JsonVO<GoodsListPageDTO::Wrapper> {
	DTO_INIT(GoodsListPageJsonVO, JsonVO<GoodsListPageDTO::Wrapper>);
};

/**
 * 客户详情显示JsonVO，用于响应给客户端的Json对象
 */
class GoodsDetailJsonVO : public JsonVO<GoodsDetailDTO::Wrapper> {
	DTO_INIT(GoodsDetailJsonVO, JsonVO<GoodsDetailDTO::Wrapper>);
};



#include OATPP_CODEGEN_END(DTO)
#endif // !_CUSTOMERVO_H_
