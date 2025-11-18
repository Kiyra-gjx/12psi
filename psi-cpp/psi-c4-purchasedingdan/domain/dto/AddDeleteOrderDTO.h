#ifndef _ADDDELETEORDERDTO_H_
#define _ADDDELETEORDERDTO_H_

#include "../GlobalInclude.h"
#include "oatpp/core/macro/codegen.hpp"

/* Begin DTO code-generation */
#include "oatpp/codegen/dto/base_define.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class AddOrderDTO : public oatpp::DTO {
	DTO_INIT(AddOrderDTO, DTO);

public:
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.id");
		info->required = false;
	};

	DTO_FIELD(String, source);
	DTO_FIELD_INFO(source) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.source");
		info->required = true;
	}

	DTO_FIELD(String, supplier);
	DTO_FIELD_INFO(supplier) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.supplier");
		info->required = true;
	};

	DTO_FIELD(String, time);
	DTO_FIELD_INFO(time) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.time");
		info->required = true;
	};

	DTO_FIELD(String, number);
	DTO_FIELD_INFO(number) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.number");
		info->required = true;
	};

	DTO_FIELD(Int64, total);
	DTO_FIELD_INFO(total) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.total");
		info->required = true;
	};

	DTO_FIELD(Int64, actual);
	DTO_FIELD_INFO(actual) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.actual");
		info->required = true;
	};

	DTO_FIELD(String, people);
	DTO_FIELD_INFO(people) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.people");
		info->required = false;
	};

	DTO_FIELD(String, arrival);
	DTO_FIELD_INFO(arrival) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.arrival");
		info->required = false;
	};

	DTO_FIELD(String, logistics);
	DTO_FIELD_INFO(logistics) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.logistics");
		info->required = false;
	};

	DTO_FIELD(String, file);
	DTO_FIELD_INFO(file) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.file");
		info->required = false;
	};

	DTO_FIELD(String, data);
	DTO_FIELD_INFO(data) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.data");
		info->required = false;
	};

	DTO_FIELD(Int8, examine);
	DTO_FIELD_INFO(examine) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.examine");
		info->required = true;
	};

	DTO_FIELD(Int8, state);
	DTO_FIELD_INFO(state) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.state");
		info->required = true;
	};

	DTO_FIELD(String, user);
	DTO_FIELD_INFO(user) {
		info->description = ZH_WORDS_GETTER("purchasedingdan.add.field.user");
		info->required = true;
	};

};

/* End DTO code-generation */
#include OATPP_CODEGEN_END(DTO)

#endif // _ADDDELETEORDERDTO_H_

