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
     * 查询商品类别
     * @return 商品类别数据
     *
     */
    JsonVO<String> listGoodsCategory();

    /**
     * 查询商品品牌
     * @return 商品品牌数据
     */
    JsonVO<String> listGoodsBrand();

    /**
     * 查询仓库信息
     * @return 仓库信息数据
     */
    JsonVO<String> listWarehouse();

    /**
     * 导出库存盘点单
     * @param
     * @return 库存盘点单excel
     */
    JsonVO<byte[]> exportInventoryVerifyExcel();

}
