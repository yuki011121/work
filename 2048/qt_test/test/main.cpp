#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;//
    w.setFixedSize(1000,1500);//设置窗口大小
    w.setWindowTitle("2048小游戏");//窗口标题
    w.show();

    return a.exec();
}
