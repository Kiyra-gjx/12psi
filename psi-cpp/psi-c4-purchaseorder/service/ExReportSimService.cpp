
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:13:11

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "stdafx.h"
#include "ExReportSimService.h"
// #include "../dao/ExReportSimDAO.h"

#include "domain/do/BuyDO.h"
#include "domain/dto/ExReportSimPageDTO.h"
#include "domain/query/ExReportSimQUERY.h"
#include "dao/ExReportSimDAO.h"

// #include "dao/ExReportSimDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"
//#include "../domain/dto/"

ExReportSimPageDTO::Wrapper SimpleReportService::listAll(const ExReportSimQUERY::Wrapper& query)
{
    // 构建返回对象
    auto pages = ExReportSimPageDTO::createShared();
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;

    // 查询数据总条数
    ExReportSimDAO dao;
    uint64_t count = dao.count(query);
    if (count <= 0)
    {
        return pages;
    }

    // 分页查询数据
    pages->total = count;
    pages->calcPages();
    list<BuyDO> result = dao.selectWithPage(query);

    // 将DO转换成DTO
    for (BuyDO& sub : result)
    {
        auto dto = ExReportSimDTO::createShared();
        // 主键字段
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id);

        // 业务字段
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, source, Source,
            frame, Frame,
            supplier, Supplier,
            time, Time,
            number, Number,
            total, Total,
            actual, Actual,
            money, Money,
            cost, Cost,
            account, Account,
            people, People,
            examine, Examine,
            nucleus, Nucleus,
            cse, Cse,
            invoice, Invoice,
            check, Check,
            user, User,
            data, Data,
            logistics, Logistics,
            file, File,
            more, More);

        pages->addData(dto);
    }
    return pages;
}
