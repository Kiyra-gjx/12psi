<template>
  <div class="sys area">
    <!-- 操作按钮区域 -->
    <div class="operation-bar">
      <div class="operation-left">
        <!-- 搜索按钮 - 小型化 -->
        <GoodSearch
          v-model="searchFormData"
          :config="searchConfig"
          @search="handleSearch"
          class="small-search"
        />
      </div>

      <div class="operation-right">
        <el-button type="primary" @click="handleSettlement" class="action-btn">
          <el-icon><Money /></el-icon>
          结算
        </el-button>
        <el-button type="primary" @click="handleExport" class="action-btn">
          <el-icon><Download /></el-icon>
          导出
        </el-button>
        <el-button type="info" @click="handleRefresh" class="action-btn">
          <el-icon><Refresh /></el-icon>
          刷新
        </el-button>
      </div>
    </div>

    <el-divider class="custom-divider" />

    <!-- 表格区域 - 占据主要空间 -->
    <div class="table-container">
      <el-table
        :data="pagedTableData"
        style="width: 100%"
        v-loading="loading"
        border
        class="grid-table"
        @selection-change="handleSelectionChange"
      >
        <!-- 选择框列 -->
        <el-table-column type="selection" width="55" align="center" />

        <!-- 单据类型列 -->
        <el-table-column prop="orderType" label="单据类型" width="120" align="center">
          <template #default="scope">
            {{ scope.row.orderType }}
          </template>
        </el-table-column>

        <!-- 所属组织列 -->
        <el-table-column prop="orgName" label="所属组织" width="120" align="center">
          <template #default="scope">
            {{ scope.row.orgName }}
          </template>
        </el-table-column>

        <!-- 往来单位列 -->
        <el-table-column prop="contactUnit" label="往来单位" width="150">
          <template #default="scope">
            {{ scope.row.contactUnit }}
          </template>
        </el-table-column>

        <!-- 单据时间 -->
        <el-table-column prop="orderDate" label="单据时间" width="120" align="center">
          <template #default="scope">
            {{ scope.row.orderDate }}
          </template>
        </el-table-column>

        <!-- 单据编号 -->
        <el-table-column prop="orderNo" label="单据编号" width="150">
          <template #default="scope">
            {{ scope.row.orderNo }}
          </template>
        </el-table-column>

        <!-- 支出类别 -->
        <el-table-column prop="expenseType" label="支出类别" width="120" align="center">
          <template #default="scope">
            {{ scope.row.expenseType }}
          </template>
        </el-table-column>

        <!-- 结算状态 -->
        <el-table-column prop="settlementStatus" label="结算状态" width="100" align="center">
          <template #default="scope">
            <el-tag :type="getSettlementStatusType(scope.row.settlementStatus)" size="small">
              {{ scope.row.settlementStatus }}
            </el-tag>
          </template>
        </el-table-column>

        <!-- 金额 -->
        <el-table-column prop="amount" label="金额" width="120" align="right">
          <template #default="scope">
            {{ formatCurrency(scope.row.amount) }}
          </template>
        </el-table-column>

        <!-- 已结算金额 -->
        <el-table-column prop="settledAmount" label="已结算金额" width="120" align="right">
          <template #default="scope">
            {{ formatCurrency(scope.row.settledAmount) }}
          </template>
        </el-table-column>

        <!-- 未结算金额 -->
        <el-table-column prop="unsettledAmount" label="未结算金额" width="120" align="right">
          <template #default="scope">
            <span :class="getUnsettledAmountClass(scope.row)">
              {{ formatCurrency(scope.row.unsettledAmount) }}
            </span>
          </template>
        </el-table-column>

        <!-- 结算金额 -->
        <el-table-column prop="settlementAmount" label="结算金额" width="120" align="right">
          <template #default="scope">
            {{ formatCurrency(scope.row.settlementAmount) }}
          </template>
        </el-table-column>
      </el-table>

      <!-- 分页区域和金额统计 -->
      <div class="pagination-container">
        <div class="pagination-left">
          <el-pagination
            v-model:current-page="currentPage"
            v-model:page-size="pageSize"
            :page-sizes="[10, 20, 30, 50]"
            :total="filteredTableData.length"
            layout="total, sizes, prev, pager, next, jumper"
            @size-change="handleSizeChange"
            @current-change="handleCurrentChange"
          />
        </div>
        <div class="amount-summary">
          <div class="amount-item">
            <span class="amount-label">单据总金额：</span>
            <span class="amount-value total-amount">{{ formatCurrency(totalAmount) }}</span>
          </div>
          <div class="amount-item">
            <span class="amount-label">已结算总金额：</span>
            <span class="amount-value settled-amount">{{
              formatCurrency(totalSettledAmount)
            }}</span>
          </div>
          <div class="amount-item">
            <span class="amount-label">未结算总金额：</span>
            <span class="amount-value unsettled-amount">{{
              formatCurrency(totalUnsettledAmount)
            }}</span>
          </div>
        </div>
      </div>
    </div>

    <!-- 结算弹框 -->
    <SettlementDialog
      v-model:visible="showSettlementDialog"
      :selected-records="selectedRecords"
      @settlement-success="handleSettlementSuccess"
    />
  </div>
</template>

<script setup lang="ts">
import { reactive, ref, computed, onMounted } from 'vue'
import { ElMessage } from 'element-plus'
import { Download, Refresh, Money } from '@element-plus/icons-vue'
import GoodSearch from '@/components/goodSearchConpoent/GoodSearchForm.vue'
import SettlementDialog from '@/views/finance/cost/SettlementDialog.vue'
import type { SearchFormData, GoodSearchConfig } from '@/components/goodSearchConpoent/type'

// 搜索配置
const searchConfig: GoodSearchConfig = {
  inline: false, // 弹窗模式

  /** 是否显示商品名称输入框 */
  showGoods: false,
  /** 是否显示单据编号输入框 */
  showNumber: true,
  /** 是否显示供应商选择 */
  showSupplier: true,
  /** 是否显示客户选择 */
  showCustomer: true,
  /** 是否显示关联人员选择 */
  showPeople: false,
  /** 是否显示单据日期范围 */
  showBillDate: true,
  /** 是否显示到货日期范围 */
  showArrivalDate: false,
  /** 是否显示制单人选择 */
  showUser: false,
  /** 是否显示审核状态选择 */
  showExamine: false,
  /** 是否显示入库状态选择 */
  showState: false,
  /** 是否显示备注输入框 */
  showRemark: false,
  /** 是否显示仓库选择 */
  showWarehouse: false,

  // 自定义字段
  customFields: [
    {
      key: 'expenseType',
      type: 'select',
      label: '支出类别',
      options: [
        { label: '采购支出', value: '采购支出' },
        { label: '人力成本', value: '人力成本' },
        { label: '租金支出', value: '租金支出' },
        { label: '水电物业费', value: '水电物业费' },
        { label: '运输物流费', value: '运输物流费' }
      ]
    },
    {
      key: 'settlementStatus',
      type: 'select',
      label: '结算状态',
      options: [
        { label: '未结算', value: '未结算' },
        { label: '部分结算', value: '部分结算' },
        { label: '已结算', value: '已结算' }
      ]
    },
    {
      key: 'orderType',
      type: 'select',
      label: '单据类型',
      options: [
        { label: '采购单', value: '采购单' },
        { label: '采购退货单', value: '采购退货单' },
        { label: '销售单', value: '销售单' },
        { label: '销售退货单', value: '销售退货单' },
        { label: '调拨单', value: '调拨单' },
        { label: '其它入库单', value: '其它入库单' },
        { label: '其它出库单', value: '其它出库单' }
      ]
    }
  ]
}

// 搜索表单数据
const searchFormData = ref<SearchFormData>({
  number: '',
  supplier: '',
  customer: '',
  startTime: '',
  endTime: '',
  expenseType: '',
  settlementStatus: '',
  orderType: ''
})

// 搜索处理
const handleSearch = (formData: SearchFormData) => {
  Object.assign(searchFormData, formData)
  // 重置到第一页
  currentPage.value = 1
  ElMessage.success('搜索完成')
}

// 刷新功能实现
const handleRefresh = () => {
  // 清空搜索表单数据
  Object.keys(searchFormData.value).forEach((key) => {
    (searchFormData.value as any)[key] = ''
  })

  // 重置分页到第一页
  currentPage.value = 1

  // 显示刷新成功消息
  ElMessage.success('数据已刷新')

  console.log('刷新完成，搜索条件已清空', searchFormData)
}

// 导出功能实现
const handleExport = () => {
  // 这里实现导出逻辑
  ElMessage.success('正在导出数据...')

  setTimeout(() => {
    const exportData = prepareExportData()
    downloadCSV(exportData)
    ElMessage.success('导出成功，已开始下载文件')
  }, 1000)
}

// 准备导出数据
const prepareExportData = () => {
  const flatData: any[] = []

  originalTableData.value.forEach((item) => {
    flatData.push({
      单据类型: item.orderType,
      所属组织: item.orgName,
      往来单位: item.contactUnit,
      单据时间: item.orderDate,
      单据编号: item.orderNo,
      支出类别: item.expenseType,
      结算状态: item.settlementStatus,
      金额: item.amount,
      已结算金额: item.settledAmount,
      未结算金额: item.unsettledAmount,
      结算金额: item.settlementAmount
    })
  })

  return flatData
}

// 下载CSV文件
const downloadCSV = (data: any[]) => {
  const headers = Object.keys(data[0]).join(',')
  const rows = data.map((row) =>
    Object.values(row)
      .map((value) => `"${value}"`)
      .join(',')
  )

  const csvContent = [headers, ...rows].join('\n')
  const blob = new Blob([csvContent], { type: 'text/csv;charset=utf-8;' })
  const link = document.createElement('a')
  const url = URL.createObjectURL(blob)

  link.setAttribute('href', url)
  link.setAttribute('download', `购销费用表_${new Date().toISOString().split('T')[0]}.csv`)
  link.style.visibility = 'hidden'

  document.body.appendChild(link)
  link.click()
  document.body.removeChild(link)
}

// 格式化金额显示
const formatCurrency = (value: number) => {
  return (
    '¥' +
    value.toLocaleString('zh-CN', {
      minimumFractionDigits: 2,
      maximumFractionDigits: 2
    })
  )
}

// 获取结算状态标签类型
const getSettlementStatusType = (status: string) => {
  switch (status) {
    case '未结算':
      return 'danger'
    case '部分结算':
      return 'warning'
    case '已结算':
      return 'success'
    default:
      return 'info'
  }
}

// 获取未结算金额显示样式
const getUnsettledAmountClass = (row: any) => {
  return row.unsettledAmount > 0 ? 'negative-amount' : 'positive-amount'
}

// 购销费用表数据
const originalTableData = ref([
  {
    id: 1,
    orderType: '采购单',
    orgName: '总部',
    contactUnit: '上海供应商A',
    orderDate: '2023-10-01',
    orderNo: 'CG20231001001',
    expenseType: '采购支出',
    settlementStatus: '未结算',
    amount: 24000,
    settledAmount: 0,
    unsettledAmount: 24000,
    settlementAmount: 24000
  },
  {
    id: 2,
    orderType: '采购退货单',
    orgName: '总部',
    contactUnit: '上海供应商A',
    orderDate: '2023-10-05',
    orderNo: 'CGTH20231005001',
    expenseType: '采购支出',
    settlementStatus: '部分结算',
    amount: -2400,
    settledAmount: -1200,
    unsettledAmount: -1200,
    settlementAmount: -2400
  },
  {
    id: 3,
    orderType: '销售单',
    orgName: '分部',
    contactUnit: '北京客户B',
    orderDate: '2023-10-10',
    orderNo: 'XS20231010001',
    expenseType: '运输物流费',
    settlementStatus: '已结算',
    amount: 38000,
    settledAmount: 38000,
    unsettledAmount: 0,
    settlementAmount: 38000
  },
  {
    id: 4,
    orderType: '销售退货单',
    orgName: '分部',
    contactUnit: '北京客户B',
    orderDate: '2023-10-15',
    orderNo: 'XSTH20231015001',
    expenseType: '运输物流费',
    settlementStatus: '未结算',
    amount: -3800,
    settledAmount: 0,
    unsettledAmount: -3800,
    settlementAmount: -3800
  },
  {
    id: 5,
    orderType: '调拨单',
    orgName: '总部',
    contactUnit: '内部调拨',
    orderDate: '2023-10-20',
    orderNo: 'DB20231020001',
    expenseType: '运输物流费',
    settlementStatus: '部分结算',
    amount: 1500,
    settledAmount: 1000,
    unsettledAmount: 500,
    settlementAmount: 1500
  },
  {
    id: 6,
    orderType: '其它入库单',
    orgName: '总部',
    contactUnit: '杭州供应商E',
    orderDate: '2023-10-25',
    orderNo: 'QT20231025001',
    expenseType: '采购支出',
    settlementStatus: '未结算',
    amount: 11875,
    settledAmount: 0,
    unsettledAmount: 11875,
    settlementAmount: 11875
  },
  {
    id: 7,
    orderType: '其它出库单',
    orgName: '分部',
    contactUnit: '内部调拨',
    orderDate: '2023-10-28',
    orderNo: 'QT20231028001',
    expenseType: '租金支出',
    settlementStatus: '已结算',
    amount: 6080,
    settledAmount: 6080,
    unsettledAmount: 0,
    settlementAmount: 6080
  }
])

// 过滤后的表格数据
const filteredTableData = computed(() => {
  let result = [...originalTableData.value]

  // 根据供应商过滤
  if (searchFormData.value.supplier) {
    result = result.filter((item) => item.contactUnit.includes(searchFormData.value.supplier as string))
  }

  // 根据客户过滤
  if (searchFormData.value.customer) {
    result = result.filter((item) => item.contactUnit.includes(searchFormData.value.customer as string))
  }

  // 根据订单编号过滤
  if (searchFormData.value.number) {
    result = result.filter((item) => item.orderNo.includes(searchFormData.value.number as string))
  }

  // 根据单据类型过滤
  if (searchFormData.value.orderType) {
    result = result.filter((item) => item.orderType === searchFormData.value.orderType)
  }

  // 根据支出类别过滤
  if (searchFormData.value.expenseType) {
    result = result.filter((item) => item.expenseType === searchFormData.value.expenseType)
  }

  // 根据结算状态过滤
  if (searchFormData.value.settlementStatus) {
    result = result.filter((item) => item.settlementStatus === searchFormData.value.settlementStatus)
  }

  // 根据单据日期范围过滤
  if (searchFormData.value.startTime) {
    result = result.filter((item) => item.orderDate >= searchFormData.value.startTime!)
  }

  if (searchFormData.value.endTime) {
    result = result.filter((item) => item.orderDate <= searchFormData.value.endTime!)
  }

  return result
})

// 分页后的表格数据
const pagedTableData = computed(() => {
  const start = (currentPage.value - 1) * pageSize.value
  const end = start + pageSize.value
  return filteredTableData.value.slice(start, end)
})

// 计算总金额统计
const totalAmount = computed(() => {
  return filteredTableData.value.reduce((sum, item) => sum + item.amount, 0)
})

const totalSettledAmount = computed(() => {
  return filteredTableData.value.reduce((sum, item) => sum + item.settledAmount, 0)
})

const totalUnsettledAmount = computed(() => {
  return filteredTableData.value.reduce((sum, item) => sum + item.unsettledAmount, 0)
})

// 分页相关
const currentPage = ref(1)
const pageSize = ref(10)
const loading = ref(false)

// 选择的行数据
const selectedRecords = ref<any[]>([])

// 分页处理
const handleSizeChange = (size: number) => {
  pageSize.value = size
  currentPage.value = 1
}

const handleCurrentChange = (page: number) => {
  currentPage.value = page
}

// 选择行处理
const handleSelectionChange = (selection: any[]) => {
  selectedRecords.value = selection
}

// 结算功能
const showSettlementDialog = ref(false)

const handleSettlement = () => {
  if (selectedRecords.value.length === 0) {
    ElMessage.warning('请选择要结算的记录')
    return
  }

  // 检查是否选择了已结算的记录
  const hasSettledRecords = selectedRecords.value.some(
    (record) => record.settlementStatus === '已结算'
  )

  if (hasSettledRecords) {
    ElMessage.warning('已选择的记录中包含已结算的记录，请重新选择')
    return
  }

  showSettlementDialog.value = true
}

// 结算成功处理
const handleSettlementSuccess = () => {
  ElMessage.success('结算成功')
  // 刷新数据或重新加载
  handleRefresh()
}

onMounted(() => {
  // 组件挂载后的初始化逻辑
})
</script>

<style scoped>
.sys.area {
  position: relative;
  padding: 16px;
  height: calc(100vh - 32px);
  display: flex;
  flex-direction: column;
  background: #f5f7fa;
}

/* 操作栏样式 */
.operation-bar {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 8px 16px;
  background: white;
  border-radius: 6px;
  box-shadow: 0 1px 3px rgba(0, 0, 0, 0.1);
  margin-bottom: 0;
  min-height: 60px;
}

.operation-left {
  display: flex;
  align-items: center;
}

.operation-right {
  display: flex;
  align-items: center;
  gap: 8px;
  flex-shrink: 0;
}

.action-btn {
  display: flex;
  align-items: center;
  gap: 4px;
}

/* 小型搜索按钮样式 */
.small-search {
  :deep(.search-trigger-btn) {
    padding: 6px 12px;
    font-size: 12px;
    height: 32px;
  }
}

/* 分割线样式 */
.custom-divider {
  margin: 8px 0;
  border-color: #e4e7ed;
}

/* 表格容器 - 占据剩余空间 */
.table-container {
  flex: 1;
  display: flex;
  flex-direction: column;
  min-height: 0;
  background: white;
  border-radius: 6px;
  box-shadow: 0 1px 3px rgba(0, 0, 0, 0.1);
  overflow: hidden;
}

/* 表格样式 */
:deep(.el-table) {
  flex: 1;
}

:deep(.el-table .el-table__row) {
  cursor: pointer;
}

/* 网状表格样式 */
:deep(.grid-table) {
  border: 1px solid #ebeef5;
}

:deep(.grid-table .el-table__header-wrapper) {
  border-bottom: 1px solid #ebeef5;
}

:deep(.grid-table .el-table__cell) {
  border-right: 1px solid #ebeef5;
}

:deep(.grid-table .el-table__row) {
  border-bottom: 1px solid #ebeef5;
}

/* 分页容器样式 */
.pagination-container {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 12px 16px;
  border-top: 1px solid #ebeef5;
  background: #fafafa;
  flex-wrap: wrap;
  gap: 16px;
}

.amount-summary {
  display: flex;
  gap: 20px;
  align-items: center;
}

.amount-item {
  display: flex;
  align-items: center;
  gap: 8px;
}

.amount-label {
  font-size: 14px;
  color: #606266;
  font-weight: 500;
  white-space: nowrap;
}

.amount-value {
  font-size: 14px;
  font-weight: 600;
  color: #303133;
  padding: 5px 12px;
  border: 1px solid #dcdfe6;
  border-radius: 4px;
  background-color: #ffffff;
  min-width: 120px;
  text-align: center;
  display: inline-block;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.04);
  transition: all 0.3s ease;
}

.amount-value:hover {
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.08);
  border-color: #c0c4cc;
}

/* 响应式设计 */
@media (max-width: 1200px) {
  .pagination-container {
    flex-direction: column;
    align-items: stretch;
    gap: 12px;
  }

  .pagination-left {
    justify-content: center;
  }

  .amount-summary {
    justify-content: center;
    flex-wrap: wrap;
  }
}

@media (max-width: 768px) {
  .sys.area {
    padding: 8px;
    height: calc(100vh - 16px);
  }

  .operation-bar {
    flex-direction: column;
    gap: 12px;
    align-items: stretch;
    padding: 12px;
  }

  .operation-left,
  .operation-right {
    justify-content: center;
  }

  .operation-left {
    border-bottom: 1px solid #e4e7ed;
    padding-bottom: 12px;
  }

  .pagination-container {
    padding: 8px 12px;
  }

  .amount-summary {
    gap: 12px;
  }

  .amount-item {
    flex-direction: column;
    gap: 4px;
    text-align: center;
  }

  .amount-value {
    min-width: 100px;
    padding: 4px 8px;
  }

  :deep(.el-pagination) {
    justify-content: center;
  }

  :deep(.el-pagination__sizes),
  :deep(.el-pagination__jump) {
    margin-top: 8px;
  }
}

/* 美化滚动条 */
:deep(.el-table__body-wrapper)::-webkit-scrollbar {
  width: 6px;
  height: 6px;
}

:deep(.el-table__body-wrapper)::-webkit-scrollbar-track {
  background: #f1f1f1;
  border-radius: 3px;
}

:deep(.el-table__body-wrapper)::-webkit-scrollbar-thumb {
  background: #c1c1c1;
  border-radius: 3px;
}

:deep(.el-table__body-wrapper)::-webkit-scrollbar-thumb:hover {
  background: #a8a8a8;
}
</style>
