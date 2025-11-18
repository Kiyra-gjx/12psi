/**
 * 销售单相关类型定义
 */

import type { PageQuery, PageResult } from '@/apis/type'

/**
 * 销售单详情数据对象
 */
export interface SaleDetailItem {
  /** 主键ID */
  id?: string
  /** 所属销售单ID（外键） */
  pid: string
  /** 所属商品 */
  goods?: string
  /** 商品名称 */
  goodsName?: string
  /** 商品编号 */
  goodsCode?: string
  /** 规格型号 */
  spec?: string
  /** 辅助属性 */
  attr?: string
  /** 单位 */
  unit?: string
  /** 仓库 */
  warehouse?: string
  /** 单价 */
  price?: number
  /** 数量 */
  nums?: number
  /** 折扣率 */
  discount?: number
  /** 折扣额 */
  dsc?: number
  /** 金额 */
  total?: number
  /** 税率 */
  tax?: number
  /** 税额 */
  tat?: number
  /** 价税合计 */
  tpt?: number
  /** 批次号 */
  batch?: string
  /** 生产日期 */
  mfd?: string
  /** 序列号（多个用逗号分隔） */
  serial?: string
  /** 退货数量 */
  retreat?: number
  /** 关联详情\|SOR */
  source?: string
  /** 备注信息 */
  data?: string
}

/**
 * 销售单数据对象
 */
export interface SaleDTO {
  /** 主键ID */
  id?: string
  /** 所属组织 */
  frame?: string
  /** 客户 */
  customer?: string
  /** 客户名称 */
  customerName?: string
  /** 单据时间 */
  time?: string
  /** 单据编号 */
  number?: string
  /** 单据金额 */
  total?: number
  /** 实际金额 */
  actual?: number
  /** 实收金额 */
  money?: number
  /** 单据费用 */
  cost?: number
  /** 结算账户 */
  account?: string
  /** 关联人员 */
  people?: string
  /** 物流信息 */
  logistics?: string
  /** 单据附件 */
  file?: string
  /** 备注信息 */
  data?: string
  /** 扩展信息 */
  more?: string
  /** 制单人 */
  user?: string
  /** 关联单据\|SOR */
  source?: string

  /** 审核状态[0:未审核|1:已审核] */
  examine?: boolean
  /** 核对状态[0:未核对|1:已核对] */
  check?: boolean
  /** 核销状态[0:未核销|1:部分核销|2:已核销] */
  nucleus?: number
  /** 费用状态[0:未结算|1:部分结算|2:已结算|3:无需结算] */
  cse?: number
  /** 发票状态[0:未开票|1:部分开票|2:已开票|3:无需开具] */
  invoice?: number

  /** 销售详情单 */
  items?: SaleDetailItem[]
}

/**
 * 销售单列表数据对象
 */
export interface SaleListItem {
  /** 销售单id */
  id: string
  /** 所属组织 */
  frame: string
  /** 客户 */
  customer: string
  /** 单据时间 */
  time: string
  /** 单据编号 */
  number: string
  /** 单据金额 */
  total: number
  /** 实际金额 */
  actual: number
  /** 实收金额 */
  money: number
  /** 单据费用 */
  cost: number
  /** 结算账户 */
  account: string
  /** 关联人员 */
  people: string
  /** 物流信息 */
  logistics: string
  /** 单据附件 */
  file: string
  /** 备注信息 */
  data: string
  /** 扩展信息 */
  more: string
  /** 制单人 */
  user: string
  /** 关联单据 */
  source: string

  /** 审核状态 */
  examine: number
  /** 核对状态 */
  check: number
  /** 核销状态 */
  nucleus: number
  /** 费用状态 */
  cse: number
  /** 发票状态 */
  invoice: number
}

/**
 * 销售单查询参数
 */
export interface SaleQueryParams extends PageQuery {
  /** 客户 */
  customer?: string
  /** 单据编号 */
  number?: string
  /** 开始时间 */
  startTime?: string
  /** 结束时间 */
  endTime?: string
  /** 商品名称 */
  goodsName?: string
  /** 关联人员 */
  people?: string
  /** 制单人 */
  user?: string
  /** 备注信息 */
  data?: string

  /** 审核状态[0:未审核|1:已审核] */
  examine?: number
  /** 核对状态[0:未核对|1:已核对] */
  check?: number
  /** 核销状态[0:未核销|1:部分核销|2:已核销] */
  nucleus?: number
  /** 费用状态[0:未结算|1:部分结算|2:已结算|3:无需结算] */
  cse?: number
  /** 发票状态[0:未开票|1:部分开票|2:已开票|3:无需开具] */
  invoice?: number
}

/**
 * 销售退货单生成数据对象
 */
export interface SaleReturnGenerateData {
  /** 退货单ID */
  id: string
  /** 所属组织 */
  frame: string
  /** 客户 */
  customer: string
  /** 单据时间 */
  time: string
  /** 单据编号 */
  number: string
  /** 单据金额 */
  total: number
  /** 实际金额 */
  actual: number
  /** 实付金额 */
  money: number
  /** 单据费用 */
  cost: number
  /** 结算账户 */
  account: string
  /** 关联人员 */
  people: string
  /** 物流信息 */
  logistics: string
  /** 单据附件 */
  file: string
  /** 备注信息 */
  data: string
  /** 扩展信息 */
  more: string
  /** 制单人 */
  user: string
  /** 关联销售单 */
  source: string

  /** 审核状态 */
  examine: number
  /** 核对状态 */
  check: number
  /** 核销状态 */
  nucleus: number
  /** 费用状态 */
  cse: number
  /** 发票状态 */
  invoice: number
}

/**
 * 批量操作参数
 */
export interface BatchOperationParams {
  /** 操作ID列表 */
  ids: string[]
  /** 操作类型 */
  operation: 'examine' | 'check' | 'delete'
  /** 操作值 */
  value?: boolean
}
