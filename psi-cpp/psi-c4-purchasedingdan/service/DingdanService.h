#pragma once
#ifndef _DINGDANSERVICE_H_
#define _DINGDANSERVICE_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/DingdanVO.h"
#include "domain/dto/DingdanDTO.h"
#include "domain/dto/DingdanExamineDTO.h"
#include "domain/do/DingdanDO.h"
#include "dao/BorDAO.h"
#include "../dao/BorInfoDAO.h"
#include "../dao/GoodsDAO.h"

#include "NacosClient.h"
/**
 * 订单业务逻辑类
 */
class DingdanService {

private:
	inline string getDfsServerAddrssUrl();

public:

	// 修改订单（新的多表更新方法）
	bool modifyDingdanMultiTable(const DingdanDetailDTO::Wrapper& dto);

	// 审核和反审核订单
	StringJsonVO::Wrapper examineDingdan(const DingdanExamineDTO::Wrapper& dto);

private:
	// 辅助方法：将DTO转换为多个DO对象
	bool convertDtoToDos(const DingdanDetailDTO::Wrapper& dto,
		PtrBorDO& borDO,
		PtrBorInfoDO& borInfoDO,
		PtrGoodsDO& goodsDO);
};


#endif // !_DINGDANSERVICE_H_