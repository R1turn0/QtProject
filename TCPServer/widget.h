#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <mythread.h>

#define PORT 8000

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void newClientHandler();
//    void clientInfoSlot();
    void threadSlot(QByteArray);

private slots:
    void on_cancelButton_clicked();

private:
    Ui::Widget *ui;
    QTcpServer* server;
};
#endif // WIDGET_H
