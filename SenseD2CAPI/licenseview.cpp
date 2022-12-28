#include "licenseview.h"
#include "ui_licenseview.h"

LicenseView::LicenseView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LicenseView)
{
    ui->setupUi(this);

    get_result();

    // 限制QLineEdit输入数据类型
    QRegExp regx("[0-9]+$");   // 第一位输入1-9,后输入0-9: [1-9][0-9]+$
    QValidator* validator = new QRegExpValidator(regx);
    ui -> licenseIDLineEdit         -> setValidator(validator);
    ui -> concurrentManerLineEdit   -> setValidator(validator);
    ui -> timeSpanLineEdit          -> setValidator(validator);
    ui -> useCountLineEdit          -> setValidator(validator);

//    QButtonGroup* concurrentManerRadioButtonGroup = new QButtonGroup(this);
    concurrentManerRadioButtonGroup -> addButton(ui -> singleRadioButton, 0);
    concurrentManerRadioButtonGroup -> addButton(ui -> networkRadioButton, 1);
}

LicenseView::~LicenseView()
{
    if (result)
    {
        free(result);
        result = nullptr;
    }
    if (root)
    {
        cJSON_Delete(root);
        root = nullptr;
    }
    delete ui;
}

void LicenseView::on_signButton_clicked()
{
    char hmaster_pin[33] = {"12345678"};
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

    ret = is_sure();
    if (SS_OK != ret)
    {
        qDebug() << "signButton error is_sure: " << ret;
        QMessageBox::warning(this, "错误", tr("is_sure error: %1").arg(ret));
        return;
    }
    ret = master_open(&hmaster);
    if (SS_OK != ret)
    {
        qDebug() << "signButton error master_open: " << ret;
        QMessageBox::warning(this, "错误", tr("master_open error: %1").arg(ret));
        return;
    }
    qDebug() << "signButton success master_open: ";
    ret = master_pin_verify(hmaster, PIN_DEFAULT_INDEX, (SS_BYTE*)hmaster_pin, strlen(hmaster_pin));
    if (SS_OK != ret)
    {
        master_close(hmaster);
        qDebug() << "signButton error master_pin_verify: " << ret;
        QMessageBox::warning(this, "错误", tr("master_pin_verify error: %1").arg(ret));
        return;
    }
    qDebug() << "signButton success master_pin_verify";

    // ========获取p7b证书用于生成许可========
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
    ret = d2c_lic_new(hmaster, &hD2c, ACCOUNT_TYPE_NONE, deviceSn, sizeof(deviceSn), p7b_cert, p7b_size);
    if (SS_OK != ret)
    {
        master_close(hmaster);
        qDebug() << "signButton error d2c_lic_new: " << ret;
        QMessageBox::warning(this, tr("错误"), tr("d2c_lic_new error: 0x%1").arg(ret));
        return;
    }
    qDebug() << "signButton success d2c_lic_new";

    // ========添加许可信息到d2c句柄并获取许可=========
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
            strcpy(d2c_filename, strDevSn);

            if (iWhich == LIC_DEL_ONE)
                strcat(d2c_filename, "_license_del_one.d2c");
            else if (iWhich == LIC_DEL_ALL)
                strcat(d2c_filename, "_license_del_all.d2c");
            else if (iWhich == LIC_LOCK_ALL)
                strcat(d2c_filename, "_license_lock_all.d2c");
            else if (iWhich == LIC_UNLOCK_ALL)
                strcat(d2c_filename, "_license_unlock_all.d2c");
            else
                QMessageBox::warning(this, "提示", tr("该功能尚未推出，敬请期待~"));
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


int LicenseView::get_result()
{
    SS_UINT32 ret = SS_ERROR;
    SS_CHAR temp[128] = {0};

    root = cJSON_CreateObject();
    if (ui -> licenseTypeComboBox -> currentText() == "许可增加")
    {
        QString szLicID = ui -> licenseIDLineEdit -> text();
        SS_UINT32 licID = szLicID.toUInt();
        // 添加许可
        cJSON_AddStringToObject(root, "op", "addlic");
        // 强制写入（标识）
//        cJSON_AddBoolToObject(root, "force", cJSON_True);
        // 许可ID
        cJSON_AddNumberToObject(root, "license_id", licID);
        // 许可条件（时间
        // 永久许可
//        switch (concurrentManerRadioButtonGroup -> checkedId())
//        {
//        case 0:
//            /************************************************************************/
//            /*                      并发访问-单机锁                                 */
//            /************************************************************************/
//            // 单机锁和网络锁设置只能是二选一
//            cJSON_AddStringToObject(root, "concurrent_type", "process");
//            cJSON_AddStringToObject(root, "concurrent", "=0");
//            break;
//        case 1:
//            /************************************************************************/
//            /*                      并发访问-网络锁                                 */
//            /************************************************************************/
//            // 如果不允许并发访问（单机锁），将 concurrent_type 设置为 "process"，concurrent设置为 "=0"。
//            // 限制并发类型（会话），限制同时访问许可的电脑数
//            // 如果要限制访问许可的程序数量，将 win_user_session 改为 process。
//            cJSON_AddStringToObject(root, "concurrent_type", "win_user_session");
//            // 同时访问电脑数数量
//            cJSON_AddStringToObject(root, "concurrent", "=3");
//            break;
//        }

        if (ui -> perpetualLicenseCheckBox -> isChecked())
        {
            // 写入永久许可
            cJSON_AddStringToObject(root, "???", temp);
        }
        // 开始时间
        if (ui -> startTimeCheckBox -> isChecked())
        {
//            QDateTime startDate = QDateTime::fromString(
//                        QString("%1-%2-%3 %4:%5")
//                        .arg(ui -> startDateTimeEdit -> date().year())
//                        .arg(ui -> startDateTimeEdit -> date().month(), 2, 10, QLatin1Char('0'))
//                        .arg(ui -> startDateTimeEdit -> date().day(), 2, 10, QLatin1Char('0'))
//                        .arg(ui -> startDateTimeEdit -> time().hour(), 2, 10, QLatin1Char('0'))
//                        .arg(ui -> startDateTimeEdit -> time().minute(), 2, 10, QLatin1Char('0')),
//                        "yyyy-MM-dd hh:mm");
//            int startTimestamp = startDate.toUTC().toTime_t();
//            itoa(startTimestamp, temp, 10);
            QDateTime dateTime = ui -> startDateTimeEdit -> dateTime();
            sprintf(temp, "=%d", dateTime.toUTC().toTime_t());
            cJSON_AddStringToObject(root, "start_time", temp);
        }
        // 结束时间
        if (ui -> overTimeCheckBox -> isChecked())
        {
            QDateTime dateTime = ui -> startDateTimeEdit -> dateTime();
            sprintf(temp, "=%d", dateTime.toUTC().toTime_t());
            cJSON_AddStringToObject(root, "end_time", temp);
        }
        // 时间跨度
        if (ui -> timeSpanCheckBox -> isChecked())
        {
            QString szTimeSpan = ui -> timeSpanLineEdit -> text();
            sprintf(temp, "=%d", szTimeSpan.toUInt());
            cJSON_AddStringToObject(root, "span", temp);
        }
        // 使用计数
        if (ui -> useCountCheckBox -> isChecked())
        {
            QString szUseCount = ui -> useCountLineEdit -> text();
            sprintf(temp, "=%d", szUseCount.toUInt());
            cJSON_AddStringToObject(root, "counter", temp);
        }
    }
    else if (ui -> licenseTypeComboBox -> currentText() == "许可更新")
    {
        QString szLicID = ui -> licenseIDLineEdit -> text();
        SS_UINT32 licID = szLicID.toUInt();
        // 添加许可
        cJSON_AddStringToObject(root, "op", "updatelic");
        // 许可ID
        cJSON_AddNumberToObject(root, "license_id", licID);

    }
    else if (ui -> licenseTypeComboBox -> currentText() == "许可删除")
    {
        // 删除单条指定许可 iWhich == LIC_DEL_ONE
        cJSON_AddStringToObject(root, "op", "dellic");
        // 许可ID
        QString szLicID = ui -> licenseIDLineEdit -> text();
        SS_UINT32 licID = szLicID.toUInt();   // QByteArray::toUShort
        cJSON_AddNumberToObject(root, "license_id", licID);
    }
    else if (ui -> licenseTypeComboBox -> currentText() == "删除所有许可")
    {
        //全部删除，包括数据区 iWhich == LIC_DEL_ALL
        cJSON_AddStringToObject(root, "op", "delalllic");
    }
    else if (ui -> licenseTypeComboBox -> currentText() == "锁定所有许可")
    {
        // 锁定所有许可 iWhich == LIC_LOCK_ALL
        cJSON_AddStringToObject(root, "op", "lockalllic");
    }
    else if (ui -> licenseTypeComboBox -> currentText() == "解锁所有许可")
    {
        // 解锁所有许可 iWhich == LIC_UNLOCK_ALL
        cJSON_AddStringToObject(root, "op", "unlockalllic");
    }

    result = cJSON_Print(root);
    if (result)
    {
        qDebug() << "signButton result: " << result;
        ui -> previewTextEdit -> setText(result);
    }
    else
    {
        qDebug() << "signButton error cJSON_Print: " << ret;
        QMessageBox::warning(this, "错误", tr("cJSON_Print error"));
        return ret;
    }

    return SS_OK;
}


// 判断参数是否合法
int LicenseView::is_sure()
{
    int ret = SS_ERROR;

    // 判断许可ID是否合法
//    QString szLicID = ui -> licenseIDLineEdit -> text();
//    if (!isDigitStr(szLicID))
//    {
//        QMessageBox::warning(this, "错误", "许可ID不合法");
//        return ret;
//    }

    // 判断许可时间
    if (ui -> startTimeCheckBox -> isChecked() && ui -> overTimeCheckBox -> isChecked())
    {
        int startYear = ui -> startDateTimeEdit -> date().year();
        int startMonth = ui -> startDateTimeEdit -> date().month();
        int startDay = ui -> startDateTimeEdit -> date().day();
        int startHour = ui -> startDateTimeEdit -> time().hour();
        int startMinute = ui -> startDateTimeEdit -> time().minute();
        int overYear = ui -> endDateTimeEdit -> date().year();
        int overMonth = ui -> endDateTimeEdit -> date().month();
        int overDay = ui -> endDateTimeEdit -> date().day();
        int overHour = ui -> endDateTimeEdit -> time().hour();
        int overMinute = ui -> endDateTimeEdit -> time().minute();

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


void LicenseView::on_licenseIDLineEdit_textChanged(const QString &arg1)
{
    get_result();
}


void LicenseView::on_startTimeCheckBox_stateChanged(int arg1)
{
    get_result();
}


void LicenseView::on_overTimeCheckBox_stateChanged(int arg1)
{
    get_result();
}


void LicenseView::on_timeSpanCheckBox_stateChanged(int arg1)
{
    get_result();
}


void LicenseView::on_useCountCheckBox_stateChanged(int arg1)
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


void LicenseView::on_perpetualLicenseCheckBox_stateChanged(int arg1)
{
    get_result();

    // StartTimeLayout
    ui -> startTimeCheckBox -> setDisabled(arg1);
    ui -> startTimeSetRadioButton -> setDisabled(arg1);
    ui -> startTimeAddRadioButton -> setDisabled(arg1);
    ui -> startTimeSubRadioButton -> setDisabled(arg1);
    ui -> startTimeBanRadioButton -> setDisabled(arg1);
    ui -> startDateTimeEdit -> setDisabled(arg1);
    ui -> startDateTimeEdit -> setDisabled(arg1);

    // OvertimeLayout
    ui -> overTimeCheckBox -> setDisabled(arg1);
    ui -> overTimeSetRadioButton -> setDisabled(arg1);
    ui -> overTimeAddRadioButton -> setDisabled(arg1);
    ui -> overTimeSubRadioButton -> setDisabled(arg1);
    ui -> overTimeBanRadioButton -> setDisabled(arg1);
    ui -> endDateTimeEdit -> setDisabled(arg1);
    ui -> endDateTimeEdit -> setDisabled(arg1);

    // TimeSpanLayout
    ui -> timeSpanCheckBox -> setDisabled(arg1);
    ui -> timeSpanSetRadioButton -> setDisabled(arg1);
    ui -> timeSpanAddRadioButton -> setDisabled(arg1);
    ui -> timeSpanSubRadioButton -> setDisabled(arg1);
    ui -> timeSpanBanRadioButton -> setDisabled(arg1);
    ui -> timeSpanLineEdit -> setDisabled(arg1);
    ui -> timeSpanComboBox -> setDisabled(arg1);

    // UseCountLayout
    ui -> useCountCheckBox -> setDisabled(arg1);
    ui -> useCountSetRadioButton -> setDisabled(arg1);
    ui -> useCountAddRadioButton -> setDisabled(arg1);
    ui -> useCountSubRadioButton -> setDisabled(arg1);
    ui -> useCountBanRadioButton -> setDisabled(arg1);
    ui -> useCountLineEdit -> setDisabled(arg1);
}


void LicenseView::on_licenseTypeComboBox_activated(int index)
{
    QString licenseType_str = ui -> licenseTypeComboBox -> currentText();
    get_result();
    if (licenseType_str == "锁定所有许可" || licenseType_str == "解锁所有许可" || licenseType_str == "删除所有许可")
    {
        // setDisabled(true) == setEnabled(false)
        // LicenseIDLayout
        ui -> licenseIDLabel -> setDisabled(true);
        ui -> licenseIDLineEdit -> setDisabled(true);
        ui -> perpetualLicenseCheckBox -> setDisabled(true);

        // ConcurrentManerLayout
        ui -> concurrentManerLabel -> setDisabled(true);
        ui -> singleRadioButton -> setDisabled(true);
        ui -> networkRadioButton -> setDisabled(true);
        ui -> concurrentManerComboBox -> setDisabled(true);
        ui -> concurrentManerLineEdit -> setDisabled(true);

        // StartTimeLayout
        ui -> startTimeCheckBox -> setDisabled(true);
        ui -> startTimeSetRadioButton -> setDisabled(true);
        ui -> startTimeAddRadioButton -> setDisabled(true);
        ui -> startTimeSubRadioButton -> setDisabled(true);
        ui -> startTimeBanRadioButton -> setDisabled(true);
        ui -> startDateTimeEdit -> setDisabled(true);
        ui -> startDateTimeEdit -> setDisabled(true);

        // OvertimeLayout
        ui -> overTimeCheckBox -> setDisabled(true);
        ui -> overTimeSetRadioButton -> setDisabled(true);
        ui -> overTimeAddRadioButton -> setDisabled(true);
        ui -> overTimeSubRadioButton -> setDisabled(true);
        ui -> overTimeBanRadioButton -> setDisabled(true);
        ui -> endDateTimeEdit -> setDisabled(true);
        ui -> endDateTimeEdit -> setDisabled(true);

        // TimeSpanLayout
        ui -> timeSpanCheckBox -> setDisabled(true);
        ui -> timeSpanSetRadioButton -> setDisabled(true);
        ui -> timeSpanAddRadioButton -> setDisabled(true);
        ui -> timeSpanSubRadioButton -> setDisabled(true);
        ui -> timeSpanBanRadioButton -> setDisabled(true);
        ui -> timeSpanLineEdit -> setDisabled(true);
        ui -> timeSpanComboBox -> setDisabled(true);

        // UseCountLayout
        ui -> useCountCheckBox -> setDisabled(true);
        ui -> useCountSetRadioButton -> setDisabled(true);
        ui -> useCountAddRadioButton -> setDisabled(true);
        ui -> useCountSubRadioButton -> setDisabled(true);
        ui -> useCountBanRadioButton -> setDisabled(true);
        ui -> useCountLineEdit -> setDisabled(true);

        // DataLayout
        ui -> readonlyCheckBox -> setDisabled(true);
        ui -> readonlyButton -> setDisabled(true);
        ui -> readWriteCheckBox -> setDisabled(true);
        ui -> readWriteButton -> setDisabled(true);
        ui -> publicCheckBox -> setDisabled(true);
        ui -> publicButton -> setDisabled(true);
    }
    else if (licenseType_str == "许可增加" || licenseType_str == "许可更新")
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
        ui -> concurrentManerComboBox -> setDisabled(false);
        ui -> concurrentManerLineEdit -> setDisabled(false);

        // StartTimeLayout
        ui -> startTimeCheckBox -> setDisabled(false);
        ui -> startTimeSetRadioButton -> setDisabled(false);
        ui -> startTimeAddRadioButton -> setDisabled(false);
        ui -> startTimeSubRadioButton -> setDisabled(false);
        ui -> startTimeBanRadioButton -> setDisabled(false);
        ui -> startDateTimeEdit -> setDisabled(false);
        ui -> startDateTimeEdit -> setDisabled(false);

        // OvertimeLayout
        ui -> overTimeCheckBox -> setDisabled(false);
        ui -> overTimeSetRadioButton -> setDisabled(false);
        ui -> overTimeAddRadioButton -> setDisabled(false);
        ui -> overTimeSubRadioButton -> setDisabled(false);
        ui -> overTimeBanRadioButton -> setDisabled(false);
        ui -> endDateTimeEdit -> setDisabled(false);
        ui -> endDateTimeEdit -> setDisabled(false);

        // TimeSpanLayout
        ui -> timeSpanCheckBox -> setDisabled(false);
        ui -> timeSpanSetRadioButton -> setDisabled(false);
        ui -> timeSpanAddRadioButton -> setDisabled(false);
        ui -> timeSpanSubRadioButton -> setDisabled(false);
        ui -> timeSpanBanRadioButton -> setDisabled(false);
        ui -> timeSpanLineEdit -> setDisabled(false);
        ui -> timeSpanComboBox -> setDisabled(false);

        // UseCountLayout
        ui -> useCountCheckBox -> setDisabled(false);
        ui -> useCountSetRadioButton -> setDisabled(false);
        ui -> useCountAddRadioButton -> setDisabled(false);
        ui -> useCountSubRadioButton -> setDisabled(false);
        ui -> useCountBanRadioButton -> setDisabled(false);
        ui -> useCountLineEdit -> setDisabled(false);

        // DataLayout
        ui -> readonlyCheckBox -> setDisabled(false);
        ui -> readonlyButton -> setDisabled(false);
        ui -> readWriteCheckBox -> setDisabled(false);
        ui -> readWriteButton -> setDisabled(false);
        ui -> publicCheckBox -> setDisabled(false);
        ui -> publicButton -> setDisabled(false);
    }
    else if (licenseType_str == "许可删除")
    {
        // setDisabled(true) == setEnabled(false)
        // LicenseIDLayout
        ui -> licenseIDLabel -> setDisabled(false);
        ui -> licenseIDLineEdit -> setDisabled(false);
        ui -> perpetualLicenseCheckBox -> setDisabled(true);

        // ConcurrentManerLayout
        ui -> concurrentManerLabel -> setDisabled(true);
        ui -> singleRadioButton -> setDisabled(true);
        ui -> networkRadioButton -> setDisabled(true);
        ui -> concurrentManerComboBox -> setDisabled(true);
        ui -> concurrentManerLineEdit -> setDisabled(true);

        // StartTimeLayout
        ui -> startTimeCheckBox -> setDisabled(true);
        ui -> startTimeSetRadioButton -> setDisabled(true);
        ui -> startTimeAddRadioButton -> setDisabled(true);
        ui -> startTimeSubRadioButton -> setDisabled(true);
        ui -> startTimeBanRadioButton -> setDisabled(true);
        ui -> startDateTimeEdit -> setDisabled(true);
        ui -> startDateTimeEdit -> setDisabled(true);

        // OvertimeLayout
        ui -> overTimeCheckBox -> setDisabled(true);
        ui -> overTimeSetRadioButton -> setDisabled(true);
        ui -> overTimeAddRadioButton -> setDisabled(true);
        ui -> overTimeSubRadioButton -> setDisabled(true);
        ui -> overTimeBanRadioButton -> setDisabled(true);
        ui -> endDateTimeEdit -> setDisabled(true);
        ui -> endDateTimeEdit -> setDisabled(true);

        // TimeSpanLayout
        ui -> timeSpanCheckBox -> setDisabled(true);
        ui -> timeSpanSetRadioButton -> setDisabled(true);
        ui -> timeSpanAddRadioButton -> setDisabled(true);
        ui -> timeSpanSubRadioButton -> setDisabled(true);
        ui -> timeSpanBanRadioButton -> setDisabled(true);
        ui -> timeSpanLineEdit -> setDisabled(true);
        ui -> timeSpanComboBox -> setDisabled(true);

        // UseCountLayout
        ui -> useCountCheckBox -> setDisabled(true);
        ui -> useCountSetRadioButton -> setDisabled(true);
        ui -> useCountAddRadioButton -> setDisabled(true);
        ui -> useCountSubRadioButton -> setDisabled(true);
        ui -> useCountBanRadioButton -> setDisabled(true);
        ui -> useCountLineEdit -> setDisabled(true);

        // DataLayout
        ui -> readonlyCheckBox -> setDisabled(true);
        ui -> readonlyButton -> setDisabled(true);
        ui -> readWriteCheckBox -> setDisabled(true);
        ui -> readWriteButton -> setDisabled(true);
        ui -> publicCheckBox -> setDisabled(true);
        ui -> publicButton -> setDisabled(true);
    }
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
//        ui -> previewTextEdit -> setText(result);
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


void LicenseView::on_singleRadioButton_clicked()
{
    ui -> concurrentManerComboBox -> setDisabled(true);
    ui -> concurrentManerLineEdit -> setDisabled(true);
}


void LicenseView::on_networkRadioButton_clicked()
{
    ui -> concurrentManerComboBox -> setDisabled(false);
    ui -> concurrentManerLineEdit -> setDisabled(false);
}

