#include"returnorderDAO.h"
#include"../domain/do/ReturnorderInfoDO.h"
bool BreInfoDAO::updateBreInfo(const BreInfoDO& obj)
{
    std::string sql = "UPDATE bre_info  SET pid=?,source=?,goods=?,attr=?,unit=?,warehouse=?,\
batch=?,mfd=?,price=?,nums=?,serial=?,discount=?,dsc=?,total=?,tax=?,tat=?,tpt=?,data=? WHERE id=?";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, obj.getPid());
    SQLPARAMS_PUSH(params, "s", std::string, obj.getSource());
    SQLPARAMS_PUSH(params, "s", std::string, obj.getGoods());
    SQLPARAMS_PUSH(params, "s", std::string, obj.getAttr());
    SQLPARAMS_PUSH(params, "s", std::string, obj.getUnit());
    SQLPARAMS_PUSH(params, "s", std::string, obj.getWarehouse());
    SQLPARAMS_PUSH(params, "s", std::string, obj.getBatch());
    SQLPARAMS_PUSH(params, "s", std::string, obj.getMfd());
    SQLPARAMS_PUSH(params, "d", double, obj.getPrice());
    SQLPARAMS_PUSH(params, "d", double, obj.getNums());
    SQLPARAMS_PUSH(params, "s", std::string, obj.getSerial());
    SQLPARAMS_PUSH(params, "d", double, obj.getDiscount());
    SQLPARAMS_PUSH(params, "d", double, obj.getDsc());
    SQLPARAMS_PUSH(params, "d", double, obj.getTotal());
    SQLPARAMS_PUSH(params, "d", double, obj.getTax());
    SQLPARAMS_PUSH(params, "s", double, obj.getTat());
    SQLPARAMS_PUSH(params, "d", double, obj.getTpt());
    SQLPARAMS_PUSH(params, "s", std::string, obj.getData());
    SQLPARAMS_PUSH(params, "s", std::string, obj.getId());
    return sqlSession->executeUpdate(sql, params) > 0;
}