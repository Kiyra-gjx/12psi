package com.zeroone.star.storemanagement.convertor;

import com.zeroone.star.project.dto.j2.store.OtherInListAddDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDetailDTO;
import com.zeroone.star.project.dto.j2.store.OtherOutListInfoDTO;
import com.zeroone.star.storemanagement.entity.EntryDO;
import com.zeroone.star.storemanagement.entity.ExtryInfoDO;
import org.mapstruct.Mapper;
import org.mapstruct.Mapping;

@Mapper(componentModel = "spring" ,uses={JsonTypeConvertor.class})
public interface MsEntryMapper {
    /**
     * 映射DTO
     * @param entity 实体
     * @return DTO
     */
    @Mapping(target = "file", source = "file", qualifiedByName = "jsonToFile")
    @Mapping(target = "logistics", source = "logistics", qualifiedByName = "jsonToLogistics")
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
    @Mapping(target = "file", source = "file", qualifiedByName = "fileToJson")
    @Mapping(target = "logistics", source = "logistics", qualifiedByName = "logisticsToJson")
    EntryDO addDtoToEntry(OtherInListAddDTO dto);

    /**
     * 映射实体
     * @param dto OtherInListDetailDto
     * @return 实体
     */
    @Mapping(target = "file", source = "file", qualifiedByName = "fileToJson")
    @Mapping(target = "logistics", source = "logistics", qualifiedByName = "logisticsToJson")
    EntryDO otherInListDetailDtoToEntry(OtherInListDetailDTO dto);
}
