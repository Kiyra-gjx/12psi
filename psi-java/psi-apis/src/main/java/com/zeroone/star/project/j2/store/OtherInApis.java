package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.j2.store.OtherInListAddDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListDetailDTO;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.http.ResponseEntity;
import org.springframework.web.multipart.MultipartFile;

import java.util.List;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 18:46
 * @Description: 其他入库单接口
 * @Version: 1.0
 */
public interface OtherInApis {
    /**
     * 修改其他入库单
     * @param otherInListDTO 修改参数
     * @return 修改结果
     */
    JsonVO<String> updateOtherInList(OtherInListDTO otherInListDTO);

    /**
     * 审核或反审核
     * @param ids 审核id列表
     * @return 修改结果
     */
    JsonVO<String> examine(List<Integer> ids);

    /**
     * 核对或反核对
     * @param ids 核对id列表
     * @return 修改结果
     */
    JsonVO<String> check(List<Integer> ids);

    /**
     * 获取指定其他入库单详细
     * @param id
     * @return
     */
    JsonVO<OtherInListDetailDTO> getOtherInList(String id);

    /**
     * 新增其他入库单
     * @param dto
     * @return
     */
    JsonVO<String> addOtherInList(OtherInListAddDTO dto);

    /**
     * 删除其他入库单(批量)
     * @param ids
     * @return
     */
    JsonVO<List<String>> deleteOtherInList(List<String> ids);

    /**
     *  导入数据
     * @param file 导入的excel文件
     */
    JsonVO<String> importExcel(MultipartFile file);

    /**
     *  导出简单报表
     * @param ids 需要导出的数据的id
     */
    JsonVO<ResponseEntity<byte[]>> exportEasyExcel(List<Integer> ids);

    /**
     *  导出详细报表
     * @param ids 需要导出的数据的id
     */
    JsonVO<ResponseEntity<byte[]>> exportDetailExcel(List<Integer> ids);
}
