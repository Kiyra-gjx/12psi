<template>
  <el-dialog
    :model-value="visible"
    @update:model-value="handleDialogUpdate"
    title="发票开具"
    width="600px"
    :close-on-click-modal="false"
  >
    <el-form :model="form" label-width="100px" ref="formRef" :rules="rules">
      <el-form-item label="合计金额" prop="totalAmount">
        <el-input v-model="form.totalAmount" disabled />
      </el-form-item>
      <el-form-item label="开票时间" prop="invoiceDate">
        <el-date-picker
          v-model="form.invoiceDate"
          type="date"
          placeholder="选择开票时间"
          value-format="yyyy-MM-dd"
          style="width: 100%"
        />
      </el-form-item>
      <el-form-item label="发票号码" prop="invoiceNumber">
        <el-input v-model="form.invoiceNumber" placeholder="请输入发票号码" />
      </el-form-item>
      <el-form-item label="发票抬头" prop="invoiceTitle">
        <el-input v-model="form.invoiceTitle" placeholder="请输入发票抬头" />
      </el-form-item>
      <el-form-item label="发票附件" prop="attachment">
        <el-upload
          action="#"
          :auto-upload="false"
          :on-change="handleFileChange"
          :file-list="fileList"
        >
          <el-button type="primary">点击上传</el-button>
        </el-upload>
      </el-form-item>
      <el-form-item label="备注信息" prop="remark">
        <el-input v-model="form.remark" type="textarea" :rows="3" placeholder="请输入备注信息" />
      </el-form-item>
    </el-form>
    <template #footer>
      <el-button @click="handleClose">取消</el-button>
      <el-button type="primary" @click="handleConfirm" :loading="loading">开票</el-button>
    </template>
  </el-dialog>
</template>

<script setup lang="ts">
import { ref, reactive, watch } from 'vue'
import { ElMessage } from 'element-plus'
import type { UploadFile } from 'element-plus'

interface InvoiceForm {
  totalAmount: number
  invoiceDate: string
  invoiceNumber: string
  invoiceTitle: string
  attachment?: File
  remark: string
}

interface Props {
  visible: boolean
  selectedRecords: any[]
}

const props = defineProps<Props>()
const emit = defineEmits(['update:visible', 'invoice-success'])

const formRef = ref()
const loading = ref(false)
const fileList = ref<UploadFile[]>([])

const form = reactive<InvoiceForm>({
  totalAmount: 0,
  invoiceDate: '',
  invoiceNumber: '',
  invoiceTitle: '',
  remark: ''
})

const rules = {
  invoiceDate: [{ required: true, message: '请选择开票时间', trigger: 'change' }],
  invoiceNumber: [{ required: true, message: '请输入发票号码', trigger: 'blur' }],
  invoiceTitle: [{ required: true, message: '请输入发票抬头', trigger: 'blur' }]
}

// 处理对话框显示状态更新
const handleDialogUpdate = (value: boolean) => {
  emit('update:visible', value)
}

// 监听可见性变化
watch(
  () => props.visible,
  (val) => {
    if (val) {
      // 计算合计金额
      form.totalAmount = props.selectedRecords.reduce((sum, record) => {
        return sum + (record.invoiceAmount || 0)
      }, 0)
      // 重置表单其他字段
      form.invoiceDate = ''
      form.invoiceNumber = ''
      form.invoiceTitle = ''
      form.remark = ''
      fileList.value = []
    }
  }
)

const handleFileChange = (file: UploadFile) => {
  form.attachment = file.raw
}

const handleClose = () => {
  emit('update:visible', false)
}

const handleConfirm = async () => {
  if (!formRef.value) return

  try {
    const valid = await formRef.value.validate()
    if (!valid) return

    loading.value = true

    // 这里调用开票API
    console.log('开票数据:', form)
    // 模拟API调用
    await new Promise((resolve) => setTimeout(resolve, 1000))

    ElMessage.success('开票成功')
    emit('invoice-success')
    handleClose()
  } catch (error) {
    console.error('开票失败:', error)
    ElMessage.error('开票失败')
  } finally {
    loading.value = false
  }
}
</script>

<style scoped>
/* 可以添加一些样式 */
</style>
