#include "stdafx.h"
#include "../domain/do/BuyJsDO.h"
#include "../domain/do/BuyInfoDO.h" 
#include "PurchaseOrderJsService.h"
#include "../dao/PurchaseOrderJsDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"
#include "SqlSession.h" 

string PurchaseOrderService::addPurchaseOrder(const OrderAddDTO::Wrapper dto)
{
	// 1. 实例化DAO
	PurchaseOrderDAO dao;
	// 2. 从DAO中取出
	SqlSession* sqlSession = dao.getSqlSession();
	// 3. 手动开启事务（保证新增事务原子性）
	sqlSession->beginTransaction();

	try
	{
		// --- A. 保存主表 (buy) ---
		BuyJsDO orderDO;

		// --- 使用 .getValue() 来获取 DTO 的值 ---

		// 映射 String 字段
		if (dto->buy_number) orderDO.setNumber(dto->buy_number);
		if (dto->buy_logistics) orderDO.setLogistics(dto->buy_logistics);
		if (dto->buy_data) orderDO.setData(dto->buy_data);
		if (dto->buy_supplier) orderDO.setSupplier(dto->buy_supplier);
		if (dto->buy_time) orderDO.setTime(dto->buy_time);
		if (dto->buy_account) orderDO.setAccount(dto->buy_account);
		if (dto->buy_people) orderDO.setPeople(dto->buy_people);
		if (dto->buy_user) orderDO.setUser(dto->buy_user);


		// 映射 Float64 字段 
		orderDO.setTotal(dto->buy_total.getValue(0.0));
		orderDO.setActual(dto->buy_actual.getValue(0.0));
		orderDO.setMoney(dto->buy_money.getValue(0.0));
		orderDO.setCost(dto->buy_cost.getValue(0.0));

		// 4. 调用DAO写入主表
		std::string newOrderId = dao.addPurchaseOrder(orderDO);
		if (newOrderId == "failed") {
			throw std::runtime_error("保存主表(buy)失败");
		}

		// --- B. 循环保存明细表 (buy_info) ---
		if (dto->items)
		{
			for (const auto& itemDTO : *dto->items)
			{
				BuyInfoDO infoDO;
				infoDO.setPid(newOrderId);
				infoDO.setSource("");
				infoDO.setAttr("");  

				// 映射 String 字段
				if (itemDTO->goods_id) infoDO.setGoods(itemDTO->goods_id);
				if (itemDTO->warehouse_id) infoDO.setWarehouse(itemDTO->warehouse_id);

				// 映射 Float64 字段
				infoDO.setNums(itemDTO->quantity.getValue(0.0));
				infoDO.setPrice(itemDTO->unit_price.getValue(0.0));
				infoDO.setTotal(itemDTO->quantity.getValue(0.0) * itemDTO->unit_price.getValue(0.0));

				if (!dao.addInfo(infoDO)) {
					throw std::runtime_error("保存明细(buy_info)失败");
				}
			}
		}

		// --- C. 提交事务 ---
		sqlSession->commitTransaction();
		return newOrderId;
	}
	catch (const std::exception& e)
	{
		// --- D. 回滚事务 ---
		const char* errorMsg = e.what();
		if (errorMsg == nullptr) {
			errorMsg = "Unknown exception";
		}
		OATPP_LOGE("PurchaseOrderService", "新增采购单失败: %s", errorMsg);
		sqlSession->rollbackTransaction();
		return "failed";
	}
}

// 删除采购单
string PurchaseOrderService::removePurchaseOrder(string id)
{
	PurchaseOrderDAO dao;

	// 1. 检查是否“已审核”
	if (dao.countByIdAndStatus(id, 1) > 0) {
		// 记录存在，且 examine=1
		return "AUDITED"; // 返回“已审核”
	}

	// 2. 检查记录是否存在 (且 examine=0)
	if (dao.countByIdAndStatus(id, 0) == 0) {
		// 记录不存在，或者 examine 不是 0
		return "NOT_FOUND_OR_FAILED"; // 返回“未找到”
	}

	// 3. 记录存在且 examine=0，执行删除 (使用事务保证操作原子性)
	SqlSession* sqlSession = dao.getSqlSession();
	sqlSession->beginTransaction(); // 开启事务

	try
	{
		// 4. 先删除明细表 (is_buy_info)
		dao.deleteInfoByPid(id);

		// 5. 再删除主表 (is_buy)
		dao.deleteById(id);

		// 6. 提交事务
		sqlSession->commitTransaction();
		return "SUCCESS";
	}
	catch (const std::exception& e)
	{
		// 7. 回滚事务
		OATPP_LOGE("PurchaseOrderService", "删除采购单失败: %s", e.what());
		sqlSession->rollbackTransaction();
		return "NOT_FOUND_OR_FAILED";
	}
}