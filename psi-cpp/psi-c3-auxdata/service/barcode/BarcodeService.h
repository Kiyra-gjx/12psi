#pragma once
#include"../../dao/barcode/BarcodeDAO.h"
#include"../../domain/dto/barcode/BarcodeDTO.h"
#include"../../domain/query/barcode/BarcodeQuery.h"
class BarcodeService {
public:
	BarcodePageDTO::Wrapper listAll(const BarcodeClassPageQuery::Wrapper& query);
	BarcodeDTO::Wrapper getById(const std::string& id);
};
