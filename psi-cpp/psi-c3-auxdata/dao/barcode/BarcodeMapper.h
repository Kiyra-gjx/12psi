#pragma once

class BarcodeMapper :public Mapper<BarcodeDO> {
public:
	BarcodeDO mapper(ResultSet* resultSet)const override {
		BarcodeDO data;
		data.setId(resultSet->getString(1));
		data.setType(resultSet->getInt(2));
		data.setName(resultSet->getString(3));
		data.setContent(resultSet->getString(4));
		data.setNotes(resultSet->getString(5));
		return data;
	}

};
class PtrBarcodeMapper : public Mapper<PtrBarcodeDO>
{
public:
	PtrBarcodeDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<BarcodeDO>();
		data->setId(resultSet->getString(1));
		data->setType(resultSet->getInt(2));
		data->setName(resultSet->getString(3));
		data->setContent(resultSet->getString(4));
		data->setNotes(resultSet->getString(5));
		return data;
	}
};
