#include "returncheckDAO.h"
#include"../domain/do/getreturnlistDO.h"
bool BrecheckDAO::updateBrecheck(const BreDO& obj)
{
    SqlParams params;
    std::string sql = "UPDATE documents SET check=? WHERE id=?";

    // 添加参数
    SQLPARAMS_PUSH(params, "i", int, obj.getCheck());  // 更新核对/反核对状态
    SQLPARAMS_PUSH(params, "s", std::string, obj.getId());     // 根据 ID 进行条件更新
    return sqlSession->executeUpdate(sql, params) > 0;
}