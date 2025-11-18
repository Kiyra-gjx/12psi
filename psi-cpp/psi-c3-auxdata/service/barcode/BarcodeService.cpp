#include "BarcodeService.h"

BarcodePageDTO::Wrapper BarcodeService::listAll(const BarcodeClassPageQuery::Wrapper& query){
   auto pages = BarcodePageDTO::createShared();
   pages->pageIndex =query->pageIndex;
   pages->pageSize =query->pageSize;

   BarcodeDAO dao;
   uint64_t count = dao.count(query);
   if (count <= 0) {
       return pages;
   }
   pages->total = count;
   pages->calcPages();
   auto results=dao.selectWithClassAndPage(query);
   for (auto& result : results) {
       auto dto = BarcodeDTO::createShared();
       ZO_STAR_DOMAIN_DO_TO_DTO(dto, result, id, Id, type, Type, name, Name, content, Content, notes, Notes);
       pages->addData(dto);
   }
   return pages;
}

BarcodeDTO::Wrapper BarcodeService::getById(const std::string& id)
{
    BarcodeDAO dao;
    auto result = dao.selectById(id);
    if (!result) {
        return nullptr;
    }
    auto dto = BarcodeDTO::createShared();
    ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, result, id, Id, type, Type, name, Name, content, Content, notes, Notes);
    return dto;
    
}
