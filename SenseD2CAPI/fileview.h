#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class FileView;
}

class FileView : public QWidget
{
    Q_OBJECT

public:
    explicit FileView(QWidget *parent = nullptr);
    ~FileView();

private slots:
    void on_licenseButton_clicked();

    void on_fileNameToolButton_clicked();

    void on_cancelButton_clicked();

    void on_operationTypeComboBox_activated(int index);

    void on_fileTypeComboBox_activated(int index);

    void on_fileDownloadButton_clicked();

private:
    Ui::FileView *ui;
    QString fileName;
};

#endif // FILEVIEW_H
