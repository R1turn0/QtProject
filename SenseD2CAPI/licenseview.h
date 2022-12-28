#ifndef LICENSEVIEW_H
#define LICENSEVIEW_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <ctype.h>
#include <QDateTime>
#include <QButtonGroup>

#include <inc/d2c.h>
#include <inc/ss_error.h>
#include <inc/ss_lm_runtime.h>
#include <inc/ss_lm_control.h>
#include <common/ss_help.h>

#define PIN_DEFAULT_INDEX       0
#define SLM_DEV_PASSWORD_LENGTH 16
#define CERT_SIZE 2048

#define LIC_DEL_ONE         0
#define LIC_DEL_ALL         1
#define LIC_LOCK_ALL        2
#define LIC_UNLOCK_ALL      3
#define SS_ERROR            1

namespace Ui {
class LicenseView;
}

class LicenseView : public QWidget
{
    Q_OBJECT

public:
    explicit LicenseView(QWidget *parent = nullptr);
    ~LicenseView();

    bool isDigitStr(QString str);

//    SS_UINT32 build_license_d2c(D2C_HANDLE hD2c, SS_UINT32* bWhich);

    int get_result();

    int is_sure();

private slots:
    void on_fileButton_clicked();

    void on_signButton_clicked();

    void on_licenseTypeComboBox_activated(int index);

    void on_licenseIDLineEdit_textChanged(const QString &arg1);

    void on_startTimeCheckBox_stateChanged(int arg1);

    void on_overTimeCheckBox_stateChanged(int arg1);

    void on_timeSpanCheckBox_stateChanged(int arg1);

    void on_useCountCheckBox_stateChanged(int arg1);

    void on_perpetualLicenseCheckBox_stateChanged(int arg1);

    void on_timeSpanLineEdit_textChanged(const QString &arg1);

    void on_useCountLineEdit_textChanged(const QString &arg1);

    void on_startDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_endDateTimeEdit_dateChanged(const QDate &date);

    void on_singleRadioButton_clicked();

    void on_networkRadioButton_clicked();

private:
    Ui::LicenseView *ui;
    cJSON* root = nullptr;
    SS_CHAR* result = nullptr;
    QButtonGroup* concurrentManerRadioButtonGroup = nullptr;
};

#endif // LICENSEVIEW_H
