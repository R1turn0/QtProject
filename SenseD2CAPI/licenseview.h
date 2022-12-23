#ifndef LICENSEVIEW_H
#define LICENSEVIEW_H

#include <QWidget>

namespace Ui {
class LicenseView;
}

class LicenseView : public QWidget
{
    Q_OBJECT

public:
    explicit LicenseView(QWidget *parent = nullptr);
    ~LicenseView();

private slots:
    void on_fileButton_clicked();

private:
    Ui::LicenseView *ui;
};

#endif // LICENSEVIEW_H
