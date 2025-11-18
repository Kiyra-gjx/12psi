#include "stdafx.h"

#include "AddDeleteOrderController.h"
#include "service/AddDeleteServer.h"

StringJsonVO::Wrapper AddDeleteOrderController::execAddOrder(const AddOrderDTO::Wrapper& dto)
{
    AddDeleteServer ads;
    auto jvo = StringJsonVO::createShared();
    auto id = ads.saveData(dto);
    if (id == "") {
        jvo->fail(id);
    }
    else {
        jvo->success(id);
    }

    return jvo;
}

ListJsonVO<String>::Wrapper AddDeleteOrderController::execDeleteOrder(const List<String>& dto)
{
    AddDeleteServer ads;
    auto jvo = ListJsonVO<String>::createShared();
    if (ads.deleteData(dto)) {
        jvo->success(dto);
    } else {
        jvo->fail(nullptr);
    }
    return jvo;


    return {};
}
