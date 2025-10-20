package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.http.ResponseEntity;
import org.springframework.web.multipart.MultipartFile;

import java.util.List;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 18:46
 * @Description: 调拨单接口
 * @Version: 1.0
 */
public interface TransferApis {

    /**
     * 修改调拨单
     * @param dto 调拨单数据
     * @return 修改结果
     */
    JsonVO<String> modifyTransfer(TransferDetailDTO dto);

    /**
     * 批量审核/反审核调拨单
     * @param ids 调拨单id列表
     * @param operation 操作类型（0-未审核，1-已审核）
     * @return 审核/反审核结果
     */
    JsonVO<String> batchAuditTransfer(List<Integer> ids, Integer operation);

    /**
     * 批量删除调拨单
     * @param ids 调拨单id列表
     * @return 删除结果
     */
    JsonVO<String> removeTransfer(List<Integer> ids);

    /**
     * 导入数据
     * @param file 导入文件
     * @return 是否导入成功
     */
    public JsonVO<String> importTransferList(MultipartFile file);


    /**
     * 导出调拨单
     * @param idList 调拨单id列表
     * @return 调拨单excel
     */
    public ResponseEntity<byte[]> exportTransferList(List<String> idList);

    /**
     * 导出调拨单详情
     * @param idList 调拨单id列表
     * @return 调拨单详情excel
     */
    public ResponseEntity<byte[]> exportTransferDetailList(List<String> idList);
}
