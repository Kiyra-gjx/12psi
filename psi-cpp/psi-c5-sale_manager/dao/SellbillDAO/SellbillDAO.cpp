
#include "stdafx.h"
#include "SellbillDAO.h"
#include "SellbillMapper.h"

PtrSellbillDO SellbillDAO::selectById(const string& id)
{
    string sql = R"(SELECT id, pid, type, source, time, money FROM sell_bill WHERE id = ?)";
    return sqlSession->executeQueryOne<PtrSellbillDO>(sql, SellbillMapper(), "%s", id);
}


//bool SellbillDAO::insert(PtrSellbillDO& bill)
//{
//    string sql = R"(INSERT INTO sell_bill (id, pid, type, source, time, money) VALUES (?, ?, ?, ?, ?, ?))";
//    int rows = sqlSession->executeUpdate(sql,
//        bill->getId().c_str(),
//        bill->getPid().c_str(),
//        bill->getType().c_str(),
//        bill->getSource().c_str(),
//        bill->getTime().c_str(),
//        bill->getMoney()
//    );
//    return rows > 0;
//}

//bool SellbillDAO::update(PtrSellbillDO& bill)
//{
//    string sql = R"(UPDATE sell_bill SET pid = ?, type = ?, source = ?, time = ?, money = ? WHERE id = ?)";
//    int rows = sqlSession->executeUpdate(sql,
//        bill->getPid().c_str(),
//        bill->getType().c_str(),
//        bill->getSource().c_str(),
//        bill->getTime().c_str(),
//        bill->getMoney(),
//        bill->getId().c_str()
//    );
//    return rows > 0;
//}

