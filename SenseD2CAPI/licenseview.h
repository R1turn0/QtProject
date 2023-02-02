#ifndef LICENSEVIEW_H
#define LICENSEVIEW_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <ctype.h>
#include <QDateTime>

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

    void showHexView();

    void showStringView();

private slots:
    void on_fileButton_clicked();

    void on_signButton_clicked();

    void on_licenseTypeComboBox_activated(int index);

    void on_licenseIDLineEdit_textChanged(const QString &arg1);

    void on_perpetualLicenseCheckBox_stateChanged(int arg1);

    void on_timeSpanLineEdit_textChanged(const QString &arg1);

    void on_useCountLineEdit_textChanged(const QString &arg1);

    void on_startDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_endDateTimeEdit_dateChanged(const QDate &date);

    void on_singleRadioButton_clicked();

    void on_networkRadioButton_clicked();

    void on_concurrentManerComboBox_activated(int index);

    void on_concurrentManerLineEdit_textChanged(const QString &arg1);

    void on_startTimeCheckBox_clicked();

    void on_endTimeCheckBox_clicked();

    void on_timeSpanCheckBox_clicked();

    void on_useCountCheckBox_clicked();

    void on_publicGroupBox_clicked();

    void on_pubDeviationCheckBox_stateChanged(int arg1);

    void on_pubDeviationLineEdit_textChanged(const QString &arg1);

    void on_pubResetSizeCheckBox_stateChanged(int arg1);

    void on_pubResetSizeLineEdit_textChanged(const QString &arg1);

    void on_pubHexTextEdit_textChanged();

    void on_pubTextEdit_textChanged();

    void on_readWriteGroupBox_clicked();

    void on_rwDeviationCheckBox_stateChanged(int arg1);

    void on_rwDeviationLineEdit_textChanged(const QString &arg1);

    void on_rwResetSizeCheckBox_stateChanged(int arg1);

    void on_rwResetSizeLineEdit_textChanged(const QString &arg1);

    void on_rwHexTextEdit_textChanged();

    void on_rwTextEdit_textChanged();

    void on_onlyReadGroupBox_clicked();

    void on_orDeviationCheckBox_stateChanged(int arg1);

    void on_orDeviationLineEdit_textChanged(const QString &arg1);

    void on_orResetSizeCheckBox_stateChanged(int arg1);

    void on_orResetSizeLineEdit_textChanged(const QString &arg1);

    void on_orHexTextEdit_textChanged();

    void on_orTextEdit_textChanged();

    void on_cancelButton_clicked();

    void on_startTimeSetRadioButton_clicked();

    void on_startTimeAddRadioButton_clicked();

    void on_startTimeSubRadioButton_clicked();

    void on_startTimeBanRadioButton_clicked();

    void on_endTimeSetRadioButton_clicked();

    void on_endTimeAddRadioButton_clicked();

    void on_endTimeSubRadioButton_clicked();

    void on_endTimeBanRadioButton_clicked();

    void on_timeSpanSetRadioButton_clicked();

    void on_timeSpanAddRadioButton_clicked();

    void on_timeSpanSubRadioButton_clicked();

    void on_timeSpanBanRadioButton_clicked();

    void on_useCountSetRadioButton_clicked();

    void on_useCountAddRadioButton_clicked();

    void on_useCountSubRadioButton_clicked();

    void on_useCountBanRadioButton_clicked();

private:
    Ui::LicenseView *ui;
    SS_CHAR* result = nullptr;
};

#endif // LICENSEVIEW_H
