#pragma once

//销售单

#ifndef _SELLDTO_H_
#define _SELLDTO_H_

#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 获取销售单列表（条件 + 分页）
class SellListDTO : public oatpp::DTO
{

    DTO_INIT(SellListDTO, DTO);

    //退货单id
    API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("sell.field.listid"), true);
    //关联单据|SELL
    API_DTO_FIELD_DEFAULT(String, source, ZH_WORDS_GETTER("sell.field.source"));
    //所属组织
    API_DTO_FIELD_REQUIRE(String, frame, ZH_WORDS_GETTER("sell.field.frame"), true);
    //客户
    API_DTO_FIELD_REQUIRE(String, customer, ZH_WORDS_GETTER("sell.field.customer"), true);
    //单据时间
    API_DTO_FIELD_REQUIRE(String, time, ZH_WORDS_GETTER("sell.field.time"), true);
    //单据编号
    API_DTO_FIELD_REQUIRE(String, number, ZH_WORDS_GETTER("sell.field.number"), true);
    //单据金额
    API_DTO_FIELD_REQUIRE(Float64, totalMoney, ZH_WORDS_GETTER("sell.field.total"), true);//String改为Float64
    //实际金额
    API_DTO_FIELD_REQUIRE(Float64, actual, ZH_WORDS_GETTER("sell.field.actual"), true);
    //实付金额
    API_DTO_FIELD_REQUIRE(Float64, money, ZH_WORDS_GETTER("sell.field.money"), true);
    //单据费用
    API_DTO_FIELD_REQUIRE(Float64, cost, ZH_WORDS_GETTER("sell.field.cost"), true);
    //结算账户
    API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("sell.field.account"));
    //关联人员
    API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("sell.field.people"));
    //物流信息
    API_DTO_FIELD_REQUIRE(String, logistics, ZH_WORDS_GETTER("sell.field.logitics"), false);
    //单据附件
    API_DTO_FIELD_REQUIRE(String, file, ZH_WORDS_GETTER("sell.field.file"), false);
    //备注信息
    API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("sell.field.data"));
    //扩展信息
    API_DTO_FIELD_REQUIRE(String, more, ZH_WORDS_GETTER("sell.field.more"), false);
    //审核状态[0:未审核|1:已审核]
    API_DTO_FIELD_REQUIRE(Int32, examine, ZH_WORDS_GETTER("sell.field.examine"), true);
    //核销状态[0:未核销|1:部分核销|2:已核销]
    API_DTO_FIELD_REQUIRE(Int32, nucleus, ZH_WORDS_GETTER("sell.field.nucleus"), true);
    //费用状态[0:未结算|1:部分解释|2:已结算|3:无需结算]
    API_DTO_FIELD_REQUIRE(Int32, cse, ZH_WORDS_GETTER("sell.field.cse"), true);
    //发票状态[0:未开票|1:部分开票|2:已开票|3:无需开票]
    API_DTO_FIELD_REQUIRE(Int32, invoice, ZH_WORDS_GETTER("sell.field.invoice"), true);
    //核对状态[0:未核对|1:已核对]
    API_DTO_FIELD_REQUIRE(Int32, check, ZH_WORDS_GETTER("sell.field.check"), true);
    //制单人
    API_DTO_FIELD_REQUIRE(String, user, ZH_WORDS_GETTER("sell.field.user"), true);
};

class InfoDTO : public oatpp::DTO {
    DTO_INIT(InfoDTO, DTO);
    //关联单据|SELL
    API_DTO_FIELD_DEFAULT(String, source, ZH_WORDS_GETTER("sell.field.source"));
    //辅助属性
    API_DTO_FIELD_DEFAULT(String, attr, ZH_WORDS_GETTER("goods.field.attr"));
    //单位
    API_DTO_FIELD_REQUIRE(String, unit, ZH_WORDS_GETTER("goods.field.unit"), true);
    //仓库
    API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("goods.field.warehouse"));
    //批次号
    API_DTO_FIELD_DEFAULT(String, batch, ZH_WORDS_GETTER("goods.field.batch"));
    //生产日期
    API_DTO_FIELD_DEFAULT(String, mfd, ZH_WORDS_GETTER("goods.field.mfd"));
    //单价
    API_DTO_FIELD_REQUIRE(Float64, price, ZH_WORDS_GETTER("goods.field.price"), true);
    //数量
    API_DTO_FIELD_REQUIRE(Float64, nums, ZH_WORDS_GETTER("goods.field.nums"), true);
    //折扣率
    API_DTO_FIELD_REQUIRE(Float64, discount, ZH_WORDS_GETTER("goods.field.discount"), true);
    //折扣额
    API_DTO_FIELD_REQUIRE(Float64, dsc, ZH_WORDS_GETTER("goods.field.dsc"), true);
    //金额
    API_DTO_FIELD_REQUIRE(Float64, total, ZH_WORDS_GETTER("sell.field.total"), true);
    //备注信息
    API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("sell.field.data"));
    //出货数量
    API_DTO_FIELD_DEFAULT(Float64, retreat, ZH_WORDS_GETTER("sell.field.retreat"));
};

//获取前端传入的单项退货商品信息
class SellSingleInfoDTO : public InfoDTO {

    DTO_INIT(SellSingleInfoDTO, InfoDTO);
    //商品id
    API_DTO_FIELD_REQUIRE(String, goods, ZH_WORDS_GETTER("goods.field.goods"), true);
};

//获取数据库传出的单项退货商品信息
class OneSingleInfoDTO : public InfoDTO {

    DTO_INIT(OneSingleInfoDTO, InfoDTO);

    //商品名称
    API_DTO_FIELD_DEFAULT(String, goodsName, ZH_WORDS_GETTER("goods.field.name"));
    //商品编号
    API_DTO_FIELD_DEFAULT(String, goodsNumber, ZH_WORDS_GETTER("goods.field.numebr"));
    //规格型号
    API_DTO_FIELD_DEFAULT(String, goodsSpec, ZH_WORDS_GETTER("goods.field.spec"));
};

// 查询分页信息的DTO
class SellPageDTO : public PageDTO<SellListDTO::Wrapper> {
    DTO_INIT(SellPageDTO, PageDTO<SellListDTO::Wrapper>);
};

// 获取指定销售单详情
class SellDetailDTO : public SellListDTO
{

    DTO_INIT(SellDetailDTO, SellListDTO);
    //出库数量
    API_DTO_FIELD_DEFAULT(Int64, handle, ZH_WORDS_GETTER("saleReturnOrder.field.handle"));
    // 销售单商品信息
    API_DTO_FIELD_REQUIRE(List<OneSingleInfoDTO::Wrapper>, sellinfos, ZH_WORDS_GETTER("sell.field.sellinfos"), true);
};

// 新增销售单
class SellCreateDTO : public SellListDTO {

    DTO_INIT(SellCreateDTO, SellListDTO);

    //传入的退货单商品信息
    API_DTO_FIELD_REQUIRE(List<SellSingleInfoDTO::Wrapper>, sellinfos, ZH_WORDS_GETTER("sell.field.sellinfos"), true);
};

// 删除销售单（支持批量）
class SalenoteDeleteDTO :public oatpp::DTO {
    DTO_INIT(SalenoteDeleteDTO, DTO);

    // 订单ID列表
    DTO_FIELD(List<String>, orderIds);
};

// 批量审核/反审核（销售单）
class SellAuditDTO : public oatpp::DTO {
    DTO_INIT(SellAuditDTO, DTO);
    DTO_FIELD(List<String>, orderIds); // 必填：ID 列表
};

//导入数据
class SellImportDTO : public oatpp::DTO {
    DTO_INIT(SellImportDTO, DTO);

    API_DTO_FIELD_REQUIRE(String, frame, ZH_WORDS_GETTER("sell.fileld.frame"), true);
    API_DTO_FIELD_REQUIRE(String, customer, ZH_WORDS_GETTER("sell.fileld.customer"), true);
    API_DTO_FIELD_REQUIRE(String, time, ZH_WORDS_GETTER("sell.fileld.time"), true);
    API_DTO_FIELD_REQUIRE(String, number, ZH_WORDS_GETTER("sell.fileld.number"), true);
    API_DTO_FIELD_REQUIRE(Float64, total, ZH_WORDS_GETTER("sell.fileld.total"), false);
    API_DTO_FIELD_REQUIRE(Float64, actual, ZH_WORDS_GETTER("sell.fileld.actual"), true);
    API_DTO_FIELD_REQUIRE(String, people, ZH_WORDS_GETTER("sell.fileld.people"), false);
    API_DTO_FIELD_REQUIRE(String, logistics, ZH_WORDS_GETTER("sell.fileld.logistics"), false);
    API_DTO_FIELD_REQUIRE(String, file, ZH_WORDS_GETTER("sell.fileld.file"), false);
    API_DTO_FIELD_REQUIRE(String, data, ZH_WORDS_GETTER("sell.fileld.data"), false);
    API_DTO_FIELD_REQUIRE(String, more, ZH_WORDS_GETTER("sell.fileld.more"), false);
    API_DTO_FIELD_REQUIRE(Int8, examine, ZH_WORDS_GETTER("sell.fileld.examine"), true);
    API_DTO_FIELD_REQUIRE(Int8, nucleus, ZH_WORDS_GETTER("sell.fileld.nucleus"), false);
    API_DTO_FIELD_REQUIRE(Int8, cse, ZH_WORDS_GETTER("sell.fileld.cse"), false);
    API_DTO_FIELD_REQUIRE(Int8, invoice, ZH_WORDS_GETTER("sell.fileld.invoice"), false);
    API_DTO_FIELD_REQUIRE(Int8, check, ZH_WORDS_GETTER("sell.fileld.check"), false);
    API_DTO_FIELD_REQUIRE(String, user, ZH_WORDS_GETTER("sell.fileld.user"), true);
};


// 修改销售单
class SellUpdateDTO :public oatpp::DTO
{
    DTO_INIT(SellUpdateDTO, oatpp::DTO);
    // 销售单id
    API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("sell.fileld.id"));
    // 关联单据|SOURCE
    API_DTO_FIELD_DEFAULT(String, source, ZH_WORDS_GETTER("sell.fileld.source"));
    // 所属组织
    API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("sell.fileld.frame"));
    // 客户
    API_DTO_FIELD_DEFAULT(String, customer, ZH_WORDS_GETTER("sell.fileld.customer"));
    // 单据时间
    API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("sell.fileld.time"));
    // 单据编号
    API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("sell.fileld.number"));
    // 单据金额
    API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("sell.fileld.total"));
    // 实际金额
    API_DTO_FIELD_DEFAULT(Float64, actual, ZH_WORDS_GETTER("sell.fileld.actual"));
    // 实收金额
    API_DTO_FIELD_DEFAULT(Float64, money, ZH_WORDS_GETTER("sell.fileld.money"));
    // 单据费用
    API_DTO_FIELD_DEFAULT(Float64, cost, ZH_WORDS_GETTER("sell.fileld.cost"));
    // 结算账户
    API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("sell.fileld.account"));
    // 关联人员
    API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("sell.fileld.people"));
    // 物流信息
    API_DTO_FIELD_DEFAULT(String, logistics, ZH_WORDS_GETTER("sell.fileld.logistics"));
    // 单据附件
    API_DTO_FIELD_DEFAULT(String, file, ZH_WORDS_GETTER("sell.fileld.file"));
    // 备注信息
    API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("sell.fileld.data"));
    // 扩展信息
    API_DTO_FIELD_DEFAULT(String, more, ZH_WORDS_GETTER("sell.fileld.more"));
    // 审核状态[0:未审核|1:已审核]
    API_DTO_FIELD_DEFAULT(Int32, examine, ZH_WORDS_GETTER("sell.fileld.examine"));
    // 核销状态[0:未核销|1:部分核销|2:已核销]
    API_DTO_FIELD_DEFAULT(Int32, nucleus, ZH_WORDS_GETTER("sell.fileld.nucleus"));
    // 费用状态[0:未结算|1:部分结算|2:已结算|3:无需结算]
    API_DTO_FIELD_DEFAULT(Int32, cse, ZH_WORDS_GETTER("sell.fileld.cse"));
    // 发票状态[0:未开票|1:部分开票|2:已开票|3:无需开票]
    API_DTO_FIELD_DEFAULT(Int32, invoice, ZH_WORDS_GETTER("sell.fileld.invoice"));
    // 核对状态[0:未核对|1:已核对]
    API_DTO_FIELD_DEFAULT(Int32, check, ZH_WORDS_GETTER("sell.fileld.check"));
    // 制单人
    API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("sell.fileld.user"));
    // 关联一个PayloadDTO负载数据对象
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};
class SellUpdatePageDTO : public PageDTO<SellUpdateDTO::Wrapper>
{
    DTO_INIT(SellUpdatePageDTO, PageDTO<SellUpdateDTO::Wrapper>);
};
// 导出简单报表
class SellExportSimpleDTO : public  SellUpdatePageDTO {
    DTO_INIT(SellExportSimpleDTO, SellUpdatePageDTO);
};

// 导出详细报表
class SellExportDetailDTO :public SellUpdatePageDTO {
    DTO_INIT(SellExportDetailDTO, SellUpdatePageDTO);
};

//// 获取生成销售退货单数据
//class SellGenerateReturnDTO : public oatpp::DTO {
//
//    DTO_INIT(SellGenerateReturnDTO, DTO)
//    DTO_FIELD(Int32, source);                      // 关联单据|SELL
//    DTO_FIELD(Int32, frame);                       // 所属组织
//    DTO_FIELD(Int32, customer);                    // 客户
//    DTO_FIELD(Int32, time);                        // 单据时间
//    DTO_FIELD(String, number);                     // 单据编号
//    DTO_FIELD(Float64, total);                     // 单据金额
//    DTO_FIELD(Float64, actual);                    // 实际金额
//    DTO_FIELD(Float64, money);                     // 实付金额
//    DTO_FIELD(Float64, cost);                      // 单据费用
//    DTO_FIELD(Int32, account);                     // 结算账户
//    DTO_FIELD(Int32, people);                      // 关联人员
//    DTO_FIELD(String, logistics);                  // 物流信息
//    DTO_FIELD(String, file);                       // 单据附件
//    DTO_FIELD(String, data);                       // 备注信息
//    DTO_FIELD(String, more);                       // 扩展信息
//    DTO_FIELD(Int8, examine);                      // 审核状态[0:未审核|1:已审核]
//    DTO_FIELD(Int8, nucleus);                      // 核销状态[0:未核销|1:部分核销|2:已核销]
//    DTO_FIELD(Int8, cse);                          // 费用状态[0:未结算|1:部分结算|2:已结算|3:无需结算]
//    DTO_FIELD(Int8, invoice);                      // 发票状态[0:未开票|1:部分开票|2:已开票|3:无需开具]
//    DTO_FIELD(Int8, check);                        // 核对状态[0:未核对|1:已核对]
//    DTO_FIELD(Int32, user);                        // 制单人
//};
// 获取生成销售退货单数据
//class SellToSre : public oatpp::DTO {
//    DTO_INIT(SellToSre, DTO)
//
//        API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("sre.field.id"), false);
//    API_DTO_FIELD_DEFAULT(String, source, ZH_WORDS_GETTER("sre.field.source"), true); // 关联销售单 必要
//    API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("sre.field.frame"), true); // 所属组织 必要
//    API_DTO_FIELD_DEFAULT(String, customer, ZH_WORDS_GETTER("sre.field.customer"), true); // 客户 必要
//    API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("sre.field.time"), true); // 单据时间 必要
//    API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("sre.field.number"), true); // 单据编号 必要
//    API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("sre.field.total"), true); // 单据金额 必要
//    API_DTO_FIELD_DEFAULT(Float64, actual, ZH_WORDS_GETTER("sre.field.actual"), true); // 实际金额 必要
//    API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("sre.field.people"), false); // 关联人员
//    API_DTO_FIELD_DEFAULT(String, logistics, ZH_WORDS_GETTER("sre.field.logistics"), false); // 物流信息
//    API_DTO_FIELD_DEFAULT(String, file, ZH_WORDS_GETTER("sre.field.file"), false); // 单据附件
//    API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("sre.field.data"), false); // 备注信息
//    API_DTO_FIELD_DEFAULT(Int32, examine, ZH_WORDS_GETTER("sre.field.examine"), true); // 审核状态 必要
//    API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("sre.field.user"), true); // 制单人 必要
//    API_DTO_FIELD_DEFAULT(List<Object<SellToSreInfoDTO>>, items, ZH_WORDS_GETTER("sre.field.items"), true); // 退货明细 必要
//};
//
//// 销售退货单明细 DTO
//class SellToSreInfoDTO : public oatpp::DTO {
//    DTO_INIT(SellToSreInfoDTO, DTO)
//
//        API_DTO_FIELD_DEFAULT(String, source, ZH_WORDS_GETTER("sreInfo.field.source"), true); // 关联销售单明细 必要
//    API_DTO_FIELD_DEFAULT(String, goods, ZH_WORDS_GETTER("sreInfo.field.goods"), true); // 所属商品 必要
//    API_DTO_FIELD_DEFAULT(String, attr, ZH_WORDS_GETTER("sreInfo.field.attr"), false); // 辅助属性
//    API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("sreInfo.field.unit"), true); // 单位 必要
//    API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("sreInfo.field.warehouse"), false); // 仓库
//    API_DTO_FIELD_DEFAULT(String, batch, ZH_WORDS_GETTER("sreInfo.field.batch"), false); // 批次号
//    API_DTO_FIELD_DEFAULT(String, mfd, ZH_WORDS_GETTER("sreInfo.field.mfd"), false); // 生产日期
//    API_DTO_FIELD_DEFAULT(Float64, price, ZH_WORDS_GETTER("sreInfo.field.price"), true); // 单价 必要
//    API_DTO_FIELD_DEFAULT(Float64, nums, ZH_WORDS_GETTER("sreInfo.field.nums"), true); // 退货数量 必要
//    API_DTO_FIELD_DEFAULT(String, serial, ZH_WORDS_GETTER("sreInfo.field.serial"), false); // 序列号
//    API_DTO_FIELD_DEFAULT(Float64, discount, ZH_WORDS_GETTER("sreInfo.field.discount"), false); // 折扣率
//    API_DTO_FIELD_DEFAULT(Float64, dsc, ZH_WORDS_GETTER("sreInfo.field.dsc"), false); // 折扣额
//    API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("sreInfo.field.total"), true); // 金额 必要
//    API_DTO_FIELD_DEFAULT(Float64, tax, ZH_WORDS_GETTER("sreInfo.field.tax"), false); // 税率
//    API_DTO_FIELD_DEFAULT(Float64, tat, ZH_WORDS_GETTER("sreInfo.field.tat"), false); // 税额
//    API_DTO_FIELD_DEFAULT(Float64, tpt, ZH_WORDS_GETTER("sreInfo.field.tpt"), true); // 价税合计 必要
//    API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("sreInfo.field.data"), false); // 备注信息
//};
// 
class SellToSreInfoDTO : public oatpp::DTO {
    DTO_INIT(SellToSreInfoDTO, DTO)

    API_DTO_FIELD_REQUIRE(String, source, ZH_WORDS_GETTER("sreInfo.field.source"), false); // 关联详情|SELL
    API_DTO_FIELD_REQUIRE(String, goods, ZH_WORDS_GETTER("sreInfo.field.goods"), true); // 所属商品 必要
    API_DTO_FIELD_REQUIRE(String, attr, ZH_WORDS_GETTER("sreInfo.field.attr"), false); // 辅助属性
    API_DTO_FIELD_REQUIRE(String, unit, ZH_WORDS_GETTER("sreInfo.field.unit"), true); // 单位 必要
    API_DTO_FIELD_REQUIRE(String, warehouse, ZH_WORDS_GETTER("sreInfo.field.warehouse"), false); // 仓库
    API_DTO_FIELD_REQUIRE(String, batch, ZH_WORDS_GETTER("sreInfo.field.batch"), false); // 批次号
    API_DTO_FIELD_REQUIRE(String, mfd, ZH_WORDS_GETTER("sreInfo.field.mfd"), false); // 生产日期
    API_DTO_FIELD_REQUIRE(Float64, price, ZH_WORDS_GETTER("sreInfo.field.price"), true); // 单价 必要
    API_DTO_FIELD_REQUIRE(Float64, nums, ZH_WORDS_GETTER("sreInfo.field.nums"), true); // 数量 必要
    API_DTO_FIELD_REQUIRE(String, serial, ZH_WORDS_GETTER("sreInfo.field.serial"), false); // 序列号
    API_DTO_FIELD_REQUIRE(Float64, discount, ZH_WORDS_GETTER("sreInfo.field.discount"), false); // 折扣率
    API_DTO_FIELD_REQUIRE(Float64, dsc, ZH_WORDS_GETTER("sreInfo.field.dsc"), false); // 折扣额
    API_DTO_FIELD_REQUIRE(Float64, total, ZH_WORDS_GETTER("sreInfo.field.total"), true); // 金额 必要
    API_DTO_FIELD_REQUIRE(Float64, tax, ZH_WORDS_GETTER("sreInfo.field.tax"), false); // 税率
    API_DTO_FIELD_REQUIRE(Float64, tat, ZH_WORDS_GETTER("sreInfo.field.tat"), false); // 税额
    API_DTO_FIELD_REQUIRE(Float64, tpt, ZH_WORDS_GETTER("sreInfo.field.tpt"), true); // 价税合计 必要
    API_DTO_FIELD_REQUIRE(String, data, ZH_WORDS_GETTER("sreInfo.field.data"), false); // 备注信息
};

// 获取生成销售退货单数据
class SellGenerateReturnDTO : public oatpp::DTO {
    DTO_INIT(SellGenerateReturnDTO, DTO)

    API_DTO_FIELD_REQUIRE(String, source, ZH_WORDS_GETTER("sre.field.source"), false); // 关联单据|SELL
    API_DTO_FIELD_REQUIRE(String, frame, ZH_WORDS_GETTER("sre.field.frame"), true); // 所属组织 必要
    API_DTO_FIELD_REQUIRE(String, customer, ZH_WORDS_GETTER("sre.field.customer"), true); // 客户 必要
    API_DTO_FIELD_REQUIRE(String, time, ZH_WORDS_GETTER("sre.field.time"), true); // 单据时间 必要
    API_DTO_FIELD_REQUIRE(String, number, ZH_WORDS_GETTER("sre.field.number"), true); // 单据编号 必要
    API_DTO_FIELD_REQUIRE(Float64, total, ZH_WORDS_GETTER("sre.field.total"), true); // 单据金额 必要
    API_DTO_FIELD_REQUIRE(Float64, actual, ZH_WORDS_GETTER("sre.field.actual"), true); // 实际金额 必要
    API_DTO_FIELD_REQUIRE(Float64, money, ZH_WORDS_GETTER("sre.field.money"), true); // 支付金额 必要
    API_DTO_FIELD_REQUIRE(Float64, cost, ZH_WORDS_GETTER("sre.field.cost"), false); // 单据费用
    API_DTO_FIELD_REQUIRE(String, account, ZH_WORDS_GETTER("sre.field.account"), false); // 结算账户
    API_DTO_FIELD_REQUIRE(String, people, ZH_WORDS_GETTER("sre.field.people"), false); // 关联人员
    API_DTO_FIELD_REQUIRE(String, logistics, ZH_WORDS_GETTER("sre.field.logistics"), false); // 物流信息
    API_DTO_FIELD_REQUIRE(String, file, ZH_WORDS_GETTER("sre.field.file"), false); // 单据附件
    API_DTO_FIELD_REQUIRE(String, data, ZH_WORDS_GETTER("sre.field.data"), false); // 备注信息
    API_DTO_FIELD_REQUIRE(String, more, ZH_WORDS_GETTER("sre.field.more"), false); // 扩展信息
    API_DTO_FIELD_REQUIRE(Int32, examine, ZH_WORDS_GETTER("sre.field.examine"), true); // 审核状态 必要
    API_DTO_FIELD_REQUIRE(Int32, nucleus, ZH_WORDS_GETTER("sre.field.nucleus"), true); // 核销状态 必要
    API_DTO_FIELD_REQUIRE(Int32, cse, ZH_WORDS_GETTER("sre.field.cse"), true); // 费用状态 必要
    API_DTO_FIELD_REQUIRE(Int32, invoice, ZH_WORDS_GETTER("sre.field.invoice"), true); // 发票状态 必要
    API_DTO_FIELD_REQUIRE(Int32, check, ZH_WORDS_GETTER("sre.field.check"), true); // 核对状态 必要
    API_DTO_FIELD_REQUIRE(String, user, ZH_WORDS_GETTER("sre.field.user"), true); // 制单人 必要
    API_DTO_FIELD_REQUIRE(List<Object<SellToSreInfoDTO>>, items, ZH_WORDS_GETTER("sre.field.items"), true); // 退货明细 必要
};

// 销售退货单明细 DTO


#include OATPP_CODEGEN_END(DTO)

#endif 