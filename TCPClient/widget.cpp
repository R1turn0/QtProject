#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 创建Socket对象
    socket = new QTcpSocket;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_cancelButton_clicked()
{
    this -> close();
}


void Widget::on_connectButton_clicked()
{
    // 获取ip地址和端口号
    QString ip = ui -> ipLineEdit -> text();
    QString port = ui -> portLineEdit -> text();

    qDebug() << ip << ":" << port;

    // 向服务器发起连接
    socket -> connectToHost(QHostAddress(ip), port.toShort());

    // 链接服务器成功，socket对象会发出信号
    connect(socket, &QTcpSocket::connected, [this]()
    {
        QMessageBox::information(this, "连接成功", "连接服务器成功");

        // 隐藏界面
        this -> hide();
        // 在堆空间创建对象
        Chat* c = new Chat(socket);
        c -> show();
    });

    // 链接服务器异常，socket对象会发出信号
    connect(socket, &QTcpSocket::disconnected, [this]()
    {
        QMessageBox::warning(this, tr("链接提示"), tr("连接异常"));
    });
}

