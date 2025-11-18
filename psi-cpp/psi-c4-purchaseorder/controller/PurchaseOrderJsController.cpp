#include "stdafx.h"
#include "PurchaseOrderJsController.h"
#include "../service/PurchaseOrderJsService.h" 

// 新增采购单
StringJsonVO::Wrapper PurchaseOrderJsController::executeAddJsOrder(const OrderAddDTO::Wrapper& dto)
{
	// 1. 创建响应对象
	auto jvo = StringJsonVO::createShared();

	// 2. 实例化并调用 Service
	PurchaseOrderService service;
	string newId = service.addPurchaseOrder(dto);

	// 3. 根据 Service 的返回结果，填充 jvo
	if (newId == "failed") {
		jvo->fail(ZH_WORDS_GETTER("js.buy.add.fail"));
	}
	else {
		jvo->success(newId); // 成功，返回新ID
	}
	return jvo; // 4. 返回 jvo (这会序列化成 JSON，不再是 null)
}

//删除采购单
StringJsonVO::Wrapper PurchaseOrderJsController::execRemoveJsOrder(const OrderDeleteDTO::Wrapper& dto) {
	auto jvo = StringJsonVO::createShared();
	if (!dto || !dto->ids || dto->ids->empty()) {
		jvo->init("", RS_PARAMS_INVALID);
		return jvo;
	}

	PurchaseOrderService service;
	std::vector<String> successIds;
	std::string firstErrorMsg = ""; // 用于保存第一个错误信息

	auto& idList = dto->ids;
	for (auto it = idList->begin(); it != idList->end(); ++it) {
		const auto& id = *it;
		string result = service.removePurchaseOrder(id); // 获取 string 结果

		if (result == "SUCCESS") {
			successIds.push_back(id);
		}
		else if (result == "AUDITED" && firstErrorMsg.empty()) {
			// 捕获“已审核”的提示
			firstErrorMsg = ZH_WORDS_GETTER("js.buy.delete.audited"); // <-- 我们需要定义这个
		}
	}

	if (successIds.empty()) {
		// 如果一个都没成功
		if (firstErrorMsg.empty()) {
			// 并且没有特定错误，就返回通用失败
			jvo->fail(ZH_WORDS_GETTER("js.buy.delete.fail"));
		}
		else {
			// 否则，返回“已审核”的提示
			jvo->fail(firstErrorMsg);
		}
	}
	else if (successIds.size() == idList->size()) {
		// 全部成功
		jvo->success(ZH_WORDS_GETTER("js.buy.delete.success"));
	}
	else {
		// 部分成功
		jvo->success(ZH_WORDS_GETTER("js.buy.delete.partly_success"));
	}

	return jvo;
}