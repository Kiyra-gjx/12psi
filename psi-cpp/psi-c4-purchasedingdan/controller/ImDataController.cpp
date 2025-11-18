#include "ImDataController.h"
#include "oatpp/web/server/api/ApiController.hpp"

StringJsonVO::Wrapper ImDataController::execImportData(std::shared_ptr<oatpp::web::server::api::ApiController::IncomingRequest> request)
{
    // 实现逻辑
    return StringJsonVO::createShared(); // 示例返回
}