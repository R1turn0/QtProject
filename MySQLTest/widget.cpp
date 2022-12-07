#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 加载MySQL数据库驱动
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("qt_project");
    db.setUserName("root");
    db.setPassword("root");
    if (db.open())
    {
        QMessageBox::information(this, "连接提示", "success:连接成功！");
    }
    else
    {
        QMessageBox::information(this, "连接提示", "error:连接失败！");
        this -> close();
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_insertPushButton_clicked()
{
    QString id = ui -> idLineEdit -> text();
    QString name = ui -> nameLineEdit -> text();
    QString birth = ui -> birLineEdit -> text();
    // INSERT INTO qt_project.student (id, name, birth) VALUES (1, 'AzusaFish', '20000213')
    QString sql = QString("INSERT INTO qt_project.student (id, name, birth) VALUES (%1, '%2', '%3');")\
            .arg(id).arg(name).arg(birth);
    QSqlQuery query;
    if (query.exec(sql))
    {
        QMessageBox::information(this, "插入提示", "插入成功");
    }
    else
    {
        QMessageBox::information(this, "插入提示", "插入失败");
    }
}


void Widget::on_findPushButton_clicked()
{
    QSqlQuery query;
    query.exec("select * from student;");
    while (query.next())
    {
        qDebug() << query.value(0);
        qDebug() << query.value(1);
        qDebug() << query.value(2);
    }
}

