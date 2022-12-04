#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    timer = new QTimer;
    picId = 2;

    // 加载图片的第二种方式
    QImage img;
    img.load(".\\Photo\\1.jpg");
    ui -> label -> setPixmap(QPixmap::fromImage(img));

    // 定时器时间到，发出timeout信号（谁发出信号，发出什么信号，谁来处理，怎么处理）
    connect(timer, &QTimer::timeout, this, &Widget::timeoutSlot);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startButton_clicked()
{
    timer -> start(TIMEOUT);
}


void Widget::on_singleButton_clicked()
{
    // 这个静态函数在一个给定时间间隔 msec(毫秒) 之后调用一个槽（时间，谁来处理，怎么处理）
    QTimer::singleShot(0, this, SLOT(timeoutSlot()));
}


void Widget::timeoutSlot()
{
    QString path(".\\Photo\\");
    path += QString::number(picId);
    path += ".jpg";

    QImage img;
    img.load(path);
    ui -> label -> setPixmap(QPixmap::fromImage(img));

    picId++;
    if (5 == picId)
    {
        picId = 1;
    }
}

void Widget::on_stopButton_clicked()
{
    timer->stop();
}
