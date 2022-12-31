#include "fileview.h"
#include "ui_fileview.h"

FileView::FileView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileView)
{
    ui->setupUi(this);

    // 限制QLineEdit输入数据类型
    // setFocusPolicy(Qt.NoFocus)设置它不氪获得焦点
    QRegExp regx("[0-9]+$");   // 第一位输入1-9,后输入0-9: [1-9][0-9]+$
    QValidator* validator = new QRegExpValidator(regx);
    ui -> fileOffsetLineEdit        -> setValidator(validator);
    ui -> licenseIDLineEdit         -> setValidator(validator);
}

FileView::~FileView()
{
    delete ui;
}


int FileView::make_reset_d2c_to_file(MASTER_HANDLE hmaster, SS_BYTE* root_ca_cert, SS_UINT32 root_ca_cert_len)
{
    D2C_HANDLE hD2c = NULL;
    SS_UINT32 ret = 0;
    cJSON* root = NULL;
    char temp[256] = {0};

    ret = d2c_file_new(hmaster, &hD2c, SIGN_TYPE_SEED, root_ca_cert, root_ca_cert_len);
    if (ret != SS_OK)
    {
        sprintf(temp, "生成重置锁D2c失败,创建句柄未成功：[Error] 0x%08X\n", ret);
        qDebug() << temp;
        goto failed;
    }

    root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "op", "reset");
    // 设置d2c的有效时间范围
    cJSON_AddNumberToObject(root, "not_before", QDateTime::currentDateTime().toTime_t());
    cJSON_AddNumberToObject(root, "not_after", QDateTime::currentDateTime().toTime_t() + 60 * 60 * 24 * 365 * 10);

    ret = d2c_add_pkg(hD2c, cJSON_PrintUnformatted(root), "bixun_lock_reset");
    if (ret != SS_OK)
    {
        sprintf(temp, "生成重置锁D2c失败,添加升级参数失败：[Error] 0x%08X\n", ret);
        qDebug() << temp;
        goto failed;
    }

    if((ret = make_d2c_to_file(hD2c, "reset_")) != SS_OK)
    {
        sprintf(temp, "写入重置锁D2c文件失败：[Error] 0x%08X\n", ret);
        qDebug() << temp;
        goto failed;
    }

failed:
    if (hD2c != NULL)
    {
        d2c_delete(hD2c);
    }

    if (root)
    {
        free(root);
        root = NULL;
    }

    return ret;
}


int FileView::make_d2c_to_file(D2C_HANDLE d2c_handle, char* filename_prefix)
{
    int ret = 0;
    SS_UINT32 d2c_len = 0;
    char* d2c = NULL;
    char d2c_filename[260] = {0};
    struct tm packtime = {0};
    time_t cur_time;
    char temp[256] = {0};

    ret = d2c_get(d2c_handle, NULL, 0, &d2c_len);
    if (ret != 0 && d2c_len == 0)
    {
        sprintf(temp, "获取D2C长度失败 :%d \n", ret);
        qDebug() << temp;
        return ret;
    }
    else
    {
        d2c = (SS_CHAR*)malloc(d2c_len);
        ret = d2c_get(d2c_handle, d2c, d2c_len, &d2c_len);
        if (ret == SS_OK)
        {
            strncat(d2c_filename, filename_prefix, qstrlen(filename_prefix));
            cur_time = time(NULL);
            packtime = *localtime(&cur_time);
            // 写入本地文件，升级至锁内需要通过 slm_update() API接口，或者使用用户许可工具的加密锁数据升级工具。
            sprintf(d2c_filename + qstrlen(d2c_filename), "%d%d%d%d%d%d", packtime.tm_year + 1900, packtime.tm_mon + 1, packtime.tm_mday,
                packtime.tm_hour, packtime.tm_min, packtime.tm_sec);
            strcat(d2c_filename + qstrlen(d2c_filename), "_package.d2c");
            write_file(d2c_filename, d2c, d2c_len);
            sprintf(temp, "种子码D2C升级包制作成功：\n\t%s\n" ,d2c_filename);
            qDebug() << temp;
        }
        else
        {
            sprintf(temp, "种子码D2C升级包制作失败：[Error] 0x%08X\n", ret);
            qDebug() << temp;
        }
        free(d2c);
    }

    return SS_OK;
}


int FileView::create_JSON()
{
    int ret = SS_ERROR;
    cJSON* root = nullptr;

    root = cJSON_CreateObject();
//    cJSON_DeleteItemFromObject(root, "op");

    cJSON_AddStringToObject(root, "op", operationType);
    cJSON_AddStringToObject(root, "filename", QFileInfo(ui -> fileNameLineEdit -> text()).fileName().toLatin1());
    if (ui -> operationTypeComboBox -> currentText() == "删除文件") goto make_result;
    cJSON_AddStringToObject(root, "filetype", fileType);
    cJSON_AddStringToObject(root, "filebuffer", fileBuffer);
    cJSON_AddNumberToObject(root, "fileoffset", fileOffset.toInt());
    cJSON_AddNumberToObject(root, "bind_lic", bindLic.toInt());

make_result:
    // 输出JSON文件
    result = cJSON_Print(root);
    if (result)
    {
        qDebug() << "signButton result: " << result;
    }
    else
    {
        qDebug() << "signButton error cJSON_Print: " << ret;
        QMessageBox::warning(this, "错误", tr("cJSON_Print error"));
        return ret;
    }
    ui -> showJSONTextEdit -> setText(result);

    return SS_OK;
}


int FileView::is_sure()
{
    if (ui -> operationTypeComboBox -> currentText() == "...")
    {
        QMessageBox::warning(this, "错误", "请选择正确的操作类型");
        return SS_ERROR;
    }
    if (ui -> fileTypeComboBox -> currentText() == "...")
    {
        QMessageBox::warning(this, "错误", "请选择一个文件类型");
        return SS_ERROR;
    }
    if (ui -> fileNameLineEdit -> text() == NULL)
    {
        QMessageBox::warning(this, "错误", "清选择一个文件");
        return SS_ERROR;
    }
    if (ui -> fileOffsetLineEdit -> text() == NULL || ui -> licenseIDLineEdit -> text() == NULL)
        if (QMessageBox::Cancel == QMessageBox::warning(this, "警告", "文件偏移/绑定许可为空时默认为0", QMessageBox::Ok | QMessageBox::Cancel))
            return SS_ERROR;

    return SS_OK;
}


void FileView::on_fileNameToolButton_clicked()
{
    QString szFileName = QFileDialog::getOpenFileName(
                this, tr("选择上传文件"), QCoreApplication::applicationFilePath(),
                "*." + ui -> fileTypeComboBox -> currentText());
    if (szFileName.isEmpty())
    {
        return;
    }
    else
    {
        QString fileNameTemp, filePathTemp, fileSuffixTemp;
        QFileInfo fileInfoTemp = QFileInfo(szFileName);
        fileNameTemp = fileInfoTemp.fileName();         // 文件名
        filePathTemp = fileInfoTemp.suffix();           // 文件后缀
        fileSuffixTemp = fileInfoTemp.absolutePath();   // 绝对路径
    }
    ui -> fileNameLineEdit -> setText(szFileName);
    strcpy(fileName, szFileName.toLatin1());
}


void FileView::on_signButton_clicked()
{
    int ret;

    if (is_sure())
    {
        qDebug() << "is_sure error";
        return;
    }
    ret = create_JSON();
    if (SS_OK != ret)
    {
        qDebug() << "create_JSON error";
        return;
    }
}


void FileView::on_operationTypeComboBox_currentTextChanged(const QString &arg1)
{
    ui -> showJSONTextEdit -> setText(arg1);
    if (arg1 == "添加文件")
    {
        strcpy(operationType, "addfile");

        ui -> fileTypeLabel -> setDisabled(false);
        ui -> fileTypeComboBox -> setDisabled(false);

        ui -> fileNameToolButton -> setDisabled(false);

        ui -> fileOffsetLabel -> setDisabled(false);
        ui -> fileOffsetLineEdit -> setDisabled(false);

        ui -> licenseIDLabel -> setDisabled(false);
        ui -> licenseIDLineEdit -> setDisabled(false);
    }
    else if (arg1 == "更新文件")
    {
        strcpy(operationType, "updatefile");

        ui -> fileTypeLabel -> setDisabled(false);
        ui -> fileTypeComboBox -> setDisabled(false);

        ui -> fileNameToolButton -> setDisabled(false);

        ui -> fileOffsetLabel -> setDisabled(false);
        ui -> fileOffsetLineEdit -> setDisabled(false);

        ui -> licenseIDLabel -> setDisabled(false);
        ui -> licenseIDLineEdit -> setDisabled(false);
    }
    else if (arg1 == "删除文件")
    {
        strcpy(operationType, "delfile");

        ui -> fileTypeLabel -> setDisabled(true);
        ui -> fileTypeComboBox -> setDisabled(true);

        ui -> fileNameToolButton -> setDisabled(true);

        ui -> fileOffsetLabel -> setDisabled(true);
        ui -> fileOffsetLineEdit -> setDisabled(true);

        ui -> licenseIDLabel -> setDisabled(true);
        ui -> licenseIDLineEdit -> setDisabled(true);
    }
}


void FileView::on_fileTypeComboBox_currentTextChanged(const QString &arg1)
{
    strcpy(fileType, arg1.toLatin1().data());
}


void FileView::on_fileOffsetLineEdit_textChanged(const QString &arg1)
{
    fileOffset = arg1;
}


void FileView::on_licenseIDLineEdit_textChanged(const QString &arg1)
{
    bindLic = arg1;
}

