#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    picId = 2;

    QPixmap pix(".\\Photo\\1.jpg");
    ui -> label -> setPixmap(pix);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startButton_clicked()
{
    // 开启定时器，返回定时器编号
    myTimerId = this -> startTimer(TIMEOUT);
}


void Widget::timerEvent(QTimerEvent* event)
{
    if (event -> timerId() != myTimerId)
        return;

    QString path(".\\Photo\\");
    path += QString::number(picId);
    path += ".jpg";

    QPixmap pix(path);
    ui -> label -> setPixmap(pix);

    picId++;
    if (5 == picId)
    {
        picId = 1;
    }
}

void Widget::on_stopButton_clicked()
{
    this -> killTimer(myTimerId);
}

