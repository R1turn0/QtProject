#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("testdata");
    db.setUserName("test");
    db.setPassword("test");

    if (db.open())
    {
        QMessageBox::information(this, "连接提示", "连接成功");

        m = new QSqlTableModel;
        m -> setTable("student");
        ui -> tableView -> setModel(m);

    }
    else
    {
        QMessageBox::information(this, "连接提示", "连接失败");
        this -> close();
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    m -> select();
}

