<template>
  <div class="other-expense-report">
    <!-- 顶部操作栏 -->
    <div class="header-actions">
      <div class="left-actions">
        <!-- 直接使用搜索组件的按钮 -->
        <good-search-form
          v-model="searchFormData"
          :config="searchConfig"
          @search="handleSearchCompatible"
        />
      </div>

      <div class="right-actions">
        <!-- 使用按钮组件 -->
        <ActionButtons
          :show-add="false"
          :show-batch="true"
          :show-refresh="true"
          export-file-name="其它支出单报表"
          :table-columns="tableColumns"
          template-file-name="其它支出单导入模板"
          @batch="handleBatch"
          @refresh="handleRefresh"
          @export="handleExport"
          @import-data="handleImportData"
        />
      </div>
    </div>

    <!-- 表格区域 -->
    <div class="table-container">
      <report-button-table
        ref="reportTable"
        :columns="tableColumns"
        :data="tableData"
        :total="total"
        :current-page="currentPage"
        :page-size="pageSize"
        :loading="loading"
        :show-selection="true"
        :show-operations="true"
        :summary-data="summaryData"
        :row-logs="getRowLogs"
        @selection-change="handleSelectionChange"
        @page-change="handlePageChange"
        @view="handleView"
        @delete="handleDelete"
        @edit="handleEdit"
      >
        <!-- 自定义页脚右侧内容 -->
        <template #footer-right>
          <div class="custom-summary">
            <span class="summary-item">
              <span class="summary-label">总单据金额:</span>
              <span class="summary-value">{{ totalBillAmount }}</span>
            </span>
            <span class="summary-divider">|</span>
            <span class="summary-item">
              <span class="summary-label">总实际金额:</span>
              <span class="summary-value">{{ totalActualAmount }}</span>
            </span>
            <span class="summary-divider">|</span>
            <span class="summary-item">
              <span class="summary-label">总单据付款:</span>
              <span class="summary-value">{{ totalPaymentAmount }}</span>
            </span>
            <span class="summary-divider">|</span>
            <span class="summary-item">
              <span class="summary-label">总核销金额:</span>
              <span class="summary-value">{{ totalVerificationAmount }}</span>
            </span>
          </div>
        </template>

        <!-- 自定义审核状态显示 -->
        <template #auditStatus="{ row }">
          <el-tag :type="getAuditStatusType(row.auditStatus) as any">
            {{ getAuditStatusText(row.auditStatus) }}
          </el-tag>
        </template>

        <!-- 自定义核销状态显示 -->
        <template #verificationStatus="{ row }">
          <el-tag :type="getVerificationStatusType(row.verificationStatus) as any">
            {{ getVerificationStatusText(row.verificationStatus) }}
          </el-tag>
        </template>

        <!-- 自定义操作列 -->
        <template #operation="{ row }">
          <div class="op-row">
            <el-button size="small" class="op-btn op-gray" @click="openDetail(row)">
              详情
            </el-button>
            <el-button size="small" class="op-btn op-gray" @click="onDelete(row)"> 删除 </el-button>
            <el-dropdown trigger="click">
              <el-button size="small" class="op-btn op-gray op-more">
                <el-icon><ArrowDown /></el-icon>
              </el-button>
              <template #dropdown>
                <el-dropdown-menu class="info-dropdown">
                  <el-dropdown-item>单据号：{{ row.billNo }}</el-dropdown-item>
                  <el-dropdown-item>供应商：{{ row.supplier }}</el-dropdown-item>
                  <el-dropdown-item>金额：{{ formatNumber(row.billAmount) }}</el-dropdown-item>
                </el-dropdown-menu>
              </template>
            </el-dropdown>
          </div>
        </template>
      </report-button-table>
    </div>

    <!-- 其它支出单详情弹窗 -->
    <OtherExpenseDetailDialog
      v-model:visible="detailVisible"
      :record="currentRow"
      @save="handleDetailSave"
    />
  </div>
</template>

<script setup lang="ts">
import { ref, reactive, computed, onMounted } from 'vue'
import { ElMessage, ElMessageBox } from 'element-plus'
import { ArrowDown } from '@element-plus/icons-vue'

// 导入组件
import GoodSearchForm from '@/components/goodSearchConpoent/GoodSearchForm.vue'
import ReportButtonTable from '@/components/report/reportButtonTable.vue'
import ActionButtons from '@/components/operationbuttons/OperationButtons.vue'
import OtherExpenseDetailDialog from './OtherExpenseDetailDialog.vue'

// ========== 类型定义 ==========
// 表格行数据类型
interface TableRow {
  id: number
  organization: string
  supplier: string // 改为供应商
  billDate: string
  billNo: string
  billAmount: number
  actualAmount: number
  paymentAmount: number // 改为单据付款
  verificationAmount: number
  settlementAccount: string
  relatedPerson: string
  auditStatus: number
  verificationStatus: number
  checkStatus: string
  creator: string
  remark: string
}

// 搜索表单数据类型
interface SearchFormData {
  supplier?: string | null // 改为供应商
  number?: string
  startTime?: string
  endTime?: string
  people?: string | null
  user?: string | null
  examine?: string
  data?: string
  account?: string | null
  verificationStatus?: string
  auditStatus?: string
  [key: string]: any
}

// 表格列配置类型
interface TableColumn {
  prop: string
  label: string
  width?: string
  minWidth?: string
  sortable?: boolean
  align?: 'left' | 'center' | 'right'
  slot?: string
  showOverflowTooltip?: boolean
  fixed?: 'left' | 'right'
}

// API响应类型
interface ApiResponse {
  data: TableRow[]
  total: number
}

// 搜索参数类型
interface SearchParams {
  supplier?: string | null // 改为供应商
  billNo?: string
  startDate?: string
  endDate?: string
  relatedPerson?: string | null
  creator?: string | null
  auditStatus?: string
  remark?: string
  account?: string | null
  verificationStatus?: string
  page?: number
  pageSize?: number
}

// 自定义字段配置类型
interface CustomFieldConfig {
  key: string
  label: string
  type: 'select' | 'input' | 'date' | 'nodList' | 'treeSelect'
  options?: Array<{ label: string; value: string | number }>
  multiple?: boolean
  collapseTags?: boolean
  nodListConfig?: any
  treeData?: any[]
  checkStrictly?: boolean
  renderAfterExpand?: boolean
  clearable?: boolean
}

// 搜索配置类型
interface SearchConfig {
  inline: boolean
  showGoods: boolean
  showSupplier: boolean // 改为显示供应商
  showCustomer: boolean // 改为false
  showWarehouse: boolean
  showAccount: boolean
  showPeople: boolean
  showUser: boolean
  showNumber: boolean
  showBillDate: boolean
  showArrivalDate: boolean
  showExamine: boolean
  showState: boolean
  showRemark: boolean
  customFields: CustomFieldConfig[]
}

// ========== 搜索相关 ==========
const searchFormData = ref<SearchFormData>({
  supplier: null, // 改为供应商
  number: '',
  startTime: '',
  endTime: '',
  people: null,
  user: null,
  examine: '',
  data: '',
  account: null,
  verificationStatus: '',
  auditStatus: ''
})

// 搜索配置 - 显示供应商，隐藏客户
const searchConfig = reactive<SearchConfig>({
  inline: false,
  showGoods: false,
  showSupplier: true, // 显示供应商
  showCustomer: false, // 隐藏客户
  showWarehouse: false,
  showAccount: true,
  showPeople: true,
  showUser: true,
  showNumber: true,
  showBillDate: true,
  showArrivalDate: false,
  showExamine: false,
  showState: false,
  showRemark: true,
  customFields: [
    {
      key: 'auditStatus',
      label: '请选择审核状态',
      type: 'select',
      options: [
        { label: '未审核', value: '1' },
        { label: '已审核', value: '2' }
      ],
      clearable: true
    },
    {
      key: 'verificationStatus',
      label: '请选择核销状态',
      type: 'select',
      options: [
        { label: '未核销', value: '1' },
        { label: '部分核销', value: '2' },
        { label: '已核销', value: '3' }
      ],
      clearable: true
    }
  ]
})

// 搜索参数
const currentSearchParams = ref<SearchParams>({})

// 主要的搜索处理函数
const handleSearch = (formData: SearchFormData) => {
  const searchParams: SearchParams = {
    supplier: formData.supplier, // 改为供应商
    billNo: formData.number,
    startDate: formData.startTime,
    endDate: formData.endTime,
    relatedPerson: formData.people,
    creator: formData.user,
    auditStatus: formData.auditStatus,
    remark: formData.data,
    account: formData.account,
    verificationStatus: formData.verificationStatus
  }

  console.log('搜索表单数据:', formData)
  console.log('转换后的搜索参数:', searchParams)

  currentSearchParams.value = searchParams
  currentPage.value = 1
  fetchTableData(searchParams)
  ElMessage.success('搜索成功')
}

// 兼容的事件处理函数
const handleSearchCompatible = (value: any) => {
  handleSearch(value as SearchFormData)
}

// ========== 表格相关 ==========
const reportTable = ref()
const tableData = ref<TableRow[]>([])
const total = ref(0)
const currentPage = ref(1)
const pageSize = ref(20)
const loading = ref(false)
const selectedRows = ref<TableRow[]>([])

// 表格列配置 - 添加操作列，客户改为供应商
const tableColumns = ref<TableColumn[]>([
  { prop: 'organization', label: '所属组织', width: '120', align: 'center' },
  { prop: 'supplier', label: '供应商', width: '120', align: 'center' }, // 改为供应商
  { prop: 'billDate', label: '单据时间', width: '120', align: 'center', sortable: true },
  { prop: 'billNo', label: '单据编号', width: '150', align: 'center' },
  { prop: 'billAmount', label: '单据金额', width: '100', align: 'right', sortable: true },
  { prop: 'actualAmount', label: '实际金额', width: '100', align: 'right', sortable: true },
  { prop: 'paymentAmount', label: '单据付款', width: '100', align: 'right', sortable: true }, // 改为单据付款
  { prop: 'verificationAmount', label: '核销金额', width: '100', align: 'right', sortable: true },
  { prop: 'settlementAccount', label: '结算账户', width: '120', align: 'center' },
  { prop: 'relatedPerson', label: '关联人员', width: '100', align: 'center' },
  {
    prop: 'auditStatus',
    label: '审核状态',
    width: '100',
    align: 'center',
    slot: 'auditStatus'
  },
  {
    prop: 'verificationStatus',
    label: '核销状态',
    width: '100',
    align: 'center',
    slot: 'verificationStatus'
  },
  { prop: 'checkStatus', label: '核对状态', width: '100', align: 'center' },
  { prop: 'creator', label: '制单人', width: '100', align: 'center' },
  { prop: 'remark', label: '备注信息', width: '150', align: 'left', showOverflowTooltip: true },
  {
    prop: 'operation',
    label: '相关操作',
    width: '170',
    align: 'center',
    slot: 'operation',
    fixed: 'right' as const
  }
])

// 汇总数据
const summaryData = computed(() => {
  return [
    { label: '总单据金额', value: totalBillAmount.value },
    { label: '总实际金额', value: totalActualAmount.value },
    { label: '总单据付款', value: totalPaymentAmount.value }, // 改为单据付款
    { label: '总核销金额', value: totalVerificationAmount.value }
  ]
})

// 计算总单据金额
const totalBillAmount = computed(() => {
  return tableData.value
    .reduce((sum: number, item: TableRow) => sum + (item.billAmount || 0), 0)
    .toFixed(2)
})

// 计算总实际金额
const totalActualAmount = computed(() => {
  return tableData.value
    .reduce((sum: number, item: TableRow) => sum + (item.actualAmount || 0), 0)
    .toFixed(2)
})

// 计算总单据付款
const totalPaymentAmount = computed(() => {
  return tableData.value
    .reduce((sum: number, item: TableRow) => sum + (item.paymentAmount || 0), 0)
    .toFixed(2)
})

// 计算总核销金额
const totalVerificationAmount = computed(() => {
  return tableData.value
    .reduce((sum: number, item: TableRow) => sum + (item.verificationAmount || 0), 0)
    .toFixed(2)
})

// ========== 数据获取 ==========
// 生成所有模拟数据
const generateAllMockData = (): TableRow[] => {
  return Array.from({ length: 150 }, (_, index) => ({
    id: index + 1,
    organization: ['总部', '分部A', '分部B'][index % 3],
    supplier: `供应商${index + 1}`, // 改为供应商
    billDate: `2024-${String((index % 12) + 1).padStart(2, '0')}-${String((index % 28) + 1).padStart(2, '0')}`,
    billNo: `EX${String(index + 1001).padStart(4, '0')}`, // 单据编号前缀改为EX（支出）
    billAmount: Math.random() * 10000 + 1000,
    actualAmount: Math.random() * 10000 + 1000,
    paymentAmount: Math.random() * 10000 + 1000, // 改为付款金额
    verificationAmount: Math.random() * 5000 + 500,
    settlementAccount: ['银行账户', '现金账户', '支付宝'][index % 3],
    relatedPerson: ['张三', '李四', '王五'][index % 3],
    auditStatus: (index % 2) + 1,
    verificationStatus: (index % 3) + 1,
    checkStatus: index % 2 === 0 ? '已核对' : '未核对',
    creator: ['管理员', '财务员', '操作员'][index % 3],
    remark: `备注信息${index + 1}`
  }))
}

// 所有模拟数据
const allMockData = ref<TableRow[]>([])

// 已删除的数据ID集合
const deletedIds = ref<Set<number>>(new Set())

// 初始化模拟数据
const initMockData = () => {
  allMockData.value = generateAllMockData()
  deletedIds.value.clear()
}

// 根据搜索条件过滤数据
const filterDataBySearchParams = (data: TableRow[], params: SearchParams): TableRow[] => {
  let filteredData = [...data]

  // 过滤掉已删除的数据
  filteredData = filteredData.filter((item) => !deletedIds.value.has(item.id))

  // 根据搜索条件过滤数据
  if (params.billNo && params.billNo.trim() !== '') {
    filteredData = filteredData.filter((item) =>
      item.billNo.toLowerCase().includes(params.billNo!.toLowerCase())
    )
  }

  if (params.supplier && params.supplier.trim() !== '') {
    filteredData = filteredData.filter((item) =>
      item.supplier.toLowerCase().includes(params.supplier!.toLowerCase())
    )
  }

  if (params.startDate && params.endDate) {
    filteredData = filteredData.filter((item) => {
      const billDate = new Date(item.billDate)
      const startDate = new Date(params.startDate as string)
      const endDate = new Date(params.endDate as string)
      return billDate >= startDate && billDate <= endDate
    })
  }

  // 审核状态筛选
  if (params.auditStatus && params.auditStatus.trim() !== '') {
    filteredData = filteredData.filter((item) => item.auditStatus.toString() === params.auditStatus)
  }

  // 核销状态筛选
  if (params.verificationStatus && params.verificationStatus.trim() !== '') {
    filteredData = filteredData.filter(
      (item) => item.verificationStatus.toString() === params.verificationStatus
    )
  }

  if (params.creator && params.creator.trim() !== '') {
    filteredData = filteredData.filter((item) =>
      item.creator.toLowerCase().includes(params.creator!.toLowerCase())
    )
  }

  if (params.remark && params.remark.trim() !== '') {
    filteredData = filteredData.filter((item) =>
      item.remark.toLowerCase().includes(params.remark!.toLowerCase())
    )
  }

  if (params.relatedPerson && params.relatedPerson.trim() !== '') {
    filteredData = filteredData.filter((item) =>
      item.relatedPerson.toLowerCase().includes(params.relatedPerson!.toLowerCase())
    )
  }

  if (params.account && params.account.trim() !== '') {
    filteredData = filteredData.filter((item) =>
      item.settlementAccount.toLowerCase().includes(params.account!.toLowerCase())
    )
  }

  return filteredData
}

const fetchTableData = async (searchParams: SearchParams = {}) => {
  loading.value = true
  try {
    const response: ApiResponse = await mockFetchOtherExpenseData({
      page: currentPage.value,
      pageSize: pageSize.value,
      ...searchParams
    })

    tableData.value = response.data
    total.value = response.total
  } catch (error) {
    console.error('获取数据失败:', error)
    ElMessage.error('获取数据失败')
  } finally {
    loading.value = false
  }
}

// 模拟数据获取函数
const mockFetchOtherExpenseData = (params: SearchParams): Promise<ApiResponse> => {
  return new Promise((resolve) => {
    setTimeout(() => {
      const filteredData = filterDataBySearchParams(allMockData.value, params)
      const startIndex = ((params.page || 1) - 1) * (params.pageSize || 20)
      const endIndex = startIndex + (params.pageSize || 20)
      const pageData = filteredData.slice(startIndex, endIndex)

      resolve({
        data: pageData,
        total: filteredData.length
      })
    }, 500)
  })
}

// ========== 状态显示函数 ==========
// 审核状态
const getAuditStatusText = (status: number): string => {
  const statusMap: { [key: number]: string } = {
    1: '未审核',
    2: '已审核'
  }
  return statusMap[status] || '未知状态'
}

const getAuditStatusType = (status: number): string => {
  const typeMap: { [key: number]: string } = {
    1: 'warning',
    2: 'success'
  }
  return typeMap[status] || 'info'
}

// 核销状态
const getVerificationStatusText = (status: number): string => {
  const statusMap: { [key: number]: string } = {
    1: '未核销',
    2: '部分核销',
    3: '已核销'
  }
  return statusMap[status] || '未知状态'
}

const getVerificationStatusType = (status: number): string => {
  const typeMap: { [key: number]: string } = {
    1: 'danger',
    2: 'warning',
    3: 'success'
  }
  return typeMap[status] || 'info'
}

// ========== 详情弹框相关 ==========
const detailVisible = ref(false)
const currentRow = ref<TableRow | null>(null)

const openDetail = (row: TableRow) => {
  currentRow.value = row
  detailVisible.value = true
}

const handleDetailSave = (data: any) => {
  console.log('保存详情数据:', data)
  ElMessage.success('详情已保存')
  detailVisible.value = false
  // 刷新表格数据
  fetchTableData(currentSearchParams.value)
}

// ========== 操作日志功能 ==========
const getRowLogs = (row: TableRow) => {
  return [
    {
      time: new Date().toLocaleString(),
      user: '系统',
      action: `单据号: ${row.billNo}`
    },
    {
      time: new Date().toLocaleString(),
      user: '系统',
      action: `供应商: ${row.supplier}` // 改为供应商
    },
    {
      time: new Date().toLocaleString(),
      user: '系统',
      action: `金额: ${row.billAmount.toFixed(2)}`
    }
  ]
}

// ========== 事件处理 ==========
// 批量操作
const handleBatch = () => {
  if (selectedRows.value.length === 0) {
    ElMessage.warning('请先选择要操作的数据')
    return
  }

  ElMessageBox.confirm(
    `确定要对选中的 ${selectedRows.value.length} 条数据进行批量操作吗?`,
    '批量操作',
    {
      confirmButtonText: '确定',
      cancelButtonText: '取消',
      type: 'warning'
    }
  )
    .then(() => {
      ElMessage.success('批量操作成功')
    })
    .catch(() => {})
}

// 刷新
const handleRefresh = () => {
  searchFormData.value = {
    supplier: null, // 改为供应商
    number: '',
    startTime: '',
    endTime: '',
    people: null,
    user: null,
    examine: '',
    data: '',
    account: null,
    verificationStatus: '',
    auditStatus: ''
  }

  currentSearchParams.value = {}
  currentPage.value = 1
  fetchTableData()
  ElMessage.success('数据已刷新')
}

// 导出数据
const handleExport = () => {
  const exportData = tableData.value.map((item) => ({
    所属组织: item.organization,
    供应商: item.supplier, // 改为供应商
    单据时间: item.billDate,
    单据编号: item.billNo,
    单据金额: item.billAmount.toFixed(2),
    实际金额: item.actualAmount.toFixed(2),
    单据付款: item.paymentAmount.toFixed(2), // 改为单据付款
    核销金额: item.verificationAmount.toFixed(2),
    结算账户: item.settlementAccount,
    关联人员: item.relatedPerson,
    审核状态: getAuditStatusText(item.auditStatus),
    核销状态: getVerificationStatusText(item.verificationStatus),
    核对状态: item.checkStatus,
    制单人: item.creator,
    备注信息: item.remark
  }))

  ElMessage.success(`准备导出 ${exportData.length} 条数据`)
}

// 导入数据
const handleImportData = (importedData: any[]) => {
  ElMessage.success(`成功导入 ${importedData.length} 条数据`)
  handleRefresh()
}

// 选择变化
const handleSelectionChange = (selection: TableRow[]) => {
  selectedRows.value = selection
}

// 分页变化
const handlePageChange = (page: number, size: number) => {
  currentPage.value = page
  pageSize.value = size
  fetchTableData(currentSearchParams.value)
}

// 查看详情 - 兼容性函数
const handleView = (row: TableRow) => {
  openDetail(row)
}

// 删除
const handleDelete = (rows: TableRow[]) => {
  rows.forEach((row) => {
    deletedIds.value.add(row.id)
  })

  fetchTableData(currentSearchParams.value)
  ElMessage.success(`成功删除 ${rows.length} 条数据`)
}

// 编辑
const handleEdit = (row: TableRow) => {
  console.log('编辑:', row)
  ElMessage.info(`编辑单据: ${row.billNo}`)
}

// 工具函数：数字格式化
const formatNumber = (n: number | undefined | null) => {
  const num = Number(n ?? 0)
  return Number.isFinite(num) ? num.toLocaleString() : '0'
}

// 单独删除函数
const onDelete = (row: TableRow) => {
  ElMessageBox.confirm(`确定删除单据【${row.billNo}】吗？`, '提示', {
    type: 'warning',
    confirmButtonText: '删除',
    cancelButtonText: '取消'
  })
    .then(() => {
      handleDelete([row])
    })
    .catch(() => {})
}

// ========== 生命周期 ==========
onMounted(() => {
  initMockData()
  fetchTableData()
})
</script>

<style scoped lang="scss">
.other-expense-report {
  padding: 16px;
  background: #f5f7fa;
  min-height: 100vh;
}

.header-actions {
  display: flex;
  justify-content: space-between;
  align-items: flex-start;
  margin-bottom: 16px;
  padding: 16px;
  background: #fff;
  border-radius: 4px;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);

  .left-actions {
    :deep(.el-popover__reference) {
      .el-button {
        background: #409eff;
        border-color: #409eff;
        color: #fff;

        &:hover {
          background: #66b1ff;
          border-color: #66b1ff;
        }
      }
    }
  }

  .right-actions {
    display: flex;
    gap: 8px;
  }
}

.table-container {
  background: #fff;
  border-radius: 4px;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  overflow: hidden;
}

.custom-summary {
  display: flex;
  align-items: center;
  font-size: 12px;
  color: #606266;

  .summary-item {
    display: flex;
    align-items: center;

    .summary-label {
      margin-right: 4px;
      color: #606266;
    }

    .summary-value {
      color: #303133;
      font-weight: 500;
    }
  }

  .summary-divider {
    margin: 0 8px;
    color: #dcdfe6;
  }
}

/* 操作列按钮 */
.op-row {
  display: inline-flex;
  align-items: center;
  justify-content: center;
}
.op-btn {
  height: 28px;
  line-height: 26px;
  background: #fff;
  color: #606266;
  border: 1px solid #dcdfe6;
  border-radius: 0;
  padding: 0 10px;
  transition: all 0.15s ease;
}
.op-row > * + * {
  margin-left: -1px;
}
.op-row :deep(.el-dropdown .el-button) {
  border-radius: 0 !important;
}
.op-row .op-btn:hover {
  border-color: #409eff;
  color: #409eff;
}

/* 响应式设计 */
@media (max-width: 768px) {
  .header-actions {
    flex-direction: column;
    gap: 12px;

    .left-actions,
    .right-actions {
      width: 100%;
      justify-content: center;
    }
  }

  .custom-summary {
    flex-wrap: wrap;
    justify-content: center;

    .summary-item {
      margin: 0 4px;
    }
  }
}
</style>
