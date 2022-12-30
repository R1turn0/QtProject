#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <ctype.h>
#include <QDateTime>
#include <QFileDialog>
#include <time.h>

#include <inc/d2c.h>
#include <inc/ss_error.h>
#include <inc/ss_lm_runtime.h>
#include <inc/ss_lm_control.h>
#include <common/ss_help.h>

#define MAX_PATH 260

namespace Ui {
class FileView;
}

class FileView : public QWidget
{
    Q_OBJECT

public:
    explicit FileView(QWidget *parent = nullptr);
    ~FileView();

    int make_reset_d2c_to_file(MASTER_HANDLE hmaster, SS_BYTE* root_ca_cert, SS_UINT32 root_ca_cert_len);

    int make_d2c_to_file(D2C_HANDLE d2c_handle, char* filename_prefix);

    int create_JSON();

private slots:
    void on_licenseButton_clicked();

    void on_fileNameToolButton_clicked();

    void on_cancelButton_clicked();

    void on_signButton_clicked();

    void on_operationTypeComboBox_currentTextChanged(const QString &arg1);

    void on_fileTypeComboBox_currentTextChanged(const QString &arg1);

    void on_fileOffsetLineEdit_textChanged(const QString &arg1);

    void on_licenseIDLineEdit_textChanged(const QString &arg1);

private:
    Ui::FileView *ui;
    SS_CHAR* result;
    char operationType[12];
    char timeStamp[11];
    char fileType[4];
    char fileName[256];
    char fileBuffer[256];
    QString fileOffset;
    QString bindLic;
};

#endif // FILEVIEW_H
