#include "licenseview.h"
#include "ui_licenseview.h"

LicenseView::LicenseView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LicenseView)
{
    ui->setupUi(this);
}

LicenseView::~LicenseView()
{
    delete ui;
}
