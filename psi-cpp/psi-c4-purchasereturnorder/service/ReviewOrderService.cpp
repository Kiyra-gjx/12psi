#include "stdafx.h"
#include "ReviewOrderService.h"
#include "../dao/ReviewOrderDAO.h"
#include "../domain/do/getreturnlistDO.h"
#include "domain/do/LogDO.h"
#include "domain/do/AccountInfoDO.h"
#include "domain/do/RoomInfoDO.h"
#include "id/UuidFacade.h"
#include <algorithm>    // 包含 std::all_of
#include <cctype>       // 包含 std::isalnum
#include <iostream>     // 包含 std::cout
#include "GBKToUTF-8.h"

using namespace std;

/**
 * 审核采购退货单
 * @param dtos 审核请求DTO列表
 * @return 审核结果列表（状态+提示信息）
 */
vector<pair<bool, string>> ReviewOrderService::reviewOrder(const List<ReviewDTO::Wrapper>& dtos)
{
    vector<pair<bool, string>> ret;

    for (auto& dto : *dtos)
    {
        // 1.参数校验
        // 非空校验：ID和来源不能为空
        if (!dto->id || !dto->source)
        {
            ret.emplace_back(false, "this a error data");
            continue;
        }

        // 格式校验：仅允许字母和数字
        auto isAlphaNumeric = [](const string& s) {
            return all_of(s.begin(), s.end(), [](unsigned char c) {
                return isalnum(c);
                });
            };

        if (!isAlphaNumeric(dto->id) || !isAlphaNumeric(dto->source))
        {
            ret.emplace_back(false, "this a error data");
            continue;
        }

        // 2.查询单据信息
        ReviewOrderDAO dao;
        auto order = dao.selectById(dto->id);
        if (!order)
        {
            ret.emplace_back(false, "id:" + dto->id + " can't find the order");
            continue;
        }

        // 3.查询商品明细
        auto goodsList = dao.selectByPid(dto->id);
        if (goodsList.empty())
        {
            ret.emplace_back(false, "id:" + dto->id + " don't have any goods");
            continue;
        }

        // 4.校验库存并准备更新数据
        vector<PtrRoomDO> stockUpdateList;
        bool stockCheckPass = true;
        int currentExamStatus = order->getExamine();  // 0-未审核，1-已审核

        for (auto& goods : goodsList)
        {
            string goodsId = goods.getGoods();
            string warehouseId = goods.getWarehouse();

            // 查询当前库存
            auto stock = dao.selectGoods(goodsId, warehouseId);
            if (!stock)
            {
                ret.emplace_back(false,
                    "id:" + dto->id +
                    " in warehouse:" + warehouseId +
                    " can't find the good:" + goodsId);
                stockCheckPass = false;
                break;
            }

            // 初始化库存更新信息
            stock->setInfo(goods.getId());       // 关联商品明细ID
            stock->setCid(order->getId());       // 关联单据ID
            stock->setPrice(goods.getPrice());   // 商品单价
            stock->setNb(goods.getNums());       // 商品数量

            // 库存数量校验与计算
            double targetNum = goods.getNums();  // 操作数量
            double currentStock = stock->getNums();  // 当前库存

            if (currentExamStatus == 0)
            {
                // 未审核→审核：检查库存是否充足
                if (targetNum > currentStock)
                {
                    ret.emplace_back(false,
                        "id:" + dto->id +
                        "There is not enough stock of Good " + goodsId +
                        " in Warehouse " + warehouseId);
                    stockCheckPass = false;
                    break;
                }
                stock->setNums(currentStock - targetNum);  // 扣减库存
            }
            else if (currentExamStatus == 1)
            {
                // 已审核→反审核：恢复库存
                stock->setNums(currentStock + targetNum);  // 增加库存
            }

            stockUpdateList.push_back(stock);
        }

        // 库存校验失败则跳过后续处理
        if (!stockCheckPass || stockUpdateList.size() != goodsList.size())
        {
            continue;
        }

        // 5.执行审核状态变更逻辑
        BreDO orderData;
        orderData.setId(order->getId());
        orderData.setSource(order->getSource());
        bool operateSuccess = true;

        if (currentExamStatus == 1)
        {
            // 已审核→反审核
            orderData.setExamine(0);
            operateSuccess &= (dao.update(orderData) == 1);

            // 恢复库存并删除关联记录
            for (auto& stock : stockUpdateList)
            {
                // 更新库存
                operateSuccess &= dao.update(*stock);
                if (!operateSuccess) break;

                // 删除仓库操作记录
                auto roomInfo = dao.selectByPCI(stock->getId(), stock->getCid(), stock->getInfo());
                operateSuccess &= dao.deleteById<RoomInfoDO>(roomInfo->getId());
                if (!operateSuccess) break;
            }

            // 删除资金记录
            if (operateSuccess)
            {
                auto accountInfo = dao.selectByPC(order->getAccount(), order->getId());
                operateSuccess &= dao.deleteById<AccountInfoDO>(accountInfo->getId());
            }
        }
        else if (currentExamStatus == 0)
        {
            // 未审核→审核
            orderData.setExamine(1);
            operateSuccess &= (dao.update(orderData) == 1);

            // 扣减库存并添加关联记录
            for (auto& stock : stockUpdateList)
            {
                // 更新库存
                operateSuccess &= dao.update(*stock);
                if (!operateSuccess) break;

                // 添加仓库操作记录
                RoomInfoDO roomData;
                UuidFacade uuidGen;
                roomData.setId(uuidGen.genUuid());
                roomData.setCid(stock->getCid());
                roomData.setInfo(stock->getInfo());
                roomData.setPid(stock->getId());
                roomData.setType("bre");
                roomData.setTime(LogDO::format());
                roomData.setDirection(0);
                roomData.setPrice(stock->getPrice());
                roomData.setNums(stock->getNb());

                operateSuccess &= dao.insert(roomData);
                if (!operateSuccess) break;
            }

            // 添加资金记录
            if (operateSuccess)
            {
                AccountInfoDO accountData;
                UuidFacade uuidGen;
                accountData.setId(uuidGen.genUuid());
                accountData.setPid(order->getAccount());  // 结算账号
                accountData.setCid(order->getId());       // 关联单据
                accountData.setType("bre");               // 单据类型
                accountData.setDirection(1);              // 资金方向：入
                accountData.setMoney(order->getMoney());  // 金额
                accountData.setTime(LogDO::format());     // 操作时间

                operateSuccess &= dao.insert(accountData);
                cout << "Acc.ID:" << accountData.getId() << endl;  // 调试信息
            }
        }

        // 6.记录操作结果与日志
        if (operateSuccess)
        {
            // 生成日志信息
            string logInfo = gbk_to_utf8(
                (currentExamStatus == 1 ? "反审核采购退货单" : "审核采购退货单") +
                string(" [") + order->getNumber() + string("] ")
            );

            // 写入日志
            if (LogDO::write_log(logInfo, order->getUser()) == 0)
            {
                ret.emplace_back(true, "id:" + dto->id + " update success, but insert log error");
            }
            else
            {
                ret.emplace_back(true, "id:" + dto->id + " update success");
            }
        }
        else
        {
            ret.emplace_back(false, "id:" + dto->id + " update error");
        }
    }

    // 调试输出结果
    for (const auto& result : ret)
    {
        cout << "first:" << result.first << "   " << "second:" << result.second << endl;
    }

    return ret;
}