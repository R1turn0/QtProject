#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_fileButton_clicked()
{
    this -> hide();
    FileView* F = new FileView();
    F -> show();
}


void Widget::on_licenseButton_clicked()
{
    this -> hide();
    LicenseView* L = new LicenseView();
    L -> show();
}


void LicenseView::on_fileButton_clicked()
{
    this -> close();
    FileView* F = new FileView();
    F -> show();
}


void FileView::on_licenseButton_clicked()
{
    this -> close();
    LicenseView* L = new LicenseView();
    L -> show();
}


void FileView::on_cancelButton_clicked()
{
    this -> close();
    Widget* W = new Widget;
    W -> show();
}


void LicenseView::on_cancelButton_clicked()
{
    this -> close();
    Widget* W = new Widget;
    W -> show();
}


