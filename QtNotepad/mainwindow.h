#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* key);
//    void mousePressEvent(QMouseEvent* mouse);
    void closeEvent(QCloseEvent* quit_ptr);

private slots:
    void newActionSlot();
    void openActionSlot();
    void saveActionSlot();
    void saveAsActionSlot();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    QString fileName;
    bool isSave;
};
#endif // MAINWINDOW_H
