#pragma once
#ifndef _GOODSDAO_H_
#define _GOODSDAO_H_

#include "BaseDAO.h"
#include "../domain/do/DingdanDO.h"
#include "GoodsMapper.h"

/**
 * 商品表数据库访问对象
 */
class GoodsDAO : public BaseDAO
{
public:
	// 根据ID查询商品
	PtrGoodsDO selectById(const std::string& id);

	// 更新商品信息
	bool updateGoods(const PtrGoodsDO& goodsDO);
};

#endif // !_GOODSDAO_H_