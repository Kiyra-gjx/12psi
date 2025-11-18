<template>
  <div class="invoice-report-container">
    <!-- 顶部操作栏 -->
    <div class="header-actions">
      <div class="left-actions">
        <GoodSearch v-model="searchFormData" :config="searchConfig" @search="handleSearch" />
      </div>

      <div class="right-actions">
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

    <!-- 表格主区域 -->
    <div class="table-main-container">
      <el-table
        :data="pagedTableData"
        style="width: 100%; height: 100%"
        v-loading="loading"
        border
        @selection-change="handleSelectionChange"
      >
        <!-- 选择框列 -->
        <el-table-column type="selection" width="55" align="center" />

        <el-table-column prop="orderType" label="单据类型" width="120" align="center" />
        <el-table-column prop="organization" label="所属组织" width="120" align="center" />
        <el-table-column prop="contactUnit" label="往来单位" width="120" align="center" />
        <el-table-column prop="billDate" label="单据时间" width="120" align="center" />
        <el-table-column prop="billNo" label="单据编号" width="150" align="center" />
        <el-table-column prop="billAmount" label="单据金额" width="100" align="right" />
        <el-table-column prop="invoiceDate" label="开票时间" width="120" align="center" />
        <el-table-column prop="invoiceNumber" label="发票号码" width="150" align="center" />
        <el-table-column prop="invoiceTitle" label="发票抬头" width="150" align="center" />
        <el-table-column prop="invoiceAmount" label="发票金额" width="100" align="right" />
        <el-table-column prop="invoiceAttachment" label="开票附件" width="100" align="center" />
        <el-table-column
          prop="remark"
          label="备注信息"
          width="150"
          align="left"
          show-overflow-tooltip
        />

        <!-- 操作列 -->
        <el-table-column label="操作" width="150" fixed="right" align="center">
          <template #default="scope">
            <el-button type="primary" link @click="handleView(scope.row)">详情</el-button>
            <el-button type="danger" link @click="handleDelete([scope.row])">删除</el-button>
          </template>
        </el-table-column>
      </el-table>
    </div>

    <!-- 分页和统计 -->
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
            <span class="amount-value">{{ formatCurrency(totalBillAmount) }}</span>
          </div>
          <div class="amount-item">
            <span class="amount-label">发票总金额：</span>
            <span class="amount-value">{{ formatCurrency(totalInvoiceAmount) }}</span>
          </div>
        </div>
      </div>
    </div>

    <!-- 发票弹框 -->
    <InvoiceDialog
      v-model:visible="showInvoiceDialog"
      :selected-records="selectedRows"
      @invoice-success="handleInvoiceSuccess"
    />
  </div>
</template>

<script setup lang="ts">
import { reactive, ref, computed, onMounted } from 'vue'
import { ElMessage } from 'element-plus'
import { Download, Refresh } from '@element-plus/icons-vue'
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
  showBillDate: false,
  showArrivalDate: false,
  showUser: false,
  showExamine: false,
  showState: false,
  showRemark: false,
  showWarehouse: false,
  customFields: [
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
    },
    {
      key: 'invoiceStartDate',
      label: '开具开始日期',
      type: 'date',
      clearable: true
    },
    {
      key: 'invoiceEndDate',
      label: '开具结束日期',
      type: 'date',
      clearable: true
    },
    {
      key: 'invoiceNumber',
      label: '发票号码',
      type: 'input',
      clearable: true
    },
    {
      key: 'invoiceTitle',
      label: '发票抬头',
      type: 'input',
      clearable: true
    }
  ]
}

// 搜索表单数据
const searchFormData = ref<SearchFormData>({
  number: '',
  supplier: '',
  customer: '',
  orderType: '',
  invoiceStartDate: '',
  invoiceEndDate: '',
  invoiceNumber: '',
  invoiceTitle: ''
})

// 表格数据
const originalTableData = ref([
  {
    id: 1,
    orderType: '采购单',
    organization: '总部',
    contactUnit: '上海供应商A',
    billDate: '2023-10-01',
    billNo: 'CG20231001001',
    billAmount: 24000,
    invoiceDate: '2023-10-02',
    invoiceNumber: 'INV20231002001',
    invoiceTitle: '上海供应商A',
    invoiceAmount: 24000,
    invoiceAttachment: '已上传',
    remark: '采购发票'
  },
  {
    id: 2,
    orderType: '采购退货单',
    organization: '总部',
    contactUnit: '上海供应商A',
    billDate: '2023-10-05',
    billNo: 'CGTH20231005001',
    billAmount: -2400,
    invoiceDate: '2023-10-06',
    invoiceNumber: 'INV20231006001',
    invoiceTitle: '上海供应商A',
    invoiceAmount: -2400,
    invoiceAttachment: '已上传',
    remark: '采购退货发票'
  },
  {
    id: 3,
    orderType: '销售单',
    organization: '分部',
    contactUnit: '北京客户B',
    billDate: '2023-10-10',
    billNo: 'XS20231010001',
    billAmount: 38000,
    invoiceDate: '2023-10-11',
    invoiceNumber: 'INV20231011001',
    invoiceTitle: '北京客户B',
    invoiceAmount: 38000,
    invoiceAttachment: '已上传',
    remark: '销售发票'
  },
  {
    id: 4,
    orderType: '销售退货单',
    organization: '分部',
    contactUnit: '北京客户B',
    billDate: '2023-10-15',
    billNo: 'XSTH20231015001',
    billAmount: -3800,
    invoiceDate: '',
    invoiceNumber: '',
    invoiceTitle: '',
    invoiceAmount: 0,
    invoiceAttachment: '',
    remark: '销售退货单未开票'
  },
  {
    id: 5,
    orderType: '采购单',
    organization: '总部',
    contactUnit: '广州供应商C',
    billDate: '2023-10-20',
    billNo: 'CG20231020001',
    billAmount: 15600,
    invoiceDate: '2023-10-21',
    invoiceNumber: 'INV20231021001',
    invoiceTitle: '广州供应商C',
    invoiceAmount: 15600,
    invoiceAttachment: '已上传',
    remark: '采购发票'
  },
  {
    id: 6,
    orderType: '销售单',
    organization: '分部',
    contactUnit: '深圳客户D',
    billDate: '2023-10-25',
    billNo: 'XS20231025001',
    billAmount: 28500,
    invoiceDate: '2023-10-26',
    invoiceNumber: 'INV20231026001',
    invoiceTitle: '深圳客户D',
    invoiceAmount: 28500,
    invoiceAttachment: '已上传',
    remark: '销售发票'
  },
  {
    id: 7,
    orderType: '采购单',
    organization: '总部',
    contactUnit: '杭州供应商E',
    billDate: '2023-10-28',
    billNo: 'CG20231028001',
    billAmount: 18900,
    invoiceDate: '',
    invoiceNumber: '',
    invoiceTitle: '',
    invoiceAmount: 0,
    invoiceAttachment: '',
    remark: '采购单未开票'
  },
  {
    id: 8,
    orderType: '销售单',
    organization: '分部',
    contactUnit: '成都客户F',
    billDate: '2023-11-01',
    billNo: 'XS20231101001',
    billAmount: 32500,
    invoiceDate: '2023-11-02',
    invoiceNumber: 'INV20231102001',
    invoiceTitle: '成都客户F',
    invoiceAmount: 32500,
    invoiceAttachment: '已上传',
    remark: '销售发票'
  }
])

// 响应式数据
const currentPage = ref(1)
const pageSize = ref(10)
const loading = ref(false)
const selectedRows = ref<any[]>([])
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
    result = result.filter((item) => item.billNo.includes(searchFormData.value.number as string))
  }

  if (searchFormData.value.orderType) {
    result = result.filter((item) => item.orderType === searchFormData.value.orderType)
  }

  if (searchFormData.value.invoiceNumber) {
    result = result.filter((item) =>
      item.invoiceNumber.includes(searchFormData.value.invoiceNumber as string)
    )
  }

  if (searchFormData.value.invoiceTitle) {
    result = result.filter((item) =>
      item.invoiceTitle.includes(searchFormData.value.invoiceTitle as string)
    )
  }

  if (searchFormData.value.invoiceStartDate && searchFormData.value.invoiceEndDate) {
    result = result.filter((item) => {
      if (!item.invoiceDate) return false
      return (
        item.invoiceDate >= searchFormData.value.invoiceStartDate! &&
        item.invoiceDate <= searchFormData.value.invoiceEndDate!
      )
    })
  }

  return result
})

const pagedTableData = computed(() => {
  const start = (currentPage.value - 1) * pageSize.value
  const end = start + pageSize.value
  return filteredTableData.value.slice(start, end)
})

const totalBillAmount = computed(() => {
  return filteredTableData.value.reduce((sum, item) => sum + item.billAmount, 0)
})

const totalInvoiceAmount = computed(() => {
  return filteredTableData.value.reduce((sum, item) => sum + item.invoiceAmount, 0)
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

  filteredTableData.value.forEach((item) => {
    flatData.push({
      单据类型: item.orderType,
      所属组织: item.organization,
      往来单位: item.contactUnit,
      单据时间: item.billDate,
      单据编号: item.billNo,
      单据金额: item.billAmount,
      开票时间: item.invoiceDate,
      发票号码: item.invoiceNumber,
      发票抬头: item.invoiceTitle,
      发票金额: item.invoiceAmount,
      开票附件: item.invoiceAttachment,
      备注信息: item.remark
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
  link.setAttribute('download', `购销发票报表_${new Date().toISOString().split('T')[0]}.csv`)
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

const handleSizeChange = (size: number) => {
  pageSize.value = size
  currentPage.value = 1
}

const handleCurrentChange = (page: number) => {
  currentPage.value = page
}

const handleSelectionChange = (selection: any[]) => {
  selectedRows.value = selection
}

const handleView = (row: any) => {
  selectedRows.value = [row]
  showInvoiceDialog.value = true
}

const handleDelete = (rows: any[]) => {
  // 实际项目中这里应该调用API删除数据
  rows.forEach((row) => {
    const index = originalTableData.value.findIndex((item) => item.id === row.id)
    if (index !== -1) {
      originalTableData.value.splice(index, 1)
    }
  })
  ElMessage.success(`成功删除 ${rows.length} 条数据`)
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
.invoice-report-container {
  position: relative;
  padding: 16px;
  height: calc(100vh - 32px);
  display: flex;
  flex-direction: column;
  background: #f5f7fa;
  overflow: hidden;
}

.header-actions {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 12px;
  padding: 12px 16px;
  background: #fff;
  border-radius: 6px;
  box-shadow: 0 1px 3px rgba(0, 0, 0, 0.1);
  flex-shrink: 0;
}

.left-actions {
  display: flex;
  align-items: center;
}

.right-actions {
  display: flex;
  align-items: center;
  gap: 8px;
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
:deep(.el-table) {
  flex: 1;
  height: 100% !important;
}

:deep(.el-table__body-wrapper) {
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
  .invoice-report-container {
    padding: 8px;
    height: calc(100vh - 16px);
  }

  .header-actions {
    flex-direction: column;
    gap: 12px;
    align-items: stretch;
    padding: 12px;
  }

  .left-actions,
  .right-actions {
    justify-content: center;
  }

  .left-actions {
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
