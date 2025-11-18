#include "stdafx.h"
#include "SorInfoDAO.h"
#include "SorInfoMapper.h"
#include "id/UuidFacade.h"


bool SorInfoDAO::insertSorInfo(const SorInfoDO& soiDO)
{
	string id = soiDO.getId();
	string pid = soiDO.getPid();
	string goods = soiDO.getGoods();
	string attr = soiDO.getAttr();
	string unit = soiDO.getUnit();
	string warehouse = soiDO.getWarehouse();
	double price = soiDO.getPrice();
	double nums = soiDO.getNums();
	double discount = soiDO.getDiscount();
	double dsc = soiDO.getDsc();
	double total = soiDO.getTotal();
	double tax = soiDO.getTax();
	double tat = soiDO.getTat();
	double tpt = soiDO.getTpt();
	string data = soiDO.getData();
	double handle = soiDO.getHandle();

	if (id.empty() || pid.empty() || goods.empty())
		return false;
	// 构建SQL语句
	char sqlBuffer[1024] =
		"INSERT INTO `sor_info` (`id`,`pid`,`goods`,`attr`,\
								`unit`,`warehouse`,`price`,`nums`,\
								`discouce`,`dsc`,`total`,`tax`,`tat`,`tpt`,`data`,`handle`)\
		VALUE ('%s','%s','%s','%s','%s','%s','%d','%d','%d','%d','%d','%d','%d','%s','%d',)";
	snprintf
	(
		sqlBuffer,
		sizeof(sqlBuffer),
		id.c_str(),
		pid.c_str(),
		goods.c_str(),
		attr.c_str(),
		unit.c_str(),
		warehouse.c_str(),
		price,
		nums,
		discount,
		dsc,
		total,
		tax,
		tat,
		tpt,
		data.c_str(),
		handle
	);
	// 获得数据库会话并执行SQL
	SqlSession* session = getSqlSession();
	int affectedRows = session->executeUpdate(sqlBuffer);
	return affectedRows > 0;

}



int64_t SorInfoDAO::count()
{
	return 0;
}


int SorInfoDAO::deleteSorInfoByID(const string& id)
{
	if (id.empty())
	{
		std::cerr << "SorInfoDAO::deleteSorInfoByID: 查询失败，ID为空" << std::endl;
		return 0;
	}
	try
	{
		char sqlBuffer[1024] = { 0 };
		string sqlTemplate = "DELETE FROM `sor_info` WHERE `id`='%s'";

		snprintf(sqlBuffer, sizeof(sqlBuffer), sqlTemplate.c_str(), id.c_str());

		SqlSession* session = getSqlSession();
		int affectedRows = session->executeUpdate(sqlBuffer);

		return affectedRows;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error delete in SorInfoDAO::deleteSorInfoByID" << std::endl;
		return 0;
	}

}

int SorInfoDAO::updateSorInfo(const SorInfoDO& soiDO)
{
	string id = soiDO.getId();
	if (id.empty())
	{
		std::cerr << "SorInfoDAO::updateSorInfo: ID cannot be empty." << std::endl;
		return 0;
	}
	try
	{
		string pid = soiDO.getPid();
		string goods = soiDO.getGoods();
		string attr = soiDO.getAttr();
		string unit = soiDO.getUnit();
		string warehouse = soiDO.getWarehouse();
		double price = soiDO.getPrice();
		double nums = soiDO.getNums();
		double discount = soiDO.getDiscount();
		double dsc = soiDO.getDsc();
		double total = soiDO.getTotal();
		double tax = soiDO.getTax();
		double tat = soiDO.getTat();
		double tpt = soiDO.getTpt();
		string data = soiDO.getData();
		double handle = soiDO.getHandle();

		char sqlBuffer[1024] = { 0 };
		string sqlTemplate = "UPDATE UPDATE sor_info \
			SET\
			id = %s,\
			pid = %s,\
			goods = %s,\
			attr = %s,\
			unit = %s,\
			warehouse = %s,\
			price = %d,\
			nums = %d,\
			discount = %d,\
			dsc = %d,\
			total = %d,\
			tax = %d,\
			tat = %d,\
			tpt = %d,\
			data = %s,\
			handle = %d,\
			WHERE id = %s ";
		snprintf(sqlBuffer, sizeof(sqlBuffer),
			id.c_str(), pid.c_str(), goods.c_str(), attr.c_str(), unit.c_str(), warehouse.c_str(), price, nums, discount, dsc, total, tax, tat, tpt, data.c_str(), handle
		);

		SqlSession* session = getSqlSession();
		int affectedRows = session->executeUpdate(sqlBuffer);

		if (affectedRows > 0)
			std::cout << "SorInfo with ID " << id << " updated successfully." << std::endl;
		else
			std::cout << "No SorInfo found with ID " << id << "." << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error updating SorInfo with ID " << id << ": " << e.what() << std::endl;
		return 0;
	}
	return 0;
}

bool SorInfoDAO::importData(const PayloadDTO& payload, const SorImportDTO::Wrapper& dto,const std::string &sor_uuid)
{
	UuidFacade uf;
	for (auto& item : (*dto->items)) {
		std::string insertSorInfoSQL = "INSERT INTO `sor_info` (\
        `id`, `pid`, `goods`, `attr`, `unit`, `warehouse`, `price`, `nums`,\
        `discount`, `dsc`, `total`, `tax`, `tat`, `tpt`, `data`\
        ) VALUES( '" + uf.genUuid() + "','" + sor_uuid + "','" + item->goods + "'," + \
			(item->attr->empty() ? "NULL" : "'" + item->attr + "'") + "," + \
			(item->unit->empty() ? "NULL" : "'" + item->unit + "'") + ",'" + \
			item->warehouse + "'," + std::to_string(item->price) + "," + \
			std::to_string(item->nums) + "," + std::to_string(item->discount) + "," + \
			std::to_string(item->dsc ? item->dsc : oatpp::Float64(0.0000)) + "," + \
			std::to_string(item->total ? item->total : oatpp::Float64(0.0000)) + "," + \
			std::to_string(item->tax) + "," + \
			std::to_string(item->tat ? item->tat : oatpp::Float64(0.0000)) + "," + \
			std::to_string(item->tpt ? item->tpt : oatpp::Float64(0.0000)) + "," + \
			(item->data->empty() ? "NULL" : "'" + item->data + "'") + ")";
		if (sqlSession->executeUpdate(insertSorInfoSQL) == 0) {
			//sqlSession->rollbackTransaction();
			return false;
		}
		//cout << "item get\n";
	}
	return true;
}


std::list<PtrSorInfoDO> SorInfoDAO::selectByOrderId(string id) {
	string sql = "select id,pid,goods,attr,unit,warehouse,price,nums,discount,dsc,total,`data` "
		"FROM sor_info "
		"WHERE pid = ?";
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, id);
	return sqlSession->executeQuery<PtrSorInfoDO>(sql, SorInfoByPidMapper(), params);
}









