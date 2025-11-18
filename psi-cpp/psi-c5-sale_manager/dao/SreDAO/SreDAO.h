#pragma once
#ifndef _SRE_DAO_
#define _SRE_DAO_

#include "BaseDAO.h"                  // 项目基础DAO类
#include "domain/do/SreDO.h"         // 销售退货单主表DO
#include "SreMapper.h"
#include "domain/query/SaleReturnOrderQuery.h"  // 查询参数头文件

//用于实现导入数据功能
#include "domain/dto/SaleReturnOrderDTO.h"


//松 按照自己逻辑额外引入的DO类
#include "domain/do/SreInfoDO.h"
// 主表+明细表关联数据结构（使用智能指针）
struct SreDetailDO {
    PtrSreDO mainDO;                      // 销售退货单主表智能指针
    std::vector<PtrSreInfoDO> itemDOList; // 销售退货单明细表智能指针列表
};
// 定义智能指针类型 PtrSreDetail（便于在 DAO 方法中使用）
using PtrSreDetailDO = std::shared_ptr<SreDetailDO>;


class SreDAO : public BaseDAO
{
    //根据query构建sql语句用于筛选符合条件的商品
    inline std::string queryConditionBuilder(const SreListQuery::Wrapper& query, SqlParams& params);
    //构建query构建sql语句用于为筛选出的结果排序
    inline std::string queryOrderBuilder(const SreListQuery::Wrapper& query, SqlParams& params);
public:
    // 1. 统计数据条数
    uint64_t count(const SreListQuery::Wrapper& query);

    // 2. 根据id查询数据条数
    uint64_t countById(const SreDetailQuery::Wrapper& query);

    // 3. 分页查询数据
    std::list<SreViewDO> selectWithPage(const SreListQuery::Wrapper& query);

    // 4. 按ID查询销售退货单详情
    std::list<SreViewDO> selectById(const SreDetailQuery::Wrapper& query);

    // 5. 新增销售退货单
    bool insert(const PtrSreDO& sreDO);

    //// 6. 更新销售退货单
    //bool update(const SreViewDO& sreDO);


    // 7. 按ID删除销售退货单
    bool delById(const std::string& id);

    // 8. 更新销售退货单核对状态
    bool updateCheckStatus(const std::string& id, int checkStatus);

    // 9. 按销售退货单号查询
    std::list<SreViewDO> selectByNumber(const std::string& number);

    // 10. 按客户查询
    std::list<SreViewDO> selectByCustomer(const std::string& customerId);

    // 11. 按审核状态查询
    std::list<SreViewDO> selectByExamine(char examine);

    // 松 按照自己的逻辑 额外添加的三个方法
    // 1. 查询简单报表数据（主表）
    std::vector<PtrSreDO> querySimpleList(
        const std::string& startDate,
        const std::string& endDate
    );

    // 2. 查询详细报表数据
    std::vector<PtrSreDetailDO> queryDetailList(
        const std::string& orderNoLike,
        const std::string& customer
        //int examineStatus
    );

    // 3. 更新销售退货单
    bool update(const std::shared_ptr<SreDO>& sreDO);


    // 审核退货单
    bool approveById(const std::string& id);

    // 反审核退货单  
    bool unapproveById(const std::string& id);

    // 导入销售退货单数据
    bool importData(const PayloadDTO& payload, const SaleReturnOrderImportDTO::Wrapper& dto, std::string& sre_uuid);
};

#endif // !_SRE_DAO_