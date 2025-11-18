#include "stdafx.h"

#include "id/UuidFacade.h"
#include "service/AddDeleteServer.h"
#include "domain/do/PurchaseDingDanDO.h"
#include "dao/AddDeleteDAO.h"
#include "domain/dto/AddDeleteOrderDTO.h"
#include "Macros.h"

std::string AddDeleteServer::saveData(const AddOrderDTO::Wrapper &dto) {
    UuidFacade uf;
    auto id = uf.genUuid();

    PurchaseDingDanDO pdo;
    pdo.setId(id);

    ZO_STAR_DOMAIN_DTO_TO_DO(pdo, dto,
        Id, id,
        Supplier, supplier,
        Time, time,
        Number, number,
        Total, total,
        Actual, actual,
        People, people,
        Arrival, arrival,
        Logistics, logistics,
        File, file,
        Data, data,
        Examine, examine,
        State, state,
        User, user);

    AddDeleteDAO adao;
    if (adao.insert(pdo)) {
        return id;
    }
    return "";
}

bool AddDeleteServer::deleteData(const oatpp::List<oatpp::String> &ids) {
    list<string> Ids;
    for (auto id : *ids.get()) {
        Ids.push_back(id);
    }

    AddDeleteDAO adao;
    int rows = adao.deleteByIds<PurchaseDingDanDO>(Ids);
    if (rows == ids->size()) {
        return true;
    }
    return false;
}
