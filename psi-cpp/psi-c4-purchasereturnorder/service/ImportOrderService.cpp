#include "ImportOrderService.h"
#include "stdafx.h"
#include "../dao/ImportDAO.h"
#include "id/UuidFacade.h"
#include "ExcelComponent.h"
#include "domain/do/LogDO.h"
#include "GBKToUTF-8.h"
// 放到最后导入防止编译冲突
#include "NacosClient.h"


#define TEST_EXCEL_SN ZH_WORDS_GETTER("excel.sheet.s1")

/**
 * 设置采购退货单主数据
 * @param cnt       Excel行数据
 * @param breData   采购退货单主数据实体（输出参数）
 * @param id        生成的单据主键ID（输出参数）
 * @return 是否设置成功
 */
bool ImportOrderService::setBreDO(vector<string>& cnt, BreDO& breData, string& id)
{
    // 单据信息必填项校验（供应商、供应商拼音首字母、单据日期、单据编号、实际金额、实收金额、结算账户）
    if (cnt[0].empty() || cnt[1].empty() || cnt[2].empty() || cnt[3].empty() || cnt[5].empty() || cnt[6].empty() || cnt[7].empty()) {
        return false;
    }

    const string supName = cnt[0];
    const string supPy = cnt[1];
    const string userName = cnt[7];
    ImportDAO dao;

    // 查询供应商信息
    auto supplier = dao.selectSupplier(supName, supPy);
    if (!supplier) {
        return false;
    }

    // 查询结算用户信息
    auto user = dao.selectUser(userName);

    // 赋值基础单据信息
    breData.setSupplier(supplier->getId());    // 供应商ID
    breData.setTime(cnt[2]);                  // 单据日期（对应原C列）
    breData.setNumber(cnt[3]);                // 单据编号（对应原D列）
    breData.setTotal(std::stod(cnt[4]));      // 单据金额（对应原E列）
    breData.setActual(std::stod(cnt[5]));     // 实际金额（对应原F列）
    breData.setMoney(std::stod(cnt[6]));      // 实收金额（对应原G列）
    breData.setAccount(user->getId());               // 结算账户（对应原H列）
    breData.setPeople(cnt[8]);                // 关联人员（对应原I列）
    breData.setLogistics(cnt[9]);             // 物流信息（对应原J列）

    // 生成单据主键并初始化状态字段
    UuidFacade uf;
    const string orderId = uf.genUuid();
    breData.setId(orderId);
    breData.setExamine(0);
    breData.setNucleus(0);
    breData.setCse(0);
    breData.setInvoice(0);
    breData.setCheck(0);
    breData.setSource("0");
    breData.setFrame("0");
    breData.setCost(0.0);
    breData.setUser(user->getId());  // 操作用户（取自结算账户列）

    id = orderId;
    return true;
}

/**
 * 设置采购退货单商品明细数据
 * @param cnt           Excel行数据
 * @param breInfoData   商品明细实体（输出参数）
 * @param pid           关联的单据主键ID
 * @return 是否设置成功
 */
bool ImportOrderService::setBreInfoDO(const vector<string>& cnt, BreInfoDO& breInfoData, const string& pid)
{
    // 商品明细必填项校验（商品名称、拼音首字母、仓库名、生成日期、单价、数量、税率）
    if (cnt[11].empty() || cnt[12].empty() || cnt[15].empty() || cnt[17].empty() || cnt[18].empty() || cnt[19].empty() || cnt[24].empty()) {
        return false;
    }

    ImportDAO dao;

    // 查询商品信息（通过名称和拼音首字母）
    const string goodsName = cnt[11];  // 对应原K列（原下标10）
    const string py = cnt[12];         // 对应原L列（原下标11）
    auto good = dao.selectByName(goodsName, py);

    // 查询仓库信息（通过仓库名称）
    const string warehouseName = cnt[15];  // 对应原P列（原下标14）
    auto warehouse = dao.selectByWarehouse(warehouseName);

    if (!good || !warehouse) {
        return false;
    }

    // 解析基础数据（处理可能的类型转换异常）
    double price = 0.0;        // 单价（对应原S列，原下标17）
    double quantity = 0.0;     // 数量（对应原T列，原下标18）
    double discountRate = 0.0; // 折扣率（对应原V列，原下标20）
    double taxRate = 0.0;      // 税率（对应原Y列，原下标23）
    try {
        price = std::stod(cnt[18]);
        quantity = std::stod(cnt[19]);
        discountRate = std::stod(cnt[21]);
        taxRate = std::stod(cnt[24]);
    }
    catch (const std::exception& e) {
        // 捕获数值转换异常（如非数字字符串）
        return false;
    }

    // 计算折扣额（优先使用Excel值，无值则自动计算）
    double discountAmount = 0.0;
    if (!cnt[22].empty()) {  // 对应原W列（原下标21）
        try {
            discountAmount = std::stod(cnt[22]);
        }
        catch (const std::exception& e) {
            return false;
        }
    }
    else {
        discountAmount = price * quantity * (discountRate / 100.0);
    }

    // 计算金额（优先使用Excel值，无值则自动计算）
    double totalAmount = 0.0;
    if (!cnt[23].empty()) {  // 对应原X列（原下标22）
        try {
            totalAmount = std::stod(cnt[23]);
        }
        catch (const std::exception& e) {
            return false;
        }
    }
    else {
        totalAmount = price * quantity - discountAmount;
    }

    // 计算税额（优先使用Excel值，无值则自动计算）
    double taxAmount = 0.0;
    if (!cnt[25].empty()) {  // 对应原Z列（原下标24）
        try {
            taxAmount = std::stod(cnt[25]);
        }
        catch (const std::exception& e) {
            return false;
        }
    }
    else {
        taxAmount = totalAmount * (taxRate / 100.0);
    }

    // 计算价税合计（优先使用Excel值，无值则自动计算）
    double totalWithTax = 0.0;
    if (!cnt[26].empty()) {  // 对应原AA列（原下标25）
        try {
            totalWithTax = std::stod(cnt[26]);
        }
        catch (const std::exception& e) {
            return false;
        }
    }
    else {
        totalWithTax = totalAmount + taxAmount;
    }

    // 设置商品明细数据
    breInfoData.setGoods(good->getId());         // 商品ID
    breInfoData.setAttr(cnt[13]);                // 辅助属性（对应原M列，原下标12）
    breInfoData.setUnit(cnt[14]);                // 单位（对应原N列，原下标13）
    breInfoData.setWarehouse(warehouse->getId()); // 仓库ID
    breInfoData.setBatch(cnt[16]);               // 批次号（对应原Q列，原下标15）
    breInfoData.setMfd(cnt[17]);                 // 生产日期（对应原R列，原下标16）
    breInfoData.setPrice(price);                 // 单价
    breInfoData.setNums(quantity);               // 数量（变量名优化：nums → quantity）
    breInfoData.setSerial(cnt[20]);              // 序列号（对应原U列，原下标19）
    breInfoData.setDiscount(discountRate);       // 折扣率(%)
    breInfoData.setDsc(discountAmount);          // 折扣额（变量名优化：dsc → discountAmount）
    breInfoData.setTotal(totalAmount);           // 金额
    breInfoData.setTax(taxRate);                 // 税率(%)
    breInfoData.setTat(taxAmount);               // 税额（变量名优化：tat → taxAmount）
    breInfoData.setTpt(totalWithTax);            // 价税合计（变量名优化：tpt → totalWithTax）

    // 生成明细主键并关联单据
    UuidFacade uf;
    breInfoData.setId(uf.genUuid());
    breInfoData.setSource("0");
    breInfoData.setPid(pid);

    return true;
}

/**
 * 导入采购退货单数据
 * @param file  Excel文件二进制数据
 * @return 导入结果列表（成功/失败状态 + 提示信息）
 */
vector<pair<bool, string>> ImportOrderService::ImportData(oatpp::String file)
{
    vector<pair<bool, string>> result;
    const string sheetName = TEST_EXCEL_SN;
    ExcelComponent excel;

    // 读取Excel数据到向量（行→列结构）
    auto excelData = excel.readIntoVector(file->data(), file->size(), sheetName);
    const int rowCount = excelData.size();

    int currentRow = 2;  // 从第3行（下标2）开始解析（跳过表头）
    while (currentRow < rowCount) {


        // 跳过空行，寻找有效单据起始行
        while (currentRow < rowCount && excelData[currentRow][0].empty()) {
            currentRow++;
        }
        if (currentRow >= rowCount) {
            break;
        }
        currentRow;
        // 解析单据主信息
        BreDO breData;
        string orderId;
        if (!setBreDO(excelData[currentRow], breData, orderId)) {
            result.emplace_back(false, "Row " + std::to_string(currentRow + 1) + ": order data error");
            currentRow++;
            continue;
        }


        ImportDAO dao;
        bool isImportSuccess = dao.insert(breData);  // 先插入主表

        if (isImportSuccess)
            cout << "insert bre ok" << endl;

        // 解析同单据的商品明细行
        int detailRow = currentRow;
        const string currentMainKey = excelData[currentRow][0];  // 主表标识（用于关联明细）

        while (detailRow < rowCount) {
            // 终止条件：下一个主表行或空行（非当前单据的明细）
            const string& detailMainKey = excelData[detailRow][0];
            if (!detailMainKey.empty() && detailMainKey != currentMainKey) {
                break;
            }
            cout << "row:" << detailRow << "   ";

            // 解析当前明细行
            BreInfoDO goodsDetail;
            if (!setBreInfoDO(excelData[detailRow], goodsDetail, orderId)) {
                result.emplace_back(false, "Row " + std::to_string(detailRow + 1) + ": goods data error");
                detailRow++;  // 失败后记得 ++，不然会进入死循环
                continue;
            }

            isImportSuccess &= dao.insert(goodsDetail);

            if (isImportSuccess)
                cout << "insert bre_info ok";
            cout << endl;

            detailRow++;
        }

        // 处理导入结果
        if (!isImportSuccess) {
            result.emplace_back(false, "Row " + std::to_string(currentRow + 1) + ": Import Database failed");
            currentRow = detailRow;
            continue;
        }

        // 记录操作日志
        const string logInfo = gbk_to_utf8("导入采购退货单 [" + orderId + " ]");
        if (LogDO::write_log(logInfo, breData.getAccount()) != 0) {
            result.emplace_back(true, "Row " + std::to_string(currentRow + 1) + ": Import success, ID: " + orderId);
        }
        else {
            result.emplace_back(false, "Row " + std::to_string(currentRow + 1) + ": Import success but log insert failed");
        }

        currentRow = detailRow;
    }

    // 调试输出结果
    for (const auto& result : result)
    {
        cout << "first:" << result.first << "   " << "second:" << result.second << endl;
    }

    return result;
}