package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.j2.store.ModifyTransferRequestDTO;
import com.zeroone.star.project.dto.j2.store.TransferDetailDTO;
import com.zeroone.star.project.dto.j2.store.TransferResponseDTO;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.models.auth.In;
import org.springframework.http.ResponseEntity;
import org.springframework.web.multipart.MultipartFile;

import java.util.List;
import java.util.Map;

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
     * @param requestData 调拨单数据（包含class、cost、info三个字段）
     * @return 修改结果
     */
    TransferResponseDTO modifyTransfer(ModifyTransferRequestDTO requestData);

    /**
     * 审核/反审核调拨单（支持批量）
     * @param parm 调拨单ID
     * @param operation 操作类型
     * @return
     */
    TransferResponseDTO batchAuditTransfer(List<Integer> parm, Integer operation);

    /**
     * 删除调拨单（支持批量）
     * @param parm 调拨单ID
     * @return 删除结果
     */
    TransferResponseDTO removeTransfer(List<Integer> parm);

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
