package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.j2.store.OtherOutListDTO;
import com.zeroone.star.project.dto.j2.store.OtherOutListInfoDTO;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;
/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.j2.store
 * @Author: nixiangtaiduole!
 * @CreateTime: 2025-10-20 14:36
 * @Description: 其他出库单接口
 * @Version: 1.0
 */public interface OtherOutApis {
    /**
     * 修改其他出库单
     * @param otherOutListDTO 修改参数
     * @return 修改结果
     */
    JsonVO<String> updateOtherOutList(OtherOutListDTO otherOutListDTO);

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
     * 获取指定其他出库单详细
     * @param id
     * @return
     */
    JsonVO<OtherOutListInfoDTO> getOtherOutList(String id);

    /**
     * 新增其他出库单
     * @param dto
     * @return
     */
    JsonVO<String> addOtherOutList(OtherOutListInfoDTO dto);

    /**
     * 删除其他出库单(批量)
     * @param ids
     * @return
     */
    JsonVO<List<String>> deleteOtherInList(List<String> ids);

}
