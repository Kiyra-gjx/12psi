<template>
  <div class="invoice-container">
    <!-- 操作按钮区域 -->
    <div class="operation-bar">
      <div class="operation-left">
        <GoodSearch
          v-model="searchFormData"
          :config="searchConfig"
          @search="handleSearch"
          class="small-search"
        />
      </div>

      <div class="operation-right">
        <el-button type="primary" @click="handleInvoice" class="action-btn">
          <el-icon><Document /></el-icon>
          开票
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

    <!-- 表格区域 - 占据主要空间 -->
    <div class="table-main-container">
      <el-table
        :data="pagedTableData"
        style="width: 100%; height: 100%"
        v-loading="loading"
        border
        class="grid-table"
        @selection-change="handleSelectionChange"
      >
        <!-- 选择框列 -->
        <el-table-column type="selection" width="55" align="center" />

        <el-table-column prop="orderType" label="单据类型" width="120" align="center">
          <template #default="scope">
            {{ scope.row.orderType }}
          </template>
        </el-table-column>

        <el-table-column prop="orgName" label="所属组织" width="120" align="center">
          <template #default="scope">
            {{ scope.row.orgName }}
          </template>
        </el-table-column>

        <el-table-column prop="contactUnit" label="往来单位" width="150">
          <template #default="scope">
            {{ scope.row.contactUnit }}
          </template>
        </el-table-column>

        <el-table-column prop="orderDate" label="单据时间" width="120" align="center">
          <template #default="scope">
            {{ scope.row.orderDate }}
          </template>
        </el-table-column>

        <el-table-column prop="orderNo" label="单据编号" width="150">
          <template #default="scope">
            {{ scope.row.orderNo }}
          </template>
        </el-table-column>

        <el-table-column prop="invoiceStatus" label="发票状态" width="100" align="center">
          <template #default="scope">
            <el-tag :type="getInvoiceStatusType(scope.row.invoiceStatus)" size="small">
              {{ scope.row.invoiceStatus }}
            </el-tag>
          </template>
        </el-table-column>

        <el-table-column prop="amount" label="单据金额" width="120" align="right">
          <template #default="scope">
            {{ formatCurrency(scope.row.amount) }}
          </template>
        </el-table-column>

        <el-table-column prop="invoicedAmount" label="已开票金额" width="120" align="right">
          <template #default="scope">
            {{ formatCurrency(scope.row.invoicedAmount) }}
          </template>
        </el-table-column>

        <el-table-column prop="uninvoicedAmount" label="未开票金额" width="120" align="right">
          <template #default="scope">
            <span :class="getUninvoicedAmountClass(scope.row)">
              {{ formatCurrency(scope.row.uninvoicedAmount) }}
            </span>
          </template>
        </el-table-column>

        <el-table-column prop="invoiceAmount" label="开票金额" width="120" align="right">
          <template #default="scope">
            {{ formatCurrency(scope.row.invoiceAmount) }}
          </template>
        </el-table-column>
      </el-table>
    </div>

    <!-- 分页区域和金额统计 - 固定在底部 -->
    <div class="footer-container">
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
            <span class="amount-label">已开票总金额：</span>
            <span class="amount-value invoiced-amount">{{
              formatCurrency(totalInvoicedAmount)
            }}</span>
          </div>
          <div class="amount-item">
            <span class="amount-label">未开票总金额：</span>
            <span class="amount-value uninvoiced-amount">{{
              formatCurrency(totalUninvoicedAmount)
            }}</span>
          </div>
        </div>
      </div>
    </div>

    <!-- 发票弹框 -->
    <InvoiceDialog
      v-model:visible="showInvoiceDialog"
      :selected-records="selectedRecords"
      @invoice-success="handleInvoiceSuccess"
    />
  </div>
</template>

<script setup lang="ts">
import { reactive, ref, computed, onMounted } from 'vue'
import { ElMessage } from 'element-plus'
import { Download, Refresh, Document } from '@element-plus/icons-vue'
import GoodSearch from '@/components/goodSearchConpoent/GoodSearchForm.vue'
import InvoiceDialog from './InvoiceDialog.vue'
import type { SearchFormData, GoodSearchConfig } from '@/components/goodSearchConpoent/type'

// 搜索配置
const searchConfig: GoodSearchConfig = {
  inline: false,
  showGoods: false,
  showNumber: true,
  showSupplier: true,
  showCustomer: true,
  showPeople: false,
  showBillDate: true,
  showArrivalDate: false,
  showUser: false,
  showExamine: false,
  showState: false,
  showRemark: false,
  showWarehouse: false,
  customFields: [
    {
      key: 'invoiceStatus',
      type: 'select',
      label: '发票状态',
      options: [
        { label: '未开票', value: '未开票' },
        { label: '部分开票', value: '部分开票' },
        { label: '已开票', value: '已开票' }
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
        { label: '销售退货单', value: '销售退货单' }
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
  invoiceStatus: '',
  orderType: ''
})

// 表格数据
const originalTableData = ref([
  {
    id: 1,
    orderType: '采购单',
    orgName: '总部',
    contactUnit: '上海供应商A',
    orderDate: '2023-10-01',
    orderNo: 'CG20231001001',
    invoiceStatus: '未开票',
    amount: 24000,
    invoicedAmount: 0,
    uninvoicedAmount: 24000,
    invoiceAmount: 24000
  },
  {
    id: 2,
    orderType: '采购退货单',
    orgName: '总部',
    contactUnit: '上海供应商A',
    orderDate: '2023-10-05',
    orderNo: 'CGTH20231005001',
    invoiceStatus: '部分开票',
    amount: -2400,
    invoicedAmount: -1200,
    uninvoicedAmount: -1200,
    invoiceAmount: -2400
  },
  {
    id: 3,
    orderType: '销售单',
    orgName: '分部',
    contactUnit: '北京客户B',
    orderDate: '2023-10-10',
    orderNo: 'XS20231010001',
    invoiceStatus: '已开票',
    amount: 38000,
    invoicedAmount: 38000,
    uninvoicedAmount: 0,
    invoiceAmount: 38000
  },
  {
    id: 4,
    orderType: '销售退货单',
    orgName: '分部',
    contactUnit: '北京客户B',
    orderDate: '2023-10-15',
    orderNo: 'XSTH20231015001',
    invoiceStatus: '未开票',
    amount: -3800,
    invoicedAmount: 0,
    uninvoicedAmount: -3800,
    invoiceAmount: -3800
  },
  {
    id: 5,
    orderType: '采购单',
    orgName: '总部',
    contactUnit: '广州供应商C',
    orderDate: '2023-10-20',
    orderNo: 'CG20231020001',
    invoiceStatus: '部分开票',
    amount: 15600,
    invoicedAmount: 8000,
    uninvoicedAmount: 7600,
    invoiceAmount: 15600
  },
  {
    id: 6,
    orderType: '销售单',
    orgName: '分部',
    contactUnit: '深圳客户D',
    orderDate: '2023-10-25',
    orderNo: 'XS20231025001',
    invoiceStatus: '已开票',
    amount: 28500,
    invoicedAmount: 28500,
    uninvoicedAmount: 0,
    invoiceAmount: 28500
  },
  {
    id: 7,
    orderType: '采购单',
    orgName: '总部',
    contactUnit: '杭州供应商E',
    orderDate: '2023-10-28',
    orderNo: 'CG20231028001',
    invoiceStatus: '未开票',
    amount: 18900,
    invoicedAmount: 0,
    uninvoicedAmount: 18900,
    invoiceAmount: 18900
  }
])

// 响应式数据
const currentPage = ref(1)
const pageSize = ref(10)
const loading = ref(false)
const selectedRecords = ref<any[]>([])
const showInvoiceDialog = ref(false)

// 计算属性
const filteredTableData = computed(() => {
  let result = [...originalTableData.value]

  if (searchFormData.value.supplier) {
    result = result.filter((item) => item.contactUnit.includes(searchFormData.value.supplier as string))
  }

  if (searchFormData.value.customer) {
    result = result.filter((item) => item.contactUnit.includes(searchFormData.value.customer as string))
  }

  if (searchFormData.value.number) {
    result = result.filter((item) => item.orderNo.includes(searchFormData.value.number as string))
  }

  if (searchFormData.value.orderType) {
    result = result.filter((item) => item.orderType === searchFormData.value.orderType)
  }

  if (searchFormData.value.invoiceStatus) {
    result = result.filter((item) => item.invoiceStatus === searchFormData.value.invoiceStatus)
  }

  if (searchFormData.value.startTime) {
    result = result.filter((item) => item.orderDate >= searchFormData.value.startTime!)
  }

  if (searchFormData.value.endTime) {
    result = result.filter((item) => item.orderDate <= searchFormData.value.endTime!)
  }

  return result
})

const pagedTableData = computed(() => {
  const start = (currentPage.value - 1) * pageSize.value
  const end = start + pageSize.value
  return filteredTableData.value.slice(start, end)
})

const totalAmount = computed(() => {
  return filteredTableData.value.reduce((sum, item) => sum + item.amount, 0)
})

const totalInvoicedAmount = computed(() => {
  return filteredTableData.value.reduce((sum, item) => sum + item.invoicedAmount, 0)
})

const totalUninvoicedAmount = computed(() => {
  return filteredTableData.value.reduce((sum, item) => sum + item.uninvoicedAmount, 0)
})

// 方法
const handleSearch = (formData: SearchFormData) => {
  Object.assign(searchFormData, formData)
  currentPage.value = 1
  ElMessage.success('搜索完成')
}

const handleRefresh = () => {
  Object.keys(searchFormData.value).forEach((key) => {
    (searchFormData.value as any)[key] = ''
  })
  currentPage.value = 1
  ElMessage.success('数据已刷新')
}

const handleExport = () => {
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
      发票状态: item.invoiceStatus,
      单据金额: item.amount,
      已开票金额: item.invoicedAmount,
      未开票金额: item.uninvoicedAmount,
      开票金额: item.invoiceAmount
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
  link.setAttribute('download', `购销发票表_${new Date().toISOString().split('T')[0]}.csv`)
  link.style.visibility = 'hidden'

  document.body.appendChild(link)
  link.click()
  document.body.removeChild(link)
}

const formatCurrency = (value: number) => {
  return (
    '¥' +
    value.toLocaleString('zh-CN', {
      minimumFractionDigits: 2,
      maximumFractionDigits: 2
    })
  )
}

const getInvoiceStatusType = (status: string) => {
  switch (status) {
    case '未开票':
      return 'danger'
    case '部分开票':
      return 'warning'
    case '已开票':
      return 'success'
    default:
      return 'info'
  }
}

const getUninvoicedAmountClass = (row: any) => {
  return row.uninvoicedAmount > 0 ? 'negative-amount' : 'positive-amount'
}

const handleSizeChange = (size: number) => {
  pageSize.value = size
  currentPage.value = 1
}

const handleCurrentChange = (page: number) => {
  currentPage.value = page
}

const handleSelectionChange = (selection: any[]) => {
  selectedRecords.value = selection
}

const handleInvoice = () => {
  if (selectedRecords.value.length === 0) {
    ElMessage.warning('请选择要开票的记录')
    return
  }

  const hasInvoicedRecords = selectedRecords.value.some(
    (record) => record.invoiceStatus === '已开票'
  )

  if (hasInvoicedRecords) {
    ElMessage.warning('已选择的记录中包含已开票的记录，请重新选择')
    return
  }

  showInvoiceDialog.value = true
}

const handleInvoiceSuccess = () => {
  ElMessage.success('开票成功')
  handleRefresh()
}

onMounted(() => {
  // 初始化逻辑
})
</script>

<style scoped>
.invoice-container {
  position: relative;
  padding: 16px;
  height: calc(100vh - 32px);
  display: flex;
  flex-direction: column;
  background: #f5f7fa;
  overflow: hidden;
}

.operation-bar {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 12px 16px;
  background: white;
  border-radius: 6px;
  box-shadow: 0 1px 3px rgba(0, 0, 0, 0.1);
  margin-bottom: 12px;
  min-height: 60px;
  flex-shrink: 0;
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

/* 表格主容器 - 占据剩余空间 */
.table-main-container {
  flex: 1;
  display: flex;
  flex-direction: column;
  background: white;
  border-radius: 6px;
  box-shadow: 0 1px 3px rgba(0, 0, 0, 0.1);
  overflow: hidden;
  min-height: 0;
}

/* 表格样式调整 */
:deep(.grid-table) {
  flex: 1;
  height: 100% !important;
}

:deep(.grid-table .el-table__body-wrapper) {
  height: calc(100% - 40px) !important;
}

/* 底部容器 */
.footer-container {
  flex-shrink: 0;
  margin-top: 12px;
}

.pagination-container {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 12px 16px;
  background: white;
  border-radius: 6px;
  box-shadow: 0 1px 3px rgba(0, 0, 0, 0.1);
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
}

.negative-amount {
  color: #f56c6c;
}

.positive-amount {
  color: #67c23a;
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
  .invoice-container {
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
  width: 8px;
  height: 8px;
}

:deep(.el-table__body-wrapper)::-webkit-scrollbar-track {
  background: #f1f1f1;
  border-radius: 4px;
}

:deep(.el-table__body-wrapper)::-webkit-scrollbar-thumb {
  background: #c1c1c1;
  border-radius: 4px;
}

:deep(.el-table__body-wrapper)::-webkit-scrollbar-thumb:hover {
  background: #a8a8a8;
}
</style>
