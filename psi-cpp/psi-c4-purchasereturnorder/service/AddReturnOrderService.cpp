#include <stdafx.h>

#include "AddReturnOrderService.h"
#include "domain/do/getreturnlistDO.h"
#include "id/UuidFacade.h"
#include "dao/AddDAO.h"

std::string AddReturnOrderService::addReturnOrder(const AddReturnOrderDTO::Wrapper& dto) {
    UuidFacade uf;
    auto id = uf.genUuid();

    BreDO pdo;
    pdo.setId(id);



    ZO_STAR_DOMAIN_DTO_TO_DO(pdo, dto,
        Source, source,
        Frame, frame,
        Supplier, supplier,
        Time, time,
        Number, number,
        Total, total,
        Actual, actual,
        Money, money,
        Cost, cost,
        Account, account,
        People, people,
        Logistics, logistics,
        File, file,
        Data, data,
        More, more,
        Examine, examine,
        Nucleus, nucleus,
        Cse, cse,
        Invoice, invoice,
        Check, check,
        User, user);


    AddDAO adao;
    if (adao.insert(pdo)) {

        return id;
    }

    return "";
}