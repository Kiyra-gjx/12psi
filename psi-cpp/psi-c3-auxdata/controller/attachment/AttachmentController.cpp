#include "stdafx.h"
#include "AttachmentController.h"
#include "../../service/attachment/AttachmentService.h"
#include "../ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "ServerInfo.h"
#include "NacosClient.h"
#include "FastDfsClient.h"
#include "SimpleDateTimeFormat.h"

// 修改附件
ModifyJsonVO::Wrapper AttachmentController::execModifyAttachment(const AttachmentDTO::Wrapper& dto, const PayloadDTO& payload)
{
    // 定义返回数据对象
    auto jvo = ModifyJsonVO::createShared();
    // 参数校验
    if (!dto->id)
    {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }
    // 定义一个Service
    AttachmentService service;
    // 执行数据修改
    dto->setPayload(&payload);
    if (service.modifyData(dto)) {
        jvo->success(dto);
    }
    else
    {
        jvo->fail(dto);
    }
    // 响应结果
    return jvo;
}


// 删除附件
RemoveJsonVO::Wrapper AttachmentController::execRemoveAttachment(const AttachmentRemoveDTO::Wrapper& id)
{
    // 定义返回数据对象
    auto jvo = RemoveJsonVO::createShared();
    // 参数校验
    if (!id->id || !id->save_path)
    {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }
    ZO_CREATE_DFS_CLIENT_URL(dfs, urlPrefix);
    bool ok = dfs.deleteFile(id->save_path.getValue(""));
    if (ok)
    {
        // 定义一个Service
        AttachmentService service;
        // 执行数据删除
        if (service.removeData(id))
        {
            jvo->success(id);
        }
    }
    else
    {
        jvo->fail(nullptr);
    }
    // 响应结果
    return jvo;
}
//查询数据
QueryJsonVO::Wrapper AttachmentController::execQueryAttachment(const AttachmentQuery::Wrapper& query)
{
    auto jvo = QueryJsonVO::createShared();

    try {
        // 直接使用Wrapper对象，避免类型转换
        int page = query->pageIndex ? *query->pageIndex : 1;
        int pageSize = query->pageSize ? *query->pageSize : 10;


        // 直接传递Wrapper对象给Service层（需要修改Service接口）
        auto result = AttachmentService().listAll(query);

        // 创建返回的DTO列表
        auto dtoList = oatpp::List<AttachmentDTO::Wrapper>::createShared();

        // 将结果转换为DTO格式
        for (const auto& item : result.data) {
            auto dto = AttachmentDTO::createShared();
            dto->id = item.id;
            dto->name = item.name;
            dto->file_type = item.file_type;
            dto->save_type = item.save_type;
            dto->save_path = item.save_path;
            dto->remark = item.remark;
            dto->status = item.status;

            dtoList->push_back(dto);
        }

        // 设置成功响应
        jvo->success(dtoList);

    }
    catch (const std::exception& e) {
        std::cout << "查询异常: " << e.what() << std::endl;
    }
    return jvo;
}

// 鏂囦欢绫诲瀷鍒ゆ柇鍑芥暟瀹炵幇锛堟斁鍦ㄤ娇鐢ㄤ箣鍓嶏級
std::string getFileTypeFromExtension(const std::string& filename)
{
    size_t pos = filename.rfind(".");
    if (pos == std::string::npos) return "other";

    std::string extension = filename.substr(pos + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    // 鏂囦欢绫诲瀷鏄犲皠
    if (extension == "jpg" || extension == "jpeg" || extension == "png" ||
        extension == "gif" || extension == "bmp" || extension == "webp") {
        return "image";
    }
    else if (extension == "pdf" || extension == "doc" || extension == "docx" ||
        extension == "xls" || extension == "xlsx" || extension == "ppt" ||
        extension == "pptx" || extension == "txt") {
        return "document";
    }
    else if (extension == "mp4" || extension == "avi" || extension == "mov" ||
        extension == "wmv" || extension == "flv") {
        return "video";
    }
    else if (extension == "mp3" || extension == "wav" || extension == "aac" ||
        extension == "flac") {
        return "audio";
    }
    else if (extension == "zip" || extension == "rar" || extension == "7z" ||
        extension == "tar") {
        return "archive";
    }
    else {
        return "other";
    }
}

// 修复 execAddAttachment 函数中的变量名问题
StringJsonVO::Wrapper AttachmentController::execAddAttachment(std::shared_ptr<IncomingRequest> request)
{
    // 1 初始化multipart数据容器和读取器
    API_MULTIPART_INIT(container, reader);

    // 2 配置读取器使用内存数据提供者
    API_MULTIPART_CONFIG_MEMO_DEFAULT(reader, -1);

    // 3 读取请求体
    request->transferBody(&reader);

    OATPP_LOGD("Multipart", "parts_count=%d", container->count());

    // 4 处理上传文件
    std::string filepath = "";
    std::string filename = "";
    std::string remark = "";

    // 4.1 检查文件是否上传
    API_MULTIPART_PARSE_FILE_FIELD(container, "file", file);
    if (!file) {
        auto jvo = StringJsonVO::createShared();
        jvo->fail("1");  // 修复：使用标准字符串
        return jvo;
    }

    // 4.2 获取文件名
    API_MULTIPART_PARSE_FORM_FIELD_STR(container, "name", nameField);
    if (!nameField || nameField.getValue("").empty()) {
        auto jvo = StringJsonVO::createShared();
        jvo->fail("2");  // 修复：使用标准字符串
        return jvo;
    }
    filename = nameField.getValue("");

    // 4.3 获取备注
    API_MULTIPART_PARSE_FORM_FIELD_STR(container, "remark", remarkField);
    if (remarkField) {
        remark = remarkField.getValue("");
    }

    // 4.4 上传文件到FastDFS
    std::string originalFilename = partfile->getFilename().getValue("");
    std::string suffix = "";
    size_t pos = originalFilename.rfind(".");
    if (pos != std::string::npos) {
        suffix = originalFilename.substr(pos + 1);
    }

    try {
        ZO_CREATE_DFS_CLIENT_URL(dfs, urlPrefix);
        filepath = dfs.uploadFile(file->data(), file->size(), suffix);

        if (filepath.empty()) {
            auto jvo = StringJsonVO::createShared();
            jvo->fail("FastDFS文件上传失败");  // 修复：使用标准字符串
            return jvo;
        }

        OATPP_LOGD("Multipart", "File uploaded successfully. Path: %s", filepath.c_str());
    }
    catch (const std::exception& e) {
        OATPP_LOGE("Multipart", "Failed to upload file to FastDFS: %s", e.what());
        auto jvo = StringJsonVO::createShared();
        jvo->fail("文件上传到FastDFS失败");  // 修复：使用标准字符串
        return jvo;
    }

    // 4.5 自动设置字段
    auto fileForm = AttachmentAddDTO::createShared();

    // 用户提供的字段c
    fileForm->name = filename;
    fileForm->remark = remark;

    // 系统自动生成的字段
    fileForm->save_path = filepath;
    fileForm->file_type = getFileTypeFromExtension(originalFilename); // 现在函数已定义
    fileForm->save_type = "fastdfs";
    fileForm->status = 1;

    //cout <<"name:"<< fileForm->name.getValue("") << endl;
    //cout << "remark:"<< fileForm->remark.getValue("") << endl;
    //cout << "save_path:" << fileForm->save_path.getValue("") << endl;
    //cout << "file_type:" << fileForm->file_type.getValue("") << endl;
    //cout << "save_type:" << fileForm->save_type.getValue("") << endl;
    //cout << "status:" << fileForm->status.getValue(0) << endl;

    // 5 保存到数据库
    std::string id = AttachmentService().saveFile(fileForm);

    // 6 响应结果
    auto jvo = StringJsonVO::createShared();
    if (!id.empty()) {
        jvo->success(id);
    }
    else {
        jvo->fail("文件信息保存到数据库失败");  // 修复：使用标准字符串
    }
    return jvo;
}
