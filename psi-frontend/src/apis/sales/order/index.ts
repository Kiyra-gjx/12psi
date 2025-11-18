import { useHttp } from '@/plugins/http'
import type { JsonVO, PageDTO } from '@/apis/type'
import type {
  SaleDTO,
  SaleListItem,
  SaleQueryParams,
  SaleDetailItem,
  SaleReturnGenerateData,
  BatchOperationParams
} from './type'

/**
 * 销售单API
 */
export class SaleOrderApi {
  private http = useHttp()

  /**
   * 新增销售单
   */
  async addSale(saleDTO: SaleDTO): Promise<JsonVO<SaleDTO>> {
    return this.http.post<SaleDTO>('/sale/form/addSale', saleDTO)
  }

  /**
   * 修改销售单
   */
  async updateSale(saleDTO: SaleDTO): Promise<JsonVO<SaleDTO>> {
    return this.http.put<SaleDTO>('/sale/form/updateSale', saleDTO)
  }

  /**
   * 删除销售单(支持批量)
   */
  async deleteSales(ids: string[]): Promise<JsonVO<number>> {
    return this.http.delete<number>('/sale/form/deleteSales', { ids })
  }

  /**
   * 审核/反审核(支持批量)
   */
  async examineSales(ids: string[], examine: boolean): Promise<JsonVO<number>> {
    return this.http.post<number>(
      '/sale/form/examine',
      { ids },
      {
        params: { examine }
      }
    )
  }

  /**
   * 核对/反核对(支持批量)
   */
  async checkSales(ids: string[], check: boolean): Promise<JsonVO<number>> {
    return this.http.post<number>(
      '/sale/form/check',
      { ids },
      {
        params: { check }
      }
    )
  }

  /**
   * 获取销售单列表（条件+分页）
   */
  async getSaleList(params: SaleQueryParams): Promise<JsonVO<PageDTO<SaleListItem>>> {
    return this.http.get<PageDTO<SaleListItem>>('/sale/form/getSaleList', params)
  }

  /**
   * 获取销售单详情
   */
  async getSaleDetail(params: {
    customer?: string
    number?: string
    time?: string
  }): Promise<JsonVO<SaleDetailItem[]>> {
    return this.http.get<SaleDetailItem[]>('/sale/form/getSaleDetail', params)
  }

  /**
   * 获取生成销售退货单数据
   */
  async getGenerateReturnData(saleId: string): Promise<JsonVO<SaleReturnGenerateData>> {
    return this.http.get<SaleReturnGenerateData>('/sale/form/getGenerateReturnData', { saleId })
  }

  /**
   * 导入销售单详细报表
   */
  async importSales(file: File): Promise<JsonVO<string>> {
    const formData = new FormData()
    formData.append('file', file)
    return this.http.post<string>('/sale/form/import', formData, {
      headers: {
        'Content-Type': 'multipart/form-data'
      }
    })
  }

  /**
   * 导出销售单简单报表
   */
  async exportSimpleReport(ids: string[]): Promise<Blob> {
    return this.http.getFile(
      '/sale/form/export-simple',
      { ids },
      {
        responseType: 'blob'
      }
    )
  }

  /**
   * 导出销售单详情报表
   */
  async exportDetailReport(ids: string[]): Promise<Blob> {
    return this.http.getFile(
      '/sale/form/export-detail',
      { ids },
      {
        responseType: 'blob'
      }
    )
  }
}

// 导出单例
export const saleOrderApi = new SaleOrderApi()

// 默认导出
export default saleOrderApi
