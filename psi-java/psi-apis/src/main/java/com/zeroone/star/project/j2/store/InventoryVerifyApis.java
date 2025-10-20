package com.zeroone.star.project.j2.store;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.store.BatchListDTO;
import com.zeroone.star.project.dto.j2.store.InventoryVerifyListDTO;
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
     * 查询盘存库点数据
     * @param query 查询参数
     * @return  库存盘点数据
     */
    JsonVO<PageDTO<InventoryVerifyListDTO>> listInventoryVerify(InventoryVerifyQuery query);

    /**
     * 查询条件查询库存盘点参数属性数据
     * @return 库存盘点参数对象数据
     **/
    JsonVO<InventoryVerifyQuery> getinventoryVerifyQueryProperty();


    /**
     * 导出库存盘点单
     * @param
     * @return 库存盘点单excel
     */
    JsonVO<byte[]> exportInventoryVerifyExcel();

}
