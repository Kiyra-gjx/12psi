#include "stdafx.h"
#include "./returncheckservice.h"
#include "../dao/returncheckDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

bool updateData(const returnordercheckDTO::Wrapper& dto)
{
    // 组装DO数据
    BreDO DATA;
    ZO_STAR_DOMAIN_DTO_TO_DO(DATA, dto,
        Id, id,
        Check, check
    );

    // 执行数据修改
    BrecheckDAO dao;
    return dao.update(DATA) == 1;
}
