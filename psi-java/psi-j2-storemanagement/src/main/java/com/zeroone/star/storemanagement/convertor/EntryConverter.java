package com.zeroone.star.storemanagement.convertor;
import com.zeroone.star.project.dto.j2.store.OtherInListDTO;
import com.zeroone.star.storemanagement.entity.EntryDO;
import org.mapstruct.*;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;
/**
 * EntryDO 和 OtherInListDTO 之间的转换器
 * MapStruct会在编译时自动生成这个接口的实现类
 */
@Mapper(componentModel = "spring", // 生成Spring组件，可以通过@Autowired注入
        nullValuePropertyMappingStrategy = NullValuePropertyMappingStrategy.IGNORE, // 忽略null值
        unmappedTargetPolicy = ReportingPolicy.IGNORE) // 忽略未映射的目标属性
public interface EntryConverter {
    
    /**
     * 单个对象转换：DO -> DTO
     * @Mapping注解用于指定特殊的映射规则
     */
    @Mapping(source = "time", target = "time", qualifiedByName = "localDateTimeToString")
    @Mapping(source = "total", target = "total", qualifiedByName = "bigDecimalToDouble")
    @Mapping(source = "cost", target = "cost", qualifiedByName = "bigDecimalToDouble")
    OtherInListDTO toDTO(EntryDO entryDO);
    
    /**
     * 列表转换：DO List -> DTO List
     * MapStruct会自动使用上面的toDTO方法来转换列表中的每个元素
     */
    List<OtherInListDTO> toDTOList(List<EntryDO> entryDOList);
    
    /**
     * 反向转换：DTO -> DO
     */
    @Mapping(source = "time", target = "time", qualifiedByName = "stringToLocalDateTime")
    @Mapping(source = "total", target = "total", qualifiedByName = "doubleToBigDecimal")
    @Mapping(source = "cost", target = "cost", qualifiedByName = "doubleToBigDecimal")
    EntryDO toDO(OtherInListDTO dto);
    
    /**
     * 更新已存在的对象
     * 这在更新操作时很有用，可以将DTO的值更新到已存在的DO对象上
     */
    @Mapping(source = "time", target = "time", qualifiedByName = "stringToLocalDateTime")
    @Mapping(source = "total", target = "total", qualifiedByName = "doubleToBigDecimal")
    @Mapping(source = "cost", target = "cost", qualifiedByName = "doubleToBigDecimal")
    void updateDOFromDTO(OtherInListDTO dto, @MappingTarget EntryDO entryDO);
    
    /**
     * 自定义转换方法：LocalDateTime -> String
     * @Named注解使这个方法可以被@Mapping注解引用
     */
    @Named("localDateTimeToString")
    default String localDateTimeToString(LocalDateTime dateTime) {
        if (dateTime == null) {
            return null;
        }
        return dateTime.format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
    }
    
    /**
     * 自定义转换方法：String -> LocalDateTime
     */
    @Named("stringToLocalDateTime")
    default LocalDateTime stringToLocalDateTime(String dateTimeStr) {
        if (dateTimeStr == null || dateTimeStr.trim().isEmpty()) {
            return null;
        }
        return LocalDateTime.parse(dateTimeStr, DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
    }
    
    /**
     * 自定义转换方法：BigDecimal -> Double
     */
    @Named("bigDecimalToDouble")
    default Double bigDecimalToDouble(BigDecimal value) {
        if (value == null) {
            return null;
        }
        return value.doubleValue();
    }
    
    /**
     * 自定义转换方法：Double -> BigDecimal
     */
    @Named("doubleToBigDecimal")
    default BigDecimal doubleToBigDecimal(Double value) {
        if (value == null) {
            return null;
        }
        return BigDecimal.valueOf(value);
    }
}