#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this -> setWindowTitle("新建文本文档.txt");
    fileName = "新建文本文档.txt";
    isSave = true;

    connect(ui -> newAction, &QAction::triggered, this, &MainWindow::newActionSlot);
    connect(ui -> openAction, &QAction::triggered, this, &MainWindow::openActionSlot);
    connect(ui -> saveAction, &QAction::triggered, this, &::MainWindow::saveActionSlot);
    connect(ui -> saveAsAction, &QAction::triggered, this, &MainWindow::saveAsActionSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::newActionSlot()
{
    ui -> textEdit -> clear();
    this -> setWindowTitle("新建文本文档.txt");
    fileName = "0";
    isSave = true;
}


void MainWindow::openActionSlot()
{
    fileName = QFileDialog::getOpenFileName(
                this, tr("选择TxT文件"), QCoreApplication::applicationFilePath(),
                tr("Normal text file(*.txt)"));
    if (fileName.isEmpty())
    {
        //QMessageBox::warning(this, "警告", "请选择一个文件");
    }
    else
    {
        this -> setWindowTitle(fileName);
        //qDebug() << fileName;
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        QByteArray ba = file.readAll();
        ui -> textEdit -> setText(QString(ba));
        isSave = true;
        file.close();
    }
}


void MainWindow::saveActionSlot()
{
    this -> setWindowTitle(fileName);
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QByteArray ba;
    ba.append(ui -> textEdit -> toPlainText());
    file.write(ba);
    file.close();
    isSave = true;
}


void MainWindow::saveAsActionSlot()
{
    fileName = QFileDialog::getSaveFileName(
                this, "选择TxT文件", QCoreApplication::applicationFilePath());
    if (fileName.isEmpty())
    {
        //QMessageBox::warning(this, "警告", "请选择一个文件");
    }
    else
    {
        this -> setWindowTitle(fileName);
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QByteArray ba;
        ba.append(ui -> textEdit -> toPlainText());
        file.write(ba);
        file.close();
        isSave = true;
    }
}


// 注意大小写
void MainWindow::keyPressEvent(QKeyEvent* key)
{
    if (key == nullptr)
    {
        return;
    }
    if ((key -> modifiers() == Qt::ControlModifier) &&
            (key -> key() == Qt::Key_S))
    {
        if (fileName != "0")
            saveActionSlot();
        else
            saveAsActionSlot();
    }
}


// 检测鼠标事件
//void MainWindow::mousePressEvent(QMouseEvent* mouse)
//{
//    QPoint pt = mouse -> pos();
//    qDebug() << pt;

//    if (mouse -> button() == Qt::LeftButton)
//    {
//        qDebug() << "左键被按下";
//    }
//    else if (mouse -> button() == Qt::RightButton)
//    {
//        qDebug() << "右键被按下";
//    }
//}


void MainWindow::on_textEdit_textChanged()
{
    isSave = false;
    this -> setWindowTitle(fileName + "*");
}


void MainWindow::closeEvent(QCloseEvent* quit_ptr)
{
//    if (QMessageBox::question(this, tr("退出"), tr("是否退出？"),
//          QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
//        quit_ptr -> accept();
//    else
//        quit_ptr -> ignore();
    if (isSave == false)
    {
        int ret = QMessageBox::question(this, tr("保存"), tr("是否保存？"), QMessageBox::Yes | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Yes)
        {
            if (fileName == "新建文本文档.txt")
                saveAsActionSlot();
            else
                saveActionSlot();
            quit_ptr -> accept();
        }
        else if (ret == QMessageBox::Discard)
            quit_ptr -> accept();
        else
            quit_ptr -> ignore();
    }
}

