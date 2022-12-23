#include "fileview.h"
#include "ui_fileview.h"

FileView::FileView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileView)
{
    ui->setupUi(this);
}

FileView::~FileView()
{
    delete ui;
}

void FileView::on_fileButtonBox_accepted()
{

}

