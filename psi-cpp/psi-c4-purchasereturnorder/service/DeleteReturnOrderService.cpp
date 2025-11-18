#include <stdafx.h>

#include "DeleteReturnOrderService.h"
#include "domain/do/getreturnlistDO.h"
#include "id/UuidFacade.h"
#include "dao/AddDAO.h"

bool DeleteReturnOrderService::deleteReturnOrders(const DeleteReturnOrdersDTO::Wrapper& dto) {
    list<string> Ids;
    for (auto id : *dto->ids) {
        Ids.push_back(id);
    }

    AddDAO adao;
    int rows = adao.deleteByIds<BreDO>(Ids);
    if (rows == Ids.size()) {
        return true;
    }
    return false;
}