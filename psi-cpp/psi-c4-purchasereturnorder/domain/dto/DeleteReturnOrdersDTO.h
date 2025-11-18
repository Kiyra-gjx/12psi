#ifndef _DELETERETURNORDERSDTO_H_
#define _DELETERETURNORDERSDTO_H_

#include "../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 采购退货单 - 删除DTO
 * 用于批量删除退货单
 */
class DeleteReturnOrdersDTO : public oatpp::DTO {
    DTO_INIT(DeleteReturnOrdersDTO, DTO)

        // 要删除的退货单ID列表 (JSON数组字符串)
        API_DTO_FIELD_DEFAULT(List<String>, ids, ZH_WORDS_GETTER("xin.bre.delete.ids"));

    // 删除原因
    API_DTO_FIELD_DEFAULT(String, reason, ZH_WORDS_GETTER("xin.bre.delete.reason"));

    // 操作人ID
    API_DTO_FIELD_DEFAULT(String, operatorId, ZH_WORDS_GETTER("xin.bre.delete.operator"));

    // 是否强制删除 (0:否 1:是)
    API_DTO_FIELD_DEFAULT(Int8, forceDelete, ZH_WORDS_GETTER("xin.bre.delete.force"));

    // 删除时间 (服务器自动填充)
    API_DTO_FIELD_DEFAULT(String, deleteTime, ZH_WORDS_GETTER("xin.bre.delete.time"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // _DELETERETURNORDERSDTO_H_