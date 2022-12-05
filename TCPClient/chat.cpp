#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
}


Chat::Chat(QTcpSocket* s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui -> setupUi(this);
    socket = s;
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_clearButton_clicked()
{
    ui -> lineEdit -> clear();
}


void Chat::on_sendButton_clicked()
{
    QByteArray ba;
    ba.append(ui -> lineEdit -> text());
    socket -> write(ba);
}

