package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.vo.JsonVO;
import java.util.List;
import com.zeroone.star.project.dto.j2.store.OtherOutListDTO;


/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 18:46
 * @Description: 其他出库单接口
 * @Version: 1.0
 */
public interface OtherOutApis {
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
     * 修改其他出库单
     * @param otherOutListDTO 修改参数
     * @return 修改结果
     */
    JsonVO<String> updateOtherOutList(OtherOutListDTO otherOutListDTO);


    /**
     * 删除其他出库单
     * @param ids 删除的出库单ID列表
     * @return 删除结果
     */
    JsonVO<String> deleteOtherOutList(List<Integer> ids);




}
