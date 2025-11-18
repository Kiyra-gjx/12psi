#include "stdafx.h"
#include "./returnorderservice.h"
#include "../dao/returnorderDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

bool updateData(const returnorderDetailDTO::Wrapper& dto)
{
    // 组装DO数据
    BreInfoDO DATA;
    ZO_STAR_DOMAIN_DTO_TO_DO(DATA, dto,
        Id, id,
        Pid, pid,
        Source, source,
        Goods, goods,
        Attr, attr,
        Unit, unit,
        Warehouse, warehouse,
        Batch, batch,
        Mfd, mfd,
        Price, price,
        Nums, nums,
        Serial, serial,
        Discount, discount,
        Dsc, dsc,
        Total, total,
        Tax, tax,
        Tat, tat,
        Tpt, tpt,
        Data, data
    );

    // 执行数据修改
    BreInfoDAO dao;
    return dao.update(DATA) == 1;
}
