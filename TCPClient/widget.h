#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <chat.h>

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
    void on_connectButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket* socket;
};
#endif // WIDGET_H
