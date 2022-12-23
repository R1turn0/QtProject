#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <fileview.h>
#include <licenseview.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_fileButton_clicked();

    void on_licenseButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
