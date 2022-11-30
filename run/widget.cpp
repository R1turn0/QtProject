#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 连接信号与槽（谁发信号，发出什么信号，谁处理信号，怎么处理）
    connect(ui -> cmdLineEdit, SIGNAL(returnPressed()), this, SLOT(on_commitButton_clicked()));
    // 通过地址处理
    connect(ui -> cancelButton, &QPushButton::clicked, this, &Widget::on_cancelButton_clicked);
    // 通过QMessageBox处理
    connect(ui -> browseButton, &QPushButton::clicked, [this]()
    {
        QMessageBox::information(this, "信息", "点击浏览");
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_commitButton_clicked()
{
    // 获取LineEdit数据
    QString program = ui -> cmdLineEdit -> text();
    // 创建process对象
    QProcess* myProcess = new QProcess(this);
    myProcess -> start(program);
}

void Widget::on_cancelButton_clicked()
{
    this -> close();
}
