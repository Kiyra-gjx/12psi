<template>
  <div class="sys area">
    <!-- 操作按钮区域 -->
    <div class="operation-bar">
      <div class="operation-left">
        <!-- 使用搜索组件 -->
        <GoodSearch
          :modelValue="searchFormData"
          :config="searchConfig"
          @update:modelValue="handleSearchFormUpdate"
          @search="handleGoodSearch"
          ref="goodSearchRef"
        />
      </div>

      <div class="operation-right">
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
        :data="currentPageData"
        style="width: 100%"
        row-key="id"
        :tree-props="{ children: 'children', hasChildren: 'hasChildren' }"
        v-loading="loading"
        :default-expand-all="false"
        border
        class="grid-table"
      >
        <!-- 单据类型列 -->
        <el-table-column prop="orderType" label="单据类型" width="120" align="center">
          <template #default="scope">
            <span :class="scope.row.isChild ? 'child-row' : 'parent-row'">
              {{ scope.row.orderType }}
            </span>
          </template>
        </el-table-column>

        <!-- 所属组织列 -->
        <el-table-column prop="orgName" label="所属组织" width="120" align="center">
          <template #default="scope">
            <span :class="scope.row.isChild ? 'child-row' : 'parent-row'">
              {{ scope.row.orgName }}
            </span>
          </template>
        </el-table-column>

        <!-- 往来单位列 -->
        <el-table-column prop="contactUnit" label="往来单位" width="150">
          <template #default="scope">
            <span :class="scope.row.isChild ? 'child-row' : 'parent-row'">
              {{ scope.row.contactUnit }}
            </span>
          </template>
        </el-table-column>

        <!-- 单据时间 -->
        <el-table-column prop="orderDate" label="单据时间" width="120" align="center">
          <template #default="scope">
            <span :class="scope.row.isChild ? 'child-row' : 'parent-row'">
              {{ scope.row.orderDate }}
            </span>
          </template>
        </el-table-column>

        <!-- 单据编号 -->
        <el-table-column prop="orderNo" label="单据编号" width="150">
          <template #default="scope">
            <span :class="scope.row.isChild ? 'child-row' : 'parent-row'">
              {{ scope.row.orderNo }}
            </span>
          </template>
        </el-table-column>

        <!-- 支出类别 -->
        <el-table-column prop="expenseType" label="支出类别" width="120" align="center">
          <template #default="scope">
            <span :class="scope.row.isChild ? 'child-row' : 'parent-row'">
              {{ scope.row.expenseType }}
            </span>
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
            <span :class="scope.row.isChild ? 'child-row' : 'parent-row'">
              {{ formatCurrency(scope.row.amount) }}
            </span>
          </template>
        </el-table-column>
      </el-table>

      <!-- 分页区域 -->
      <div class="pagination-container">
        <el-pagination
          v-model:current-page="currentPage"
          v-model:page-size="pageSize"
          :page-sizes="[10, 20, 30, 50]"
          :total="total"
          layout="total, sizes, prev, pager, next, jumper"
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange"
        />
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { reactive, ref, computed, onMounted } from 'vue'
import { ElMessage } from 'element-plus'
import { Download, Refresh } from '@element-plus/icons-vue'
import GoodSearch from '@/components/goodSearchConpoent/GoodSearchForm.vue'
import type { SearchFormData, GoodSearchConfig } from '@/components/goodSearchConpoent/type'

// 搜索组件引用
const goodSearchRef = ref()

// 原始数据 - 购销费用数据（树形结构）
const originalTableData = ref([
  {
    id: 1,
    orderType: '采购单',
    orgName: '总部',
    contactUnit: '上海供应商A',
    orderDate: '2023-10-01 ~ 2023-10-05',
    orderNo: '2个单据',
    expenseType: '采购支出',
    settlementStatus: '部分结算',
    amount: 42000,
    children: [
      {
        id: 11,
        orderType: '采购单',
        orgName: '总部',
        contactUnit: '上海供应商A',
        orderDate: '2023-10-01',
        orderNo: 'CG20231001001',
        expenseType: '采购支出',
        settlementStatus: '未结算',
        amount: 24000,
        isChild: true
      },
      {
        id: 12,
        orderType: '采购单',
        orgName: '总部',
        contactUnit: '上海供应商A',
        orderDate: '2023-10-05',
        orderNo: 'CG20231005001',
        expenseType: '采购支出',
        settlementStatus: '部分结算',
        amount: 18000,
        isChild: true
      }
    ]
  },
  {
    id: 2,
    orderType: '销售单',
    orgName: '分部',
    contactUnit: '北京客户B',
    orderDate: '2023-10-10 ~ 2023-10-15',
    orderNo: '2个单据',
    expenseType: '运输物流费',
    settlementStatus: '部分结算',
    amount: 60000,
    children: [
      {
        id: 21,
        orderType: '销售单',
        orgName: '分部',
        contactUnit: '北京客户B',
        orderDate: '2023-10-10',
        orderNo: 'XS20231010001',
        expenseType: '运输物流费',
        settlementStatus: '已结算',
        amount: 38000,
        isChild: true
      },
      {
        id: 22,
        orderType: '销售单',
        orgName: '分部',
        contactUnit: '北京客户B',
        orderDate: '2023-10-15',
        orderNo: 'XS20231015001',
        expenseType: '运输物流费',
        settlementStatus: '未结算',
        amount: 22000,
        isChild: true
      }
    ]
  },
  {
    id: 3,
    orderType: '采购退货单',
    orgName: '总部',
    contactUnit: '广州供应商C',
    orderDate: '2023-10-20',
    orderNo: 'CGTH20231020001',
    expenseType: '采购支出',
    settlementStatus: '部分结算',
    amount: -15000,
    children: [
      {
        id: 31,
        orderType: '采购退货单',
        orgName: '总部',
        contactUnit: '广州供应商C',
        orderDate: '2023-10-20',
        orderNo: 'CGTH20231020001',
        expenseType: '采购支出',
        settlementStatus: '部分结算',
        amount: -15000,
        isChild: true
      }
    ]
  },
  {
    id: 4,
    orderType: '调拨单',
    orgName: '分部',
    contactUnit: '内部调拨',
    orderDate: '2023-10-25',
    orderNo: 'DB20231025001',
    expenseType: '运输物流费',
    settlementStatus: '已结算',
    amount: 5000,
    children: [
      {
        id: 41,
        orderType: '调拨单',
        orgName: '分部',
        contactUnit: '内部调拨',
        orderDate: '2023-10-25',
        orderNo: 'DB20231025001',
        expenseType: '运输物流费',
        settlementStatus: '已结算',
        amount: 5000,
        isChild: true
      }
    ]
  }
])

// 当前显示的表格数据（树形结构）
const currentTableData = ref(JSON.parse(JSON.stringify(originalTableData.value)))

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

// 搜索配置 - 使用购销费用界面的搜索配置
const searchConfig = reactive<GoodSearchConfig>({
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
  inline: false,
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
})

// 处理搜索表单更新
const handleSearchFormUpdate = (newValue: SearchFormData) => {
  Object.assign(searchFormData, newValue)
}

// 处理搜索组件的搜索事件
const handleGoodSearch = (formData: SearchFormData) => {
  console.log('搜索条件:', formData)
  applySearchFilters(formData)
  ElMessage.success('搜索完成')
}

// 应用搜索过滤
const applySearchFilters = (formData: SearchFormData) => {
  let filteredData = JSON.parse(JSON.stringify(originalTableData.value))

  // 根据搜索条件过滤数据
  filteredData = filteredData.filter(
    (parent: { orderType: string | string[]; contactUnit: string | string[]; children: any[] }) => {
      // 过滤单据类型
      if (formData.orderType && parent.orderType !== formData.orderType) {
        return false
      }

      // 过滤供应商/客户
      if (formData.supplier && !parent.contactUnit.includes(formData.supplier as string)) {
        return false
      }

      if (formData.customer && !parent.contactUnit.includes(formData.customer as string)) {
        return false
      }

      // 过滤单据编号
      if (formData.number) {
        const hasMatchingChild = parent.children?.some((child: { orderNo: string | string[] }) =>
          child.orderNo.includes(formData.number as string)
        )
        if (!hasMatchingChild) return false
      }

      // 过滤支出类别
      if (formData.expenseType) {
        const filteredChildren = parent.children?.filter(
          (child: { expenseType: any }) => child.expenseType === formData.expenseType
        )
        if (!filteredChildren || filteredChildren.length === 0) return false
        parent.children = filteredChildren
      }

      // 过滤结算状态
      if (formData.settlementStatus) {
        const filteredChildren = parent.children?.filter(
          (child: { settlementStatus: any }) => child.settlementStatus === formData.settlementStatus
        )
        if (!filteredChildren || filteredChildren.length === 0) return false
        parent.children = filteredChildren
      }

      // 过滤单据日期范围
      if (formData.startTime || formData.endTime) {
        const filteredChildren = parent.children?.filter(
          (child: { orderDate: string | number | Date }) => {
            const orderDate = new Date(child.orderDate)
            const startDate = formData.startTime ? new Date(formData.startTime) : null
            const endDate = formData.endTime ? new Date(formData.endTime) : null

            if (startDate && orderDate < startDate) return false
            if (endDate && orderDate > endDate) return false
            return true
          }
        )
        if (!filteredChildren || filteredChildren.length === 0) return false
        parent.children = filteredChildren
      }

      return true
    }
  )

  // 更新当前显示的数据（树形结构）
  currentTableData.value = filteredData
  currentPage.value = 1 // 重置到第一页
}

// 刷新功能
const handleRefresh = () => {
  // 重置搜索表单
  if (goodSearchRef.value) {
    goodSearchRef.value.resetForm()
  }

  // 重置搜索条件
  Object.assign(searchFormData, {
    number: '',
    supplier: '',
    customer: '',
    startTime: '',
    endTime: '',
    expenseType: '',
    settlementStatus: '',
    orderType: ''
  })

  // 恢复显示所有原始数据
  currentTableData.value = JSON.parse(JSON.stringify(originalTableData.value))
  currentPage.value = 1 // 重置到第一页

  ElMessage.success('已刷新数据，显示全部记录')
}

// 导出功能实现
const handleExport = () => {
  const exportData = prepareExportData()
  ElMessage.success('正在导出数据...')
  setTimeout(() => {
    downloadCSV(exportData)
    ElMessage.success('导出成功，已开始下载文件')
  }, 1000)
}

// 准备导出数据
const prepareExportData = () => {
  const flatData: any[] = []
  currentTableData.value.forEach(
    (parent: {
      orderType: any
      orgName: any
      contactUnit: any
      orderDate: any
      orderNo: any
      expenseType: any
      settlementStatus: any
      amount: any
      children: any[]
    }) => {
      // 添加父级数据
      flatData.push({
        单据类型: parent.orderType,
        所属组织: parent.orgName,
        往来单位: parent.contactUnit,
        单据时间: parent.orderDate,
        单据编号: parent.orderNo,
        支出类别: parent.expenseType,
        结算状态: parent.settlementStatus,
        金额: formatCurrency(parent.amount)
      })

      // 添加子级数据
      if (parent.children && parent.children.length > 0) {
        parent.children.forEach(
          (child: {
            orderType: any
            orgName: any
            contactUnit: any
            orderDate: any
            orderNo: any
            expenseType: any
            settlementStatus: any
            amount: any
          }) => {
            flatData.push({
              单据类型: child.orderType,
              所属组织: child.orgName,
              往来单位: child.contactUnit,
              单据时间: child.orderDate,
              单据编号: child.orderNo,
              支出类别: child.expenseType,
              结算状态: child.settlementStatus,
              金额: formatCurrency(child.amount)
            })
          }
        )
      }
    }
  )
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
  link.setAttribute('download', `购销费用报表_${new Date().toISOString().split('T')[0]}.csv`)
  link.style.visibility = 'hidden'
  document.body.appendChild(link)
  link.click()
  document.body.removeChild(link)
}

// 分页相关
const currentPage = ref(1)
const pageSize = ref(10)
const loading = ref(false)

// 计算总数据条数（计算所有父级行）
const total = computed(() => {
  return currentTableData.value.length
})

// 当前页数据（树形结构）
const currentPageData = computed(() => {
  const start = (currentPage.value - 1) * pageSize.value
  const end = start + pageSize.value
  return currentTableData.value.slice(start, end)
})

// 分页处理
const handleSizeChange = (size: number) => {
  pageSize.value = size
  currentPage.value = 1
}

const handleCurrentChange = (page: number) => {
  currentPage.value = page
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

// 初始化
onMounted(() => {
  // 初始化数据
  currentTableData.value = JSON.parse(JSON.stringify(originalTableData.value))
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

.operation-bar {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 12px 0;
  background: white;
  border-radius: 6px;
  box-shadow: 0 1px 3px rgba(0, 0, 0, 0.1);
  margin-bottom: 0;
}

.operation-left,
.operation-right {
  display: flex;
  align-items: center;
  gap: 8px;
  padding: 0 16px;
}

.custom-divider {
  margin: 8px 0;
  border-color: #e4e7ed;
}

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

/* 分页容器样式 */
.pagination-container {
  display: flex;
  justify-content: center;
  align-items: center;
  padding: 12px 16px;
  border-top: 1px solid #ebeef5;
  background: #fafafa;
}

.parent-row {
  font-weight: 600;
  color: #303133;
}

.child-row {
  color: #606266;
}

/* 响应式设计 */
@media (max-width: 1200px) {
  .pagination-container {
    flex-direction: column;
    align-items: stretch;
    gap: 12px;
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

  :deep(.el-pagination) {
    justify-content: center;
  }

  :deep(.el-pagination__sizes),
  :deep(.el-pagination__jump) {
    margin-top: 8px;
  }
}
</style>
