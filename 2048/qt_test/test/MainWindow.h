#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QPushButton>
#include <QPainter>
#include <QTime>
#include <vector>
#include <QDebug> //用来 Debug
#include <QMessageBox>//自定义消息提示框
#include <QFrame>
#include <QTimer>
#include <QFile>

using namespace std;
namespace Ui
{
class MainWindow;
}
class tscore
{
public:
    struct fscore
    {
        int a[100];
        struct fscore *next;
    };
    struct fscore *head;
};


class Point
{
public:
    int i;
    int j;
    virtual void setnewscore();
    virtual ~Point(){}
};

class MainWindow : public QMainWindow,public Point
{
    Q_OBJECT
    friend class tscore;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);//alt+enter就可以自动补全

    void Up();
    void Down();
    void Left();
    void Right();
    void myRand();
    void setnewscore();
    void getmax();
    void findmax();
    void judge(int x);


    QPushButton *button;//按钮指针 #include <QPushButton>得有这个头文件
    QPushButton *button1;
    int s[4][4];
    int score=0;
    int maxscore=0;
    int step=0;
    int count=0;
    static int flag;
    struct tscore::fscore arr;

    bool state;//
public slots://初始化 槽函数
    void slotStart();
    void displaytime();
    void slothelp();
private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
