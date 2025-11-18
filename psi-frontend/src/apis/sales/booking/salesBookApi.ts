import { useHttp } from '@/plugins/http'
import type { JsonVO, PageDTO, PageQuery } from '@/apis/type'
import type { AxiosRequestConfig } from 'axios'

/**
 * 销售订单数据对象
 */
export interface SaleOrderData {
  id?: string
  number?: string
  time?: string
  customer?: string
  total?: number
  actual?: number
  examine?: number
  state?: number
  user?: string
  people?: string
  logistics?: string
  file?: string
  data?: string
  more?: string
  frame?: string
  arrival?: string
}

/**
 * 销售订单查询参数
 */
export interface SaleOrderQuery extends PageQuery {
  id?: string
  number?: string
  customer?: string
  time?: string
  examine?: number
  state?: number
  user?: string
  startTime?: string
  endTime?: string
  startArrival?: string
  endArrival?: string
  data?: string // 添加缺失的 data 属性
}

/**
 * 销售订单详情数据对象
 */
export interface SaleOrderDetailData {
  id?: string
  pid?: string
  goods?: string
  nums?: number
  handle?: number
  price?: number
  discount?: number
  dsc?: number
  total?: number
  tax?: number
  tat?: number
  tpt?: number
  unit?: string
  attr?: string
  warehouse?: string
  data?: string
}

/**
 * 销售订单审核请求对象
 */
export interface SaleOrderVerifyRequest {
  ids: string[]
  num: number // 1:审核, 0:反审核
}

/**
 * 生成采购订单数据传输对象
 */
export interface GeneratePurchaseOrderData {
  id?: string
  number?: string
  time?: string
  supplier?: string
  total?: number
  actual?: number
  money?: number
  examine?: number
  check?: number
  invoice?: number
  nucleus?: number
  cse?: number
  cost?: number
  user?: string
  people?: string
  logistics?: string
  file?: string
  data?: string
  more?: string
  frame?: string
  account?: string
  source?: string
}

/**
 * 生成销售订单数据传输对象
 */
export interface GenerateSaleOrderData {
  id?: string
  number?: string
  time?: string
  customer?: string
  total?: number
  actual?: number
  money?: number
  examine?: number
  check?: number
  invoice?: number
  nucleus?: number
  cse?: number
  cost?: number
  user?: string
  people?: string
  logistics?: string
  file?: string
  data?: string
  more?: string
  frame?: string
  account?: string
  source?: string
}

// 创建HTTP实例
const http = useHttp()

/**
 * 销售订单API
 */
export const salesBookApi = {
  /**
   * 获取销售订单列表（条件+分页）
   */
  getSaleOrdersList: (
    query: SaleOrderQuery,
    config?: AxiosRequestConfig
  ): Promise<JsonVO<PageDTO<SaleOrderData>>> => {
    return http.post('/sale/order/saleOrdersList', query, config)
  },

  /**
   * 新增销售订单
   */
  addSaleOrder: (data: SaleOrderData, config?: AxiosRequestConfig): Promise<JsonVO<boolean>> => {
    return http.post('/sale/order/saleOrdersAdd', data, config)
  },

  /**
   * 修改销售订单
   */
  updateSaleOrder: (data: SaleOrderData, config?: AxiosRequestConfig): Promise<JsonVO<boolean>> => {
    return http.put('/sale/order/saleOrdersUpdate', data, config)
  },

  /**
   * 批量删除销售订单 - 修复参数格式
   */
  deleteSaleOrders: (ids: string[], config?: AxiosRequestConfig): Promise<JsonVO<boolean>> => {
    // 直接传递数组，而不是对象包装
    return http.delete('/sale/order/saleOrdersDelete', ids, config)
  },

  /**
   * 获取指定销售订单详情
   */
  getSaleOrderInfo: (
    params: { customer?: string; number?: string; time?: string },
    config?: AxiosRequestConfig
  ): Promise<JsonVO<SaleOrderDetailData[][]>> => {
    return http.get('/sale/order/saleOrderInfo', params, config)
  },

  /**
   * 批量审核/反审核销售订单
   */
  verifySaleOrders: (
    request: SaleOrderVerifyRequest,
    config?: AxiosRequestConfig
  ): Promise<JsonVO<boolean>> => {
    return http.post('/sale/order/saleOrdersVerify', request, config)
  },

  /**
   * 导入数据
   */
  importSaleOrders: (file: File, config?: AxiosRequestConfig): Promise<JsonVO<boolean>> => {
    const formData = new FormData()
    formData.append('file', file)
    return http.postWithFile('/sale/order/saleOrderImport', formData, config)
  },

  /**
   * 导出详细报表
   */
  exportDetailReport: (billNos: string[], config?: AxiosRequestConfig): Promise<any> => {
    return http.getFile(
      '/sale/order/saleOrderExportDetail',
      { billNo: billNos },
      {
        ...config,
        responseType: 'blob'
      }
    )
  },

  /**
   * 导出简单报表
   */
  exportSimpleReport: (billNos: string[], config?: AxiosRequestConfig): Promise<any> => {
    return http.getFile(
      '/sale/order/saleOrderExportSimple',
      { billNo: billNos },
      {
        ...config,
        responseType: 'blob'
      }
    )
  },

  /**
   * 获取生成采购订单数据
   */
  getGeneratePurchaseOrderData: (
    purchaseId: string,
    config?: AxiosRequestConfig
  ): Promise<JsonVO<GeneratePurchaseOrderData>> => {
    return http.get('/sale/order/getGeneratePurchaseOrderData', { purchaseId }, config)
  },

  /**
   * 获取生成销售单数据
   */
  getGenerateSaleOrderData: (
    saleId: string,
    config?: AxiosRequestConfig
  ): Promise<JsonVO<GenerateSaleOrderData>> => {
    return http.get('/sale/order/getGenerateSaleOrderData', { saleId }, config)
  }
}

export default salesBookApi
