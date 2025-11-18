#include "stdafx.h"
#include "SrebillDAO.h"
#include "SrebillMapper.h"



uint64_t SrebillDAO::insert(const PtSrebillDO& billDO) {
    string sql = "INSERT INTO `sre_bill` (`id`,`pid`,`type`,`source`,`time`,`money`) VALUES (?, ?, ?, ?, ?, ?)";
    return sqlSession->executeInsert(sql, "%s%s%s%s%dt%d", billDO->getId(), billDO->getPid(), billDO->getType(),
        billDO->getSource(), billDO->getTime(), billDO->getMoney());
}

bool SrebillDAO::update(const PtSrebillDO& dto) {
    string sql = "UPDATE `sre_bill` SET `pid`=?, `type`=?, `source`=?, `time`=?, `money`=? WHERE `id`=?";
    return sqlSession->executeUpdate(sql, "%s%s%s%dt%d%s", dto->getPid(), dto->getType(),
        dto->getSource(), dto->getTime(), dto->getMoney(), dto->getId()) == 1;
}

bool SrebillDAO::removeById(const string& id) {
    string sql = "DELETE FROM `sre_bill` WHERE `id`=?";
    return sqlSession->executeUpdate(sql, "%s", id) == 1;
}

bool SrebillDAO::removeByPid(const string& pid) {
    string sql = "DELETE FROM `sre_bill` WHERE `pid`=?";
    return sqlSession->executeUpdate(sql, "%s", pid) >= 0;
}

//PtSrebillDO SrebillDAO::selectById(const string& id) {
//    string sql = "SELECT * FROM `sre_bill` WHERE `id`=?";
//    SrebillMapper mapper;
//    return sqlSession->executeQueryOne<PtSrebillDO>(sql, mapper, "%s", id);
//}
//
//list<PtSrebillDO> SrebillDAO::selectByPid(const string& pid) {
//    string sql = "SELECT * FROM `sre_bill` WHERE `pid`=?";
//    SrebillMapper mapper;
//    return sqlSession->executeQuery<PtSrebillDO>(sql, mapper, "%s", pid);
//
//}
