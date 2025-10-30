package com.zeroone.star.storemanagement.service.impl;

import com.zeroone.star.project.dto.j2.store.OtherInListAddDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDetailDTO;
import com.zeroone.star.project.dto.j2.store.OtherOutListInfoDTO;
import com.zeroone.star.storemanagement.entity.EntryDO;
import com.zeroone.star.storemanagement.entity.ExtryInfoDO;
import org.mapstruct.Mapper;

@Mapper(componentModel = "spring")
public interface MsEntryMapper {
    /**
     * 映射DTO
     * @param entity 实体
     * @return DTO
     */
    OtherInListDetailDTO entryToOtherInListDetailDTO(EntryDO entity);

    /**
     * 映射DTO
     * @param entity ExtryInfoDO
     * @return DTO
     */
    OtherOutListInfoDTO extryInfoToOtherOutListInfoDTO(ExtryInfoDO entity);

    /**
     * 映射实体
     * @param dto EntryAddDTO
     * @return 实体
     */
    EntryDO addDtoToEntry(OtherInListAddDTO dto);

    /**
     * 映射实体
     * @param dto EntryDTO
     * @return 实体
     */
    EntryDO entryDtoToEntry(OtherInListDTO dto);
}
