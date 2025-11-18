#include"ReviewOrderController.h"
#include"../service/ReviewOrderService.h"


ListJsonVO<String>::Wrapper ReviewOrderController::execReviewOrder(const List<ReviewDTO::Wrapper>& dtos)
{
	// 定义返回数据对象
	auto jvo = ListJsonVO<String>::createShared();
	// 参数校验
	if (dtos->empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}



	// 定义执行service
	ReviewOrderService ser;
	auto vec_pair = ser.reviewOrder(dtos);

	// 记得初始化
	List<String> list_ans = List<String>::createShared();

	// 获取每一个数据的执行结果
	for (auto& pr : vec_pair)
	{
		bool is_ok = pr.first;

		list_ans->push_back(is_ok ? "ok" : pr.second);
	}


	jvo->success(list_ans);
	return jvo;
};
