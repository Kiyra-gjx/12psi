#ifndef _SOR_DAO_
#define _SOR_DAO_

#include "BaseDAO.h"
#include "domain/do/SorDO.h"  // 数据库
#include "SorMapper.h"  // 映射
#include "domain/query/SaleOrderListQuery.h" // 查询参数
#include"domain/dto/SaleOrderListDTO.h"
#include "domain/do/SorInfoDO.h"

struct SorDetailDO {
	PtrSorDO sor;
	std::vector<PtrSorInfoDO> sorInfoList;
};

using PtrSorDetailDO = std::shared_ptr<SorDetailDO>;
class SorDAO : public BaseDAO {
public:
	bool SorUpdate(const PtrSorDO& sorDO);
	std::vector<PtrSorDO> querySimpleReport(const std::string& startDate, const std::string& endDate);
	std::vector<PtrSorDetailDO> queryDetailReport(const std::string& orderNoLike);
	//导入数据
	bool importData(const PayloadDTO& payload,const SorImportDTO::Wrapper& dto, std::string& sor_uuid);

	uint64_t count(const SaleOrderListQuery::Wrapper& query);

	std::list<PtrSorDO> selectAll(const SaleOrderListQuery::Wrapper& query);

	PtrSorDO selectById(const string& id);

	std::string queryConditionBuilder(const SaleOrderListQuery::Wrapper& query, SqlParams& params);

	std::string queryOrderBuilder(const SaleOrderListQuery::Wrapper& query, SqlParams& params);

	//std::list<PtrSorDO> selectWithPage(const SaleOrderListQuery::Wrapper& query);


	bool deleteById(const std::string& id);
	bool approveById(const std::string& id);
	bool unapproveById(const std::string& id);
	bool isOrderApproved(const std::string& id);  // 检查是否已审核

};

#endif