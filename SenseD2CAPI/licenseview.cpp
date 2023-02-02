#include "licenseview.h"
#include "ui_licenseview.h"

LicenseView::LicenseView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LicenseView)
{
    ui->setupUi(this);

    get_result();

    // 限制QLineEdit输入数据类型
    // setFocusPolicy(Qt.NoFocus)设置它不氪获得焦点
    QRegExp regx("[0-9]+$");   // 第一位输入1-9,后输入0-9: [1-9][0-9]+$
    QValidator* validator = new QRegExpValidator(regx);
    ui -> licenseIDLineEdit         -> setValidator(validator);
    ui -> concurrentManerLineEdit   -> setValidator(validator);
    ui -> timeSpanLineEdit          -> setValidator(validator);
    ui -> useCountLineEdit          -> setValidator(validator);
    ui -> startTimeLineEdit         -> setValidator(validator);
    ui -> endTimeLineEdit           -> setValidator(validator);
    ui -> pubDeviationLineEdit      -> setValidator(validator);
    ui -> pubResetSizeLineEdit      -> setValidator(validator);
    ui -> rwDeviationLineEdit       -> setValidator(validator);
    ui -> rwResetSizeLineEdit       -> setValidator(validator);
    ui -> orDeviationLineEdit       -> setValidator(validator);
    ui -> orResetSizeLineEdit       -> setValidator(validator);

    // QLineedit限定只输入16进制字符的正则表达式这样写："^[0-9a-fA-F]+$"
    // 16进制字符后插入空格则 "^[0-9a-fA-F ]+$"

    // 设置QTextEdit输入模式为覆盖
    ui -> pubHexTextEdit -> setOverwriteMode(true);
    ui -> rwHexTextEdit -> setOverwriteMode(true);
    ui -> orHexTextEdit -> setOverwriteMode(true);

    // 设置RadioButtonGrop，添加RadioButton并设置ID，通过checkedId()选择信号
//    QButtonGroup* concurrentManerRadioButtonGroup = new QButtonGroup(this);
//    concurrentManerRadioButtonGroup -> addButton(ui -> singleRadioButton, 0);
//    concurrentManerRadioButtonGroup -> addButton(ui -> networkRadioButton, 1);

    // 设置DateTimeEdit为当前日期
    ui -> startDateTimeEdit -> setDate(QDate::currentDate());
    ui -> endDateTimeEdit -> setDate(QDate::currentDate());
}

LicenseView::~LicenseView()
{
    if (result)
    {
        free(result);
        result = nullptr;
    }
    delete ui;
}


/************************************************************************/
/*                             签发D2C包                                 */
/************************************************************************/
void LicenseView::on_signButton_clicked()
{
    char hmaster_pin[9] = {"12345678"};
    const char *devp_id = "080000000000090d";

    SS_INT32 ret = SS_OK;
    MASTER_HANDLE hmaster = NULL;
    D2C_HANDLE hD2c = NULL;
    SS_UINT32 iWhich = 0;

    SS_CHAR strDevSn[SLM_LOCK_SN_LENGTH*2+1]    = {0};
    SS_BYTE deviceSn[SLM_LOCK_SN_LENGTH] = {0x97, 0x33, 0xc8, 0x01, 0x00, 0x07, 0x02, 0x00, 0xa8, 0x13, 0x00, 0x01, 0x00, 0x41, 0x00, 0x36};

    SS_BYTE p7b_cert[CERT_SIZE*3]               = {0};
    SS_UINT32 p7b_size                          = CERT_SIZE*3;

    SS_CHAR* d2c = nullptr;
    SS_UINT32 d2c_len = 0;
    SS_CHAR d2c_filename[256] = {0};
    SS_CHAR lic_guid[D2C_GUID_LENGTH] = {0};

    // ======== 判断输入数据合法性 ========
    ret = is_sure();
    if (SS_OK != ret)
    {
        qDebug() << "signButton error is_sure: " << ret;
        QMessageBox::warning(this, "错误", tr("is_sure error: %1").arg(ret));
        return;
    }
    // ======== 打开控制所 ========
    ret = master_open(&hmaster);
    if (SS_OK != ret)
    {
        qDebug() << "signButton error master_open: " << ret;
        QMessageBox::warning(this, "错误", tr("master_open error: %1").arg(ret));
        return;
    }
    qDebug() << "signButton success master_open: ";
    // ======== 验证控制所PIN码 ========
    ret = master_pin_verify(hmaster, PIN_DEFAULT_INDEX, (SS_BYTE*)hmaster_pin, strlen(hmaster_pin));
    if (SS_OK != ret)
    {
        master_close(hmaster);
        qDebug() << "signButton error master_pin_verify: " << ret;
        QMessageBox::warning(this, "错误", tr("master_pin_verify error: %1").arg(ret));
        return;
    }
    qDebug() << "signButton success master_pin_verify";

    // ======== 获取p7b证书用于生成许可 ========
    ret = getUserDevP7b(devp_id, p7b_cert, &p7b_size);
    if (SS_OK != ret)
    {
        qDebug() << "signButton error getUserDevP7b: " << ret;
        QMessageBox::warning(this, "错误", tr("getUserDevP7b error: %1").arg(ret));
        return;
    }
    qDebug() << "signButton success getUserDevP7b";

    getUserDevSN(devp_id, strDevSn);
    hexstr_to_bytes(strDevSn, SLM_LOCK_SN_LENGTH, deviceSn);
    // ======== 创建 D2C 句柄，用于签发许可 ========
    ret = d2c_lic_new(hmaster, &hD2c, ACCOUNT_TYPE_NONE, deviceSn, sizeof(deviceSn), p7b_cert, p7b_size);
    if (SS_OK != ret)
    {
        master_close(hmaster);
        qDebug() << "signButton error d2c_lic_new: " << ret;
        QMessageBox::warning(this, tr("错误"), tr("d2c_lic_new error: 0x%1").arg(ret));
        return;
    }
    qDebug() << "signButton success d2c_lic_new";

    // ======== 添加许可信息到d2c句柄并获取许可 =========
    //添加许可信息到d2c句柄
    //ret = build_license_d2c(hD2c, &iWhich);
    ret = d2c_add_lic(hD2c, result, (SS_CHAR*)"manage license sample", lic_guid);
    if (SS_OK != ret)
    {
        qDebug() << "signButton error d2c_add_lic: " << ret;
        QMessageBox::warning(this, tr("错误"), tr("d2c_add_lic error: 0x%1").arg(ret));
        return;
    }

    // 获取签发完的许可，获取buffer传入空，可获取到许可大小
    ret = d2c_get(hD2c, NULL, 0, &d2c_len);
    if (ret != 0 && d2c_len == 0)
    {
        qDebug() << "signButton error d2c_get: " << ret;
        QMessageBox::warning(this, "错误", tr("d2c_get error: %1").arg(ret));
        return;
    }
    else
    {
        d2c = (SS_CHAR*)malloc(d2c_len);
        ret = d2c_get(hD2c, d2c, d2c_len, &d2c_len);
        if (SS_OK == ret)
        {
            // 写入本地文件，升级至锁内需要通过 slm_update() API接口，或者使用用户许可工具的加密锁数据升级工具。
//            strcpy(d2c_filename, strDevSn);
            strcpy(d2c_filename, "SenseD2CAPI");

            if (ui -> licenseTypeComboBox -> currentText() == "许可增加")
                strcat(d2c_filename, "_license_add_one.d2c");
            else if (ui -> licenseTypeComboBox -> currentText() == "许可更新")
                strcat(d2c_filename, "_license_update_one.d2c");
            else if (ui -> licenseTypeComboBox -> currentText() == "许可删除")
                strcat(d2c_filename, "_license_del_one.d2c");
            else if (ui -> licenseTypeComboBox -> currentText() == "删除所有许可")
                strcat(d2c_filename, "_license_del_all.d2c");
            else if (ui -> licenseTypeComboBox -> currentText() == "锁定所有许可")
                strcat(d2c_filename, "_license_lock_all.d2c");
            else if (ui -> licenseTypeComboBox -> currentText() == "解锁所有许可")
                strcat(d2c_filename, "_license_unlock_all.d2c");
            else
                QMessageBox::warning(this, "错误", tr("该功能尚未推出，敬请期待~"));
            write_file(d2c_filename, d2c, d2c_len);
            qDebug() << "signButton success to Update d2c file: " << d2c_filename;
            QMessageBox::information(this, "成功", "Success Update D2C file!");
        }
        else
        {
            QMessageBox::warning(this, "错误", tr("signButton d2c_get error: 0x00%1").arg(ret));
        }
        free(d2c);
    }
    masterPINDeauth(hmaster);
    master_close(hmaster);
    d2c_delete(hD2c);
    return;
}


/************************************************************************/
/*                            制作result                                */
/************************************************************************/
int LicenseView::get_result()
{
    SS_UINT32 ret = SS_ERROR;
    SS_CHAR temp[128] = {0};
    cJSON* root = nullptr;

    root = cJSON_CreateObject();


    // ================ 许可添加/许可更新 ================
    if (ui -> licenseTypeComboBox -> currentText() == "许可增加" || ui -> licenseTypeComboBox -> currentText() == "许可更新")
    {
        QString szLicID = ui -> licenseIDLineEdit -> text();
        SS_UINT32 licID = szLicID.toUInt();

        // ======== 添加许可 ========
        // ======== 强制写入（标识） ========
//        cJSON_AddBoolToObject(root, "force", cJSON_True); // 该项目暂无此按钮
        if (ui -> licenseTypeComboBox -> currentText() == "许可增加")
            cJSON_AddStringToObject(root, "op", "addlic");
        else
            cJSON_AddStringToObject(root, "op", "updatelic");
        // ======== 许可ID ========
        cJSON_AddNumberToObject(root, "license_id", licID);
        // ======== 写入单机/网络锁 ========
        if (ui -> singleRadioButton -> isChecked())
        {
            // 并发访问-单机锁
            cJSON_AddStringToObject(root, "concurrent_type", "process");
            cJSON_AddStringToObject(root, "concurrent", "=0");
        }
        else
        {
            // 并发访问-网络锁
            // 如果不允许并发访问（单机锁），将 concurrent_type 设置为 "process"，concurrent设置为 "=0"。
            // 限制并发类型（会话），限制同时访问许可的电脑数
            // 如果要限制访问许可的程序数量，将 win_user_session 改为 process。
            if (ui -> concurrentManerComboBox -> currentText() == "进程")
                cJSON_AddStringToObject(root, "concurrent_type", "process");
            else
                cJSON_AddStringToObject(root, "concurrent_type", "win_user_session");
            // 同时访问电脑数数量
            sprintf(temp, "=%d", (ui -> concurrentManerLineEdit -> text()).toUInt());
            cJSON_AddStringToObject(root, "concurrent", temp);
        }
        // ======== 许可条件（时间 ========
        // 永久许可
        if (ui -> perpetualLicenseCheckBox -> isChecked())
        {
            // 写入永久许可
        }
        else
        {
            // 开始时间
            if (ui -> startTimeCheckBox -> isChecked())
            {
//                QDateTime startDate = QDateTime::fromString(
//                            QString("%1-%2-%3 %4:%5")
//                            .arg(ui -> startDateTimeEdit -> date().year())
//                            .arg(ui -> startDateTimeEdit -> date().month(), 2, 10, QLatin1Char('0'))
//                            .arg(ui -> startDateTimeEdit -> date().day(), 2, 10, QLatin1Char('0'))
//                            .arg(ui -> startDateTimeEdit -> time().hour(), 2, 10, QLatin1Char('0'))
//                            .arg(ui -> startDateTimeEdit -> time().minute(), 2, 10, QLatin1Char('0')),
//                            "yyyy-MM-dd hh:mm");
//                int startTimestamp = startDate.toUTC().toTime_t();
//                itoa(startTimestamp, temp, 10);
                if (ui -> licenseTypeComboBox -> currentText() == "许可更新")
                {
                    if (ui -> startTimeSetRadioButton -> isChecked())       // 设置
                        sprintf(temp, "=%d", (ui -> startDateTimeEdit -> dateTime()).toUTC().toTime_t());
                    else if (ui -> startTimeAddRadioButton -> isChecked())  // 追加
                        sprintf(temp, "+%d", (ui -> startTimeLineEdit -> text().toLatin1().data()));
                    else if (ui -> startTimeSubRadioButton -> isChecked())  // 减少
                        sprintf(temp, "-%d", (ui -> startTimeLineEdit -> text().toLatin1().data()));
                    else if (ui -> startTimeBanRadioButton -> isChecked())  // 禁用
                        qstrncpy(temp, "disable", sizeof("disable"));
                }
                else
                    sprintf(temp, "=%d", (ui -> startDateTimeEdit -> dateTime()).toUTC().toTime_t());
                cJSON_AddStringToObject(root, "start_time", temp);
            }
            // 结束时间
            if (ui -> endTimeCheckBox -> isChecked())
            {
                if (ui -> licenseTypeComboBox -> currentText() == "许可更新")
                {
                    if (ui -> endTimeSetRadioButton -> isChecked())         // 设置
                        sprintf(temp, "=%d", (ui -> endDateTimeEdit -> dateTime()).toUTC().toTime_t());
                    else if (ui -> endTimeAddRadioButton -> isChecked())    // 追加
                        sprintf(temp, "+%d", (ui -> endTimeLineEdit -> text().toLatin1().data()));
                    else if (ui -> endTimeSubRadioButton -> isChecked())    // 减少
                        sprintf(temp, "-%d", (ui -> endTimeLineEdit -> text().toLatin1().data()));
                    else if (ui -> endTimeBanRadioButton -> isChecked())    // 禁用
                        qstrncpy(temp, "disable", sizeof("disable"));
                }
                else
                    sprintf(temp, "=%d", (ui -> endDateTimeEdit -> dateTime()).toUTC().toTime_t());
                cJSON_AddStringToObject(root, "end_time", temp);
            }
            // ======== 时间跨度 ========
            if (ui -> timeSpanCheckBox -> isChecked())
            {
                int TimeSpanNum = (ui -> timeSpanLineEdit -> text()).toUInt();
                if (ui -> timeSpanComboBox -> currentText() == "天")
                    TimeSpanNum *= 24 * 3600;
                if (ui -> licenseTypeComboBox -> currentText() == "许可更新")
                {
                    if (ui -> timeSpanSetRadioButton -> isChecked())
                        sprintf(temp, "=%d", TimeSpanNum);
                    else if (ui -> timeSpanAddRadioButton -> isChecked())
                        sprintf(temp, "+%d", TimeSpanNum);
                    else if (ui -> timeSpanSubRadioButton -> isChecked())
                        sprintf(temp, "-%d", TimeSpanNum);
                    else if (ui -> timeSpanBanRadioButton -> isChecked())
                        qstrncpy(temp, "disable", sizeof("disable"));
                }
                else
                    sprintf(temp, "=%d", TimeSpanNum);
                cJSON_AddStringToObject(root, "span", temp);
            }
            // ======== 使用计数 ========
            if (ui -> useCountCheckBox -> isChecked())
            {
                if (ui -> licenseTypeComboBox -> currentText() == "许可更新")
                {
                    if (ui -> useCountSetRadioButton -> isChecked())
                        sprintf(temp, "=%d", (ui -> useCountLineEdit -> text()).toUInt());
                    else if (ui -> useCountAddRadioButton -> isChecked())
                        sprintf(temp, "+%d", (ui -> useCountLineEdit -> text()).toUInt());
                    else if (ui -> useCountSubRadioButton -> isChecked())
                        sprintf(temp, "-%d", (ui -> useCountLineEdit -> text()).toUInt());
                    else if (ui -> useCountBanRadioButton -> isChecked())
                        qstrncpy(temp, "disable", sizeof("disable"));
                }
                else
                    sprintf(temp, "=%d", (ui -> useCountLineEdit -> text()).toUInt());



                cJSON_AddStringToObject(root, "counter", temp);
            }
        }
    }


    // ================ 许可更新 ================
//    else if (ui -> licenseTypeComboBox -> currentText() == "许可更新")
//    {
//        QString szLicID = ui -> licenseIDLineEdit -> text();
//        SS_UINT32 licID = szLicID.toUInt();
//        // 添加许可
//        cJSON_AddStringToObject(root, "op", "updatelic");
//        // 许可ID
//        cJSON_AddNumberToObject(root, "license_id", licID);
//    }


    // ================ 许可删除 ================
    else if (ui -> licenseTypeComboBox -> currentText() == "许可删除")
    {
        // 删除单条指定许可 iWhich == LIC_DEL_ONE
        cJSON_AddStringToObject(root, "op", "dellic");
        // 许可ID
        QString szLicID = ui -> licenseIDLineEdit -> text();
        SS_UINT32 licID = szLicID.toUInt();   // QByteArray::toUShort
        cJSON_AddNumberToObject(root, "license_id", licID);
    }


    // ================ 删除所有许可 ================
    else if (ui -> licenseTypeComboBox -> currentText() == "删除所有许可")
    {
        //全部删除，包括数据区 iWhich == LIC_DEL_ALL
        cJSON_AddStringToObject(root, "op", "delalllic");
    }


    // ================ 锁定所有许可 ================
    else if (ui -> licenseTypeComboBox -> currentText() == "锁定所有许可")
    {
        // 锁定所有许可 iWhich == LIC_LOCK_ALL
        cJSON_AddStringToObject(root, "op", "lockalllic");
    }


    // ================ 解锁所有许可 ================
    else if (ui -> licenseTypeComboBox -> currentText() == "解锁所有许可")
    {
        // 解锁所有许可 iWhich == LIC_UNLOCK_ALL
        cJSON_AddStringToObject(root, "op", "unlockalllic");
    }


    // ================ 公开区 ================
    if (ui -> publicGroupBox -> isChecked() && ui -> publicGroupBox -> isEnabled())
    {
        cJSON* dateArea = nullptr;
        dateArea = cJSON_CreateObject();
        QString pubDate = ui -> pubTextEdit -> toPlainText();
//        bytes_to_hexstr(pubDate.toUtf8(), pubDate.length(), temp);
        qstrncpy(temp,pubDate.toLatin1().toHex(), pubDate.length() * 4);

        cJSON_AddStringToObject(dateArea, "data", temp);
        cJSON_AddNumberToObject(dateArea, "offset", 0);
        cJSON_AddNumberToObject(dateArea, "resize", pubDate.length());
        cJSON_AddItemToObject(root, "pub", dateArea);
    }


    // ================ 读写区 ================
    if (ui -> readWriteGroupBox -> isChecked() && ui -> readWriteGroupBox -> isEnabled())
    {
        cJSON* dateArea = nullptr;
        dateArea = cJSON_CreateObject();
        QString pubDate = ui -> rwTextEdit -> toPlainText();
        bytes_to_hexstr(pubDate.toUtf8(), pubDate.length(), temp);

        cJSON_AddStringToObject(dateArea, "data", temp);
        cJSON_AddNumberToObject(dateArea, "offset", 0);
        cJSON_AddNumberToObject(dateArea, "resize", pubDate.length());
        cJSON_AddItemToObject(root, "raw", dateArea);
    }


    // ================ 只读区 ================
    if (ui -> onlyReadGroupBox -> isChecked() && ui -> onlyReadGroupBox -> isEnabled())
    {
        cJSON* dateArea = nullptr;
        dateArea = cJSON_CreateObject();
        QString pubDate = ui -> orTextEdit -> toPlainText();
        bytes_to_hexstr(pubDate.toUtf8(), pubDate.length(), temp);

        cJSON_AddStringToObject(dateArea, "data", temp);
        cJSON_AddNumberToObject(dateArea, "offset", 0);
        cJSON_AddNumberToObject(dateArea, "resize", pubDate.length());
        cJSON_AddItemToObject(root, "rom", dateArea);
    }


    // ================制作result================
    result = cJSON_Print(root);
    if (result)
    {
        qDebug() << "signButton result: " << result;
        ui -> previewTextBrowser -> setText(result);
    }
    else
    {
        qDebug() << "signButton error cJSON_Print: " << ret;
        QMessageBox::warning(this, "错误", tr("cJSON_Print error"));
        return ret;
    }

    // ================释放root================
    if (root)
    {
        cJSON_Delete(root);
        root = nullptr;
    }

    return SS_OK;
}


/************************************************************************/
/*                         判断参数是否合法                                */
/************************************************************************/
int LicenseView::is_sure()
{
    int ret = SS_ERROR;

    // 判断许可ID是否合法
    if ((ui -> licenseIDLineEdit -> text()).isEmpty() && ui -> licenseIDLineEdit -> isEnabled())
    {
        QMessageBox::warning(this, "错误", "许可ID不能为空");
        return ret;
    }
//    QString szLicID = ui -> licenseIDLineEdit -> text();
//    if (!isDigitStr(szLicID))
//    {
//        QMessageBox::warning(this, "错误", "许可ID不合法");
//        return ret;
//    }

    // 判断并发数是否合法
    if (ui -> networkRadioButton -> isChecked())
    {
        unsigned int concurrentNum = (ui -> concurrentManerLineEdit -> text()).toUInt();
        if (0 == concurrentNum)
        {
            QMessageBox::warning(this, "错误", "设置并发数必须大于0");
            return ret;
        }
    }

    // 判断许可时间
    if (ui -> startTimeCheckBox -> isChecked()
            && ui -> endTimeCheckBox -> isChecked()
            && ui -> startTimeCheckBox -> isEnabled()
            && ui -> endTimeCheckBox -> isEnabled())
    {
        unsigned int startYear = ui -> startDateTimeEdit -> date().year();
        unsigned int startMonth = ui -> startDateTimeEdit -> date().month();
        unsigned int startDay = ui -> startDateTimeEdit -> date().day();
        unsigned int startHour = ui -> startDateTimeEdit -> time().hour();
        unsigned int startMinute = ui -> startDateTimeEdit -> time().minute();
        unsigned int overYear = ui -> endDateTimeEdit -> date().year();
        unsigned int overMonth = ui -> endDateTimeEdit -> date().month();
        unsigned int overDay = ui -> endDateTimeEdit -> date().day();
        unsigned int overHour = ui -> endDateTimeEdit -> time().hour();
        unsigned int overMinute = ui -> endDateTimeEdit -> time().minute();

        if (overYear > startYear)
            qDebug() << "signButton success Date OK!";
        else if (overYear == startYear && overMonth > startMonth)
            qDebug() << "signButton success Date OK!";
        else if (overYear == startYear && overMonth == startMonth && overDay > startDay)
            qDebug() << "signButton success Date OK!";
        else if (overYear == startYear && overMonth == startMonth && overDay == startDay && overHour > startHour)
            qDebug() << "signButton success Date OK!";
        else if (overYear == startYear && overMonth == startMonth && overDay == startDay && overHour == startHour && overMinute > startMinute)
            qDebug() << "signButton success Date OK!";
        else
        {
            QMessageBox::warning(this, "错误", "许可时间不合法");
            return ret;
        }
        qDebug() << "signButton success startTime:  " << startYear << "/" << startMonth << "/" << startDay << " " << startHour << ":" << startMinute;
        qDebug() << "signButton success overTime:   " << overYear << "/" << overMonth << "/" << overDay << " " << overHour << ":" << overMinute;
    }

    // 判断使用次数是否合法
    if (ui -> useCountCheckBox -> isChecked())
    {
        unsigned int useCountNum = (ui -> useCountLineEdit -> text()).toUInt();
        if (0 == useCountNum)
        {
            QMessageBox::warning(this, "错误", "使用次数必须大于0");
            return ret;
        }
    }

    return SS_OK;
}


bool LicenseView::isDigitStr(QString str)
{
    QByteArray BArray = str.toLatin1();
    const char* s = BArray.data();

    if (str.isEmpty())
        return false;
    while (*s && *s >= '0' && *s <= '9')
        s++;
    if (*s)
        return false;
    else
        return true;
}


// ================ 永久许可 ================
void LicenseView::on_perpetualLicenseCheckBox_stateChanged(int arg1)
{
    get_result();

    // StartTimeLayout
    ui -> startTimeCheckBox -> setDisabled(arg1);

    // EndTimeLayout
    ui -> endTimeCheckBox -> setDisabled(arg1);

    // TimeSpanLayout
    ui -> timeSpanCheckBox -> setDisabled(arg1);

    // UseCountLayout
    ui -> useCountCheckBox -> setDisabled(arg1);
}


/************************************************************************/
/*                            设置许可类型                                */
/************************************************************************/
void LicenseView::on_licenseTypeComboBox_activated(int index)
{
    QString licenseType_str = ui -> licenseTypeComboBox -> currentText();
    if (licenseType_str == "锁定所有许可" || licenseType_str == "解锁所有许可" || licenseType_str == "删除所有许可")
    {
        // setDisabled(true) == setEnabled(false)
        // LicenseIDLayout
        ui -> licenseIDLabel -> setDisabled(true);
        ui -> licenseIDLineEdit -> setDisabled(true);
        ui -> perpetualLicenseCheckBox -> setDisabled(true);
        ui -> perpetualLicenseCheckBox -> setChecked(false);

        // ConcurrentManerLayout
        ui -> concurrentManerLabel -> setDisabled(true);
        ui -> singleRadioButton -> setDisabled(true);
        ui -> networkRadioButton -> setDisabled(true);
        ui -> concurrentManerComboBox -> setDisabled(true);
        ui -> concurrentManerLineEdit -> setDisabled(true);

        // StartTimeLayout
        ui -> startTimeCheckBox -> setDisabled(true);

        // EndtimeLayout
        ui -> endTimeCheckBox -> setDisabled(true);

        // TimeSpanLayout
        ui -> timeSpanCheckBox -> setDisabled(true);

        // UseCountLayout
        ui -> useCountCheckBox -> setDisabled(true);

        // DataLayout
        ui -> publicGroupBox -> setDisabled(true);
        ui -> readWriteGroupBox -> setDisabled(true);
        ui -> onlyReadGroupBox ->setDisabled(true);
    }
    else if (licenseType_str == "许可增加")
    {
        // setDisabled(true) == setEnabled(false)
        // LicenseIDLayout
        ui -> licenseIDLabel -> setDisabled(false);
        ui -> licenseIDLineEdit -> setDisabled(false);
        ui -> perpetualLicenseCheckBox -> setDisabled(false);

        // ConcurrentManerLayout
        ui -> concurrentManerLabel -> setDisabled(false);
        ui -> singleRadioButton -> setDisabled(false);
        ui -> networkRadioButton -> setDisabled(false);
        ui -> concurrentManerComboBox -> setDisabled(true);
        ui -> concurrentManerLineEdit -> setDisabled(true);

        // StartTimeLayout
        ui -> startTimeCheckBox -> setDisabled(false);
        ui -> startTimeSetRadioButton -> setDisabled(true);
        ui -> startTimeAddRadioButton -> setDisabled(true);
        ui -> startTimeSubRadioButton -> setDisabled(true);
        ui -> startTimeBanRadioButton -> setDisabled(true);
        ui -> startTimeLineEdit -> setDisabled(true);

        // EndTimeLayout
        ui -> endTimeCheckBox -> setDisabled(false);
        ui -> endTimeSetRadioButton -> setDisabled(true);
        ui -> endTimeAddRadioButton -> setDisabled(true);
        ui -> endTimeSubRadioButton -> setDisabled(true);
        ui -> endTimeBanRadioButton -> setDisabled(true);
        ui -> endTimeLineEdit -> setDisabled(true);

        // TimeSpanLayout
        ui -> timeSpanCheckBox -> setDisabled(false);
        ui -> timeSpanSetRadioButton -> setDisabled(true);
        ui -> timeSpanAddRadioButton -> setDisabled(true);
        ui -> timeSpanSubRadioButton -> setDisabled(true);
        ui -> timeSpanBanRadioButton -> setDisabled(true);

        // UseCountLayout
        ui -> useCountCheckBox -> setDisabled(false);
        ui -> useCountSetRadioButton -> setDisabled(true);
        ui -> useCountAddRadioButton -> setDisabled(true);
        ui -> useCountSubRadioButton -> setDisabled(true);
        ui -> useCountBanRadioButton -> setDisabled(true);

        // DataLayout
        ui -> publicGroupBox -> setDisabled(false);
        ui -> readWriteGroupBox -> setDisabled(false);
        ui -> onlyReadGroupBox ->setDisabled(false);
    }
    else if (licenseType_str == "许可更新")
    {
        // setDisabled(true) == setEnabled(false)
        // LicenseIDLayout
        ui -> licenseIDLabel -> setDisabled(false);
        ui -> licenseIDLineEdit -> setDisabled(false);
        ui -> perpetualLicenseCheckBox -> setDisabled(false);
        ui -> perpetualLicenseCheckBox -> setChecked(false);

        // ConcurrentManerLayout
        ui -> concurrentManerLabel -> setDisabled(false);
        ui -> singleRadioButton -> setDisabled(false);
        ui -> networkRadioButton -> setDisabled(false);
        ui -> concurrentManerComboBox -> setDisabled(false);
        ui -> concurrentManerLineEdit -> setDisabled(false);

        // StartTimeLayout
        ui -> startTimeCheckBox -> setDisabled(false);
        ui -> startTimeSetRadioButton -> setDisabled(false);
        ui -> startTimeAddRadioButton -> setDisabled(false);
        ui -> startTimeSubRadioButton -> setDisabled(false);
        ui -> startTimeBanRadioButton -> setDisabled(false);
        ui -> startTimeLineEdit -> setDisabled(true);

        // EndtimeLayout
        ui -> endTimeCheckBox -> setDisabled(false);
        ui -> endTimeSetRadioButton -> setDisabled(false);
        ui -> endTimeAddRadioButton -> setDisabled(false);
        ui -> endTimeSubRadioButton -> setDisabled(false);
        ui -> endTimeBanRadioButton -> setDisabled(false);
        ui -> endTimeLineEdit -> setDisabled(true);

        // TimeSpanLayout
        ui -> timeSpanCheckBox -> setDisabled(false);
        ui -> timeSpanSetRadioButton -> setDisabled(false);
        ui -> timeSpanAddRadioButton -> setDisabled(false);
        ui -> timeSpanSubRadioButton -> setDisabled(false);
        ui -> timeSpanBanRadioButton -> setDisabled(false);

        // UseCountLayout
        ui -> useCountCheckBox -> setDisabled(false);
        ui -> useCountSetRadioButton -> setDisabled(false);
        ui -> useCountAddRadioButton -> setDisabled(false);
        ui -> useCountSubRadioButton -> setDisabled(false);
        ui -> useCountBanRadioButton -> setDisabled(false);

        // DataLayout
        ui -> publicGroupBox -> setDisabled(false);
        ui -> readWriteGroupBox -> setDisabled(false);
        ui -> onlyReadGroupBox -> setDisabled(false);
    }
    else if (licenseType_str == "许可删除")
    {
        // setDisabled(true) == setEnabled(false)
        // LicenseIDLayout
        ui -> licenseIDLabel -> setDisabled(false);
        ui -> licenseIDLineEdit -> setDisabled(false);
        ui -> perpetualLicenseCheckBox -> setDisabled(true);
        ui -> perpetualLicenseCheckBox -> setChecked(false);

        // ConcurrentManerLayout
        ui -> concurrentManerLabel -> setDisabled(true);
        ui -> singleRadioButton -> setDisabled(true);
        ui -> networkRadioButton -> setDisabled(true);
        ui -> concurrentManerComboBox -> setDisabled(true);
        ui -> concurrentManerLineEdit -> setDisabled(true);

        // StartTimeLayout
        ui -> startTimeCheckBox -> setDisabled(true);

        // EndTimeLayout
        ui -> endTimeCheckBox -> setDisabled(true);

        // TimeSpanLayout
        ui -> timeSpanCheckBox -> setDisabled(true);

        // UseCountLayout
        ui -> useCountCheckBox -> setDisabled(true);

        // DataLayout
        ui -> publicGroupBox -> setDisabled(true);
        ui -> readWriteGroupBox -> setDisabled(true);
        ui -> onlyReadGroupBox ->setDisabled(true);
    }
    get_result();   // 重新调用一次生成result
}



//SS_UINT32 LicenseView::build_license_d2c(D2C_HANDLE hD2c, SS_UINT32* bWhich)
//{
//    SS_UINT32 ret = SS_ERROR;
//    SS_UINT32 licID;
//    QString szLicID;
//    SS_CHAR lic_guid[D2C_GUID_LENGTH] = {0};

//    root = cJSON_CreateObject();
//    if(ui -> licenseTypeComboBox -> currentText() == "许可删除")
//    {
//        // 删除单条指定许可 iWhich == LIC_DEL_ONE
//        cJSON_AddStringToObject(root, "op", "dellic");
//        // 许可ID
//        szLicID = ui -> licenseIDLineEdit -> text();
//        if (!isDigitStr(szLicID))
//        {
//            QMessageBox::warning(this, "错误", "许可ID不合法");
//            return ret;
//        }
//        licID = szLicID.toUInt();   // QByteArray::toUShort
//        cJSON_AddNumberToObject(root, "license_id", licID);
//        *bWhich = LIC_DEL_ONE;
//    }
//    else if(ui -> licenseTypeComboBox -> currentText() == "删除所有许可")
//    {
//        //全部删除，包括数据区 iWhich == LIC_DEL_ALL
//        cJSON_AddStringToObject(root, "op", "delalllic");
//        *bWhich = LIC_DEL_ALL;
//    }
//    else if(ui -> licenseTypeComboBox -> currentText() == "锁定所有许可")
//    {
//        // 锁定所有许可 iWhich == LIC_LOCK_ALL
//        cJSON_AddStringToObject(root, "op", "lockalllic");
//        *bWhich = LIC_LOCK_ALL;
//    }
//    else if(ui -> licenseTypeComboBox -> currentText() == "解锁所有许可")
//    {
//        // 解锁所有许可 iWhich == LIC_UNLOCK_ALL
//        cJSON_AddStringToObject(root, "op", "unlockalllic");
//        *bWhich = LIC_UNLOCK_ALL;
//    }

//    result = cJSON_Print(root);
//    if (result)
//    {
//        qDebug() << "signButton result: " << result;
//        ret = d2c_add_lic(hD2c, result, (SS_CHAR*)"manage license sample", lic_guid);
//        ui -> previewTextBrowser -> setText(result);
//        free(result);
//        result = NULL;
//    }
//    else
//    {
//        qDebug() << "signButton error cJSON_Print: " << ret;
//        QMessageBox::warning(this, "错误", tr("cJSON_Print error"));
//        return ret;
//    }
//    if (SS_OK != ret)
//    {
//        qDebug() << "signButton error d2c_add_lic: " << ret;
//        QMessageBox::warning(this, "错误", tr("d2c_add_lic error: %1").arg(ret));
//        return ret;
//    }
//    if (root)
//    {
//        cJSON_Delete(root);
//        root = nullptr;
//    }

//    return ret;
//}


// ================ 设置单机锁 ================
void LicenseView::on_singleRadioButton_clicked()
{
    get_result();
    ui -> concurrentManerComboBox -> setDisabled(true);
    ui -> concurrentManerLineEdit -> setDisabled(true);
}


// ================ 选择网络锁 ================
void LicenseView::on_networkRadioButton_clicked()
{
    get_result();
    ui -> concurrentManerComboBox -> setDisabled(false);
    ui -> concurrentManerLineEdit -> setDisabled(false);
}


void LicenseView::on_concurrentManerComboBox_activated(int index)
{
    get_result();
}


void LicenseView::on_concurrentManerLineEdit_textChanged(const QString &arg1)
{
    get_result();
}


void LicenseView::on_startTimeCheckBox_clicked()
{
    get_result();
}


void LicenseView::on_endTimeCheckBox_clicked()
{
    get_result();
}


void LicenseView::on_timeSpanCheckBox_clicked()
{
    get_result();
}


void LicenseView::on_useCountCheckBox_clicked()
{
    get_result();
}


void LicenseView::on_licenseIDLineEdit_textChanged(const QString &arg1)
{
    get_result();
}


void LicenseView::on_timeSpanLineEdit_textChanged(const QString &arg1)
{
    get_result();
}


void LicenseView::on_useCountLineEdit_textChanged(const QString &arg1)
{
    get_result();
}


void LicenseView::on_startDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    get_result();
}


void LicenseView::on_endDateTimeEdit_dateChanged(const QDate &date)
{
    get_result();
}


// ================ 公开区-槽 ================
void LicenseView::on_publicGroupBox_clicked()
{
    get_result();
}

void LicenseView::on_pubDeviationCheckBox_stateChanged(int arg1)
{
    get_result();
    ui -> pubDeviationLineEdit -> setEnabled(arg1);
}


void LicenseView::on_pubDeviationLineEdit_textChanged(const QString &arg1)
{
    get_result();
}


void LicenseView::on_pubResetSizeCheckBox_stateChanged(int arg1)
{
    ui -> pubResetSizeLineEdit -> setEnabled(arg1);
    get_result();
}


void LicenseView::on_pubResetSizeLineEdit_textChanged(const QString &arg1)
{
    get_result();
}


void LicenseView::on_pubHexTextEdit_textChanged()
{
    // 在输入模式为覆盖时，先删除被覆盖的字符，此时触发一次textChanged信号，后再输入覆盖的字符，不触发textChanged信号
    get_result();

    if (ui -> pubHexTextEdit -> hasFocus())
        showStringView();
}


void LicenseView::on_pubTextEdit_textChanged()
{
    get_result();

    if (ui -> pubTextEdit -> hasFocus())
        showHexView();
}


// ================ 读写区-槽 ================
void LicenseView::on_readWriteGroupBox_clicked()
{
    get_result();
}


void LicenseView::on_rwDeviationCheckBox_stateChanged(int arg1)
{
    ui -> rwDeviationLineEdit -> setEnabled(arg1);
    get_result();
}


void LicenseView::on_rwDeviationLineEdit_textChanged(const QString &arg1)
{
    get_result();
}


void LicenseView::on_rwResetSizeCheckBox_stateChanged(int arg1)
{
    ui -> rwResetSizeLineEdit -> setEnabled(arg1);
    get_result();
}


void LicenseView::on_rwResetSizeLineEdit_textChanged(const QString &arg1)
{
    get_result();
}


void LicenseView::on_rwHexTextEdit_textChanged()
{
    get_result();

    if (ui -> pubHexTextEdit -> hasFocus())
        showStringView();
}


void LicenseView::on_rwTextEdit_textChanged()
{
    get_result();

    if (ui -> pubTextEdit -> hasFocus())
        showHexView();
}


// ================ 只读区-槽 ================
void LicenseView::on_onlyReadGroupBox_clicked()
{
    get_result();
}


void LicenseView::on_orDeviationCheckBox_stateChanged(int arg1)
{
    ui -> orDeviationLineEdit -> setEnabled(arg1);
    get_result();
}


void LicenseView::on_orDeviationLineEdit_textChanged(const QString &arg1)
{
    get_result();
}


void LicenseView::on_orResetSizeCheckBox_stateChanged(int arg1)
{
    ui -> orResetSizeLineEdit -> setEnabled(arg1);
    get_result();
}


void LicenseView::on_orResetSizeLineEdit_textChanged(const QString &arg1)
{
    get_result();
}


void LicenseView::on_orHexTextEdit_textChanged()
{
    get_result();

    if (ui -> pubHexTextEdit -> hasFocus())
        showStringView();
}


void LicenseView::on_orTextEdit_textChanged()
{
    get_result();

    showHexView();

    if (ui -> pubTextEdit -> hasFocus())
        showHexView();
}


// ================ Start Time Radio Button-槽 ================
void LicenseView::on_startTimeSetRadioButton_clicked()
{
    ui -> startDateTimeEdit -> setDisabled(false);
    ui -> startTimeLineEdit -> setDisabled(true);
}


void LicenseView::on_startTimeAddRadioButton_clicked()
{
    ui -> startDateTimeEdit -> setDisabled(true);
    ui -> startTimeLineEdit -> setDisabled(false);
}


void LicenseView::on_startTimeSubRadioButton_clicked()
{
    ui -> startDateTimeEdit -> setDisabled(true);
    ui -> startTimeLineEdit -> setDisabled(false);
}


void LicenseView::on_startTimeBanRadioButton_clicked()
{
    ui -> startDateTimeEdit -> setDisabled(true);
    ui -> startTimeLineEdit -> setDisabled(true);
}


// ================ End Time Radio Button-槽 ================
void LicenseView::on_endTimeSetRadioButton_clicked()
{
    ui -> endDateTimeEdit -> setDisabled(false);
    ui -> endTimeLineEdit -> setDisabled(true);
}


void LicenseView::on_endTimeAddRadioButton_clicked()
{
    ui -> endDateTimeEdit -> setDisabled(true);
    ui -> endTimeLineEdit -> setDisabled(false);
}


void LicenseView::on_endTimeSubRadioButton_clicked()
{
    ui -> endDateTimeEdit -> setDisabled(true);
    ui -> endTimeLineEdit -> setDisabled(false);
}


void LicenseView::on_endTimeBanRadioButton_clicked()
{
    ui -> endDateTimeEdit -> setDisabled(true);
    ui -> endTimeLineEdit -> setDisabled(true);
}


// ================ Time Span Radio Button-槽 ================
void LicenseView::on_timeSpanSetRadioButton_clicked()
{
    ui -> timeSpanLineEdit -> setDisabled(false);
    ui -> timeSpanComboBox -> setDisabled(false);
}


void LicenseView::on_timeSpanAddRadioButton_clicked()
{
    ui -> timeSpanLineEdit -> setDisabled(false);
    ui -> timeSpanComboBox -> setDisabled(false);
}


void LicenseView::on_timeSpanSubRadioButton_clicked()
{
    ui -> timeSpanLineEdit -> setDisabled(false);
    ui -> timeSpanComboBox -> setDisabled(false);
}


void LicenseView::on_timeSpanBanRadioButton_clicked()
{
    ui -> timeSpanLineEdit -> setDisabled(true);
    ui -> timeSpanComboBox -> setDisabled(true);
}


// ================ Use Count Radio Button-槽 ================
void LicenseView::on_useCountSetRadioButton_clicked()
{
    ui -> useCountLineEdit -> setDisabled(false);
}


void LicenseView::on_useCountAddRadioButton_clicked()
{
    ui -> useCountLineEdit -> setDisabled(false);
}


void LicenseView::on_useCountSubRadioButton_clicked()
{
    ui -> useCountLineEdit -> setDisabled(false);
}


void LicenseView::on_useCountBanRadioButton_clicked()
{
    ui -> useCountLineEdit -> setDisabled(true);
}


void LicenseView::showHexView()
{
    QString str = ui -> pubTextEdit -> toPlainText();
    QByteArray bytes;

    ui -> pubHexTextEdit -> setText("");
    for (QString::const_iterator cit = str.cbegin(); cit < str.cend(); cit++)
    {
        // .append() 会自动换行，.insertPlainText() 不会自动换行
        ui -> pubHexTextEdit -> insertPlainText(QString(*cit).toLatin1().toHex());
        ui -> pubHexTextEdit -> insertPlainText(" ");
    }

    //    // 将QString转译为Hex后显示在Hex编辑器中，注释原因为转移为Hex后中间没有空格
    //    QString str = ui -> pubTextEdit -> toPlainText();
    //    ui -> pubHexTextEdit -> setText(str.toLatin1().toHex());
}


void LicenseView::showStringView()
{
    unsigned char inChar, tmp;
    QString str = ui -> pubHexTextEdit -> toPlainText();
    QString outStr;
    QByteArray bytes;
    QString tmpStr1, tmpStr2;

    // 输入两个Hex数后添加空格
    str = str.replace(" ", "");// 移除空格
    int len = str.count();

    // 记录光标所在位置
    QTextCursor cursor = ui -> pubHexTextEdit -> textCursor();
    int blockNumber = cursor.blockNumber();
    int columnNumber = cursor.columnNumber();

    // 获取文本，并在每个Hex中间加入空格
    tmpStr2 = "";
    for (int i = 0; i < (((len + 1) / 2) - 1); i++)
    {
        tmpStr1 = str.mid(i * 2, 2);
        tmpStr2 += tmpStr1 + " ";
    }
    tmpStr1 = str.mid(len - (2 - len % 2), 2);
    tmpStr2 += tmpStr1;
    if (len % 2 == 0)
        tmpStr2 += " ";

    // 临时屏蔽控件信号，设置Hex文本
    ui -> pubHexTextEdit -> blockSignals(true);
    ui -> pubHexTextEdit -> setText(tmpStr2);
    ui -> pubHexTextEdit -> blockSignals(false);

    // 移动光标到末尾
//    cursor.movePosition(QTextCursor::End);
    cursor.setPosition(columnNumber);
    ui -> pubHexTextEdit -> setTextCursor(cursor);

    // 将Hex转换为字符并显示
    str.remove(QRegExp("\\s"));
    if (str.count() % 2 != 0)
        str.append("0");
    bytes = str.toLatin1();
//    bytes.fromHex(bytes);
    ui -> pubTextEdit -> setText(bytes.fromHex(bytes));
}
