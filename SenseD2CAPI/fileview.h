#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QWidget>

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

    void on_fileButtonBox_accepted();

private:
    Ui::FileView *ui;
};

#endif // FILEVIEW_H
