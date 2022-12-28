#include "fileview.h"
#include "ui_fileview.h"

FileView::FileView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileView)
{
    ui->setupUi(this);
    QString operationType_str = ui -> operationTypeComboBox -> currentText();
    QString fileType_str = ui -> fileTypeComboBox -> currentText();
    ui -> fileDownloadTextEdit -> setText( "当前选择：" + operationType_str + "\n" + "当前选择：" + fileType_str);
}

FileView::~FileView()
{
    delete ui;
}


void FileView::on_fileNameToolButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(
                this, tr("选择上传文件"), QCoreApplication::applicationFilePath(),
                tr("*"));
    if (fileName.isEmpty())
    {
//        QMessageBox::warning(this, "警告", "请选择一个文件");
    }
    else
    {
        QString operationType_str = ui -> operationTypeComboBox -> currentText();
        QString fileType_str = ui -> fileTypeComboBox -> currentText();
        ui -> fileNameLineEdit -> setText(fileName);
        ui -> fileDownloadTextEdit -> setText( "当前选择：" + operationType_str + "\n" + "当前选择：" + fileType_str + "\n" + "当前文件：" + fileName);
    }
}


void FileView::on_operationTypeComboBox_activated(int index)
{
    QString operationType_str = ui -> operationTypeComboBox -> currentText();
    QString fileType_str = ui -> fileTypeComboBox -> currentText();
    ui -> fileDownloadTextEdit -> setText( "当前选择：" + operationType_str + "\n" + "当前选择：" + fileType_str + "\n" + "当前文件：" + fileName);
}


void FileView::on_fileTypeComboBox_activated(int index)
{
    QString operationType_str = ui -> operationTypeComboBox -> currentText();
    QString fileType_str = ui -> fileTypeComboBox -> currentText();
    ui -> fileDownloadTextEdit -> setText( "当前选择：" + operationType_str + "\n" + "当前选择：" + fileType_str + "\n" + "当前文件：" + fileName);
}


void FileView::on_fileDownloadButton_clicked()
{

}

