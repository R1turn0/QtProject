#include "widget.h"
#include "inc/d2c.h"
#include "inc/ss_error.h"

#include <QApplication>
#include <QDebug>

#define PIN_DEFAULT_INDEX       0
#define SLM_DEV_PASSWORD_LENGTH 16

int main(int argc, char *argv[])
{
    int ret = 0;
    static MASTER_HANDLE hmaster = NULL;
    char hmaster_pin[33] = {"12345678"};

    QApplication a(argc, argv);

    // 当最后一个可视窗口关闭时，不退出程序
//    a.setQuitOnLastWindowClosed(false);

    // 测试登陆状态
//    ret = master_open(&hmaster);
//    qDebug() << "master_open: " << ret;
//    ret = master_pin_verify(hmaster, PIN_DEFAULT_INDEX, (SS_BYTE*)hmaster_pin, strlen(hmaster_pin));
//    qDebug() << "master_pin_verify: " << ret;
//    if (SS_OK != ret)
//    {
//        master_close(hmaster);
//        return 1;
//    }

    Widget w;
    w.show();
    return a.exec();
}
