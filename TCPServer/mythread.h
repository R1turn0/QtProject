#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class myThread : public QThread
{
    // 必须加上Q_OBJECT否则无法使用槽
    Q_OBJECT
public:
    explicit myThread(QTcpSocket* s);
    void run();     // 线程处理函数

signals:
    void sendToWidget(QByteArray);

public slots:
    void clientInfoSlot();

private:
    QTcpSocket* socket;

};

#endif // MYTHREAD_H
