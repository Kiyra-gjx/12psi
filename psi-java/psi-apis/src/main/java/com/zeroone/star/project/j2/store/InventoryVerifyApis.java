package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchListDTO;
import com.zeroone.star.project.dto.j2.store.InventoryVerifyListDTO;
import com.zeroone.star.project.dto.j2.store.OtherInListInfoDTO;
import com.zeroone.star.project.dto.j2.store.OtherOutListInfoDTO;
import com.zeroone.star.project.query.j2.store.InventoryVerifyQuery;
import com.zeroone.star.project.vo.JsonVO;

/**
 * @BelongsProject: psi-java
 * @BelongsPackage: com.zeroone.star.project.j2.store
 * @Author: 高
 * @CreateTime: 2025-10-19 18:45
 * @Description: 库存盘点接口
 * @Version: 1.0
 */
public interface InventoryVerifyApis {

    /**
     * 获取盘盈单数据
     * @param inventoryVerifyList 查询参数
     * @return  库存盘点数据
     */
    JsonVO<PageDTO<OtherInListInfoDTO>> getInventoryPlus(InventoryVerifyListDTO inventoryVerifyList);

    /**
     * 获取盘亏单数据
     * @return 库存盘点参数对象数据
     **/
    JsonVO<PageDTO<OtherOutListInfoDTO>> getInventoryReduce(InventoryVerifyListDTO inventoryVerifyList);


    /**
     * 导出库存盘点单
     * @param
     * @return 库存盘点单excel
     */
    JsonVO<byte[]> exportInventoryVerifyExcel(InventoryVerifyListDTO inventoryVerifyList);

}
