#include "MainWindow.h"
#include "ui_MainWindow.h"
int MainWindow::flag=0;

MainWindow::MainWindow(QWidget *parent) ://构造函数
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer* timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(displaytime()));
    timer->start(1000); //刷新1s1次
    for(int i=0;i<4;i++)//初始化
    {
        for(int j=0;j<4;j++)
        {
            s[i][j]=0;
        }
    }
    button = new QPushButton("开始游戏",this); //开始游戏的按钮
    button->setGeometry(330,800,330,85);//xy坐标从(330,800)做一个330*85的按钮
    QPushButton *button1;
    button1 = new QPushButton("帮助",this); //按钮
    button1->setGeometry(750,800,175,85);//



    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));//随机种子函数#include <QTime>

    connect(button,SIGNAL(clicked()),this,SLOT(slotStart()));//槽与信号 点击
    connect(button1,SIGNAL(clicked()),this,SLOT(slothelp()));//槽与信号 点击
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::displaytime()
{

    count++;


}

void MainWindow::slothelp()
{
    QMessageBox::about(this,"帮助","\n\t手指向一个方向滑动，所有格子会向那个方向运动。相同数字的两个格子，相撞时数字会相加。每次滑动时，空白处会随机刷新出一个数字的格子。\t\n\n");//#include <QMessageBox>
}

void MainWindow::paintEvent(QPaintEvent *)//#include <QPainter>
{
    QPainter p(this);

    QPixmap pixmap(":/back.jpeg");
    p.drawPixmap(0,0,1000,1500,pixmap);

    p.setBrush(Qt::blue);
    p.setFont(QFont("微软雅黑",25,600,false));//600是字体粗细

    QString str;//string类
    p.drawText(QPoint(40,80),"分数: "+QString::number(score));//显示分数
    p.drawText(QPoint(370,80),"步数: "+QString::number(step));
    p.drawText(QPoint(650,80),"所用时间: "+QString::number(count)+"s");

    for (int i=0;i<4;i++)//格子的实现
    {
        for (int j=0;j<4;j++)
        {
            p.setPen(Qt::transparent);//?
            if(s[i][j]==0)
            {
                p.setBrush(QBrush(QColor(204,202,202,80)));
                p.drawRect(i*120+250,j*120+180,110,110);//每个方块110*110，原来坐标（250,180）后面都移动120 空10
            }
            else if (s[i][j]==2)
            {
                p.setBrush(QColor("#FAEBD7"));//setBrush(Qt::red);
                p.drawRect(i*120+250,j*120+180,110,110);
                p.setPen(QColor("#696969"));//(Qt::darkGray);
                p.setFont(QFont("Arial Black",15,700,false));
                //在方块中 绘制Text， 并且文本位置位于中部
                p.drawText(QRectF(i*120+250,j*120+180,110,110),QString::number(2),QTextOption(Qt::AlignCenter));
            }
            else if (s[i][j]==4)
            {
                p.setBrush(QColor("#FFE4C4"));//(Qt::darkRed);
                p.drawRect(i*120+250,j*120+180,110,110);
                p.setPen(QColor("#696969"));//p.setPen(Qt::darkGray);
                p.setFont(QFont("Arial Black",15,700,false));
                p.drawText(QRectF(i*120+250,j*120+180,110,110),QString::number(4),QTextOption(Qt::AlignCenter));
            }
            else if (s[i][j]==8)
            {
                p.setBrush(QColor("#DEB887"));//(Qt::green);
                p.drawRect(i*120+250,j*120+180,110,110);
                p.setPen(Qt::white);
                p.setFont(QFont("Arial Black",15,700,false));
                p.drawText(QRectF(i*120+250,j*120+180,110,110),QString::number(8),QTextOption(Qt::AlignCenter));
            }
            else if (s[i][j]==16)
            {
                p.setBrush(QColor("#FFA500"));//p.setBrush(Qt::darkGreen);
                p.drawRect(i*120+250,j*120+180,110,110);
                p.setPen(Qt::white);
                p.setFont(QFont("Arial Black",15,700,false));
                p.drawText(QRectF(i*120+250,j*120+180,110,110),QString::number(16),QTextOption(Qt::AlignCenter));
            }
            else if (s[i][j]==32)
            {
                p.setBrush(QColor("#FF7F50"));//p.setBrush(Qt::yellow);
                p.drawRect(i*120+250,j*120+180,110,110);
                p.setPen(Qt::white);
                p.setFont(QFont("Arial Black",15,700,false));
                p.drawText(QRectF(i*120+250,j*120+180,110,110),QString::number(32),QTextOption(Qt::AlignCenter));
            }
            else if (s[i][j]==64)
            {
                p.setBrush(QColor("#FF0000"));//p.setBrush(Qt::darkYellow);
                p.drawRect(i*120+250,j*120+180,110,110);
                p.setPen(Qt::white);
                p.setFont(QFont("Arial Black",15,700,false));
                p.drawText(QRectF(i*120+250,j*120+180,110,110),QString::number(64),QTextOption(Qt::AlignCenter));
            }
            else if (s[i][j]==128)
            {
                p.setBrush(QColor("#F0E68C"));//p.setBrush(Qt::cyan);
                p.drawRect(i*120+250,j*120+180,110,110);
                p.setPen(Qt::white);
                p.setFont(QFont("Arial Black",15,700,false));
                p.drawText(QRectF(i*120+250,j*120+180,110,110),QString::number(128),QTextOption(Qt::AlignCenter));
            }
            else if (s[i][j]==256)
            {
                p.setBrush(QColor("#FFD700"));//p.setBrush(Qt::darkCyan);
                p.drawRect(i*120+250,j*120+180,110,110);
                p.setPen(Qt::white);
                p.setFont(QFont("Arial Black",15,700,false));
                p.drawText(QRectF(i*120+250,j*120+180,110,110),QString::number(256),QTextOption(Qt::AlignCenter));
            }
            else if (s[i][j]==512)
            {
                p.setBrush(QColor("#DAA520"));//p.setBrush(Qt::magenta);
                p.drawRect(i*120+250,j*120+180,110,110);
                p.setPen(Qt::white);
                p.setFont(QFont("Arial Black",15,700,false));
                p.drawText(QRectF(i*120+250,j*120+180,110,110),QString::number(512),QTextOption(Qt::AlignCenter));
            }
            else if (s[i][j]==1024)
            {
                p.setBrush(QColor("#FFA07A"));//p.setBrush(Qt::darkMagenta);
                p.drawRect(i*120+250,j*120+180,110,110);
                p.setPen(Qt::white);
                p.setFont(QFont("Arial Black",15,700,false));
                p.drawText(QRectF(i*120+250,j*120+180,110,110),QString::number(1024),QTextOption(Qt::AlignCenter));
            }
            else if (s[i][j]==2048)
            {
                p.setBrush(QColor("#F08080"));//p.setBrush(Qt::blue);
                p.drawRect(i*120+250,j*120+180,110,110);
                p.setPen(Qt::white);
                p.setFont(QFont("Arial Black",15,700,false));
                p.drawText(QRectF(i*120+250,j*120+180,110,110),QString::number(2048),QTextOption(Qt::AlignCenter));
            }
            else
            {
                p.setBrush(QColor("#CD5C5C"));//p.setBrush(Qt::darkBlue);
                p.drawRect(i*120+250,j*120+180,110,110);
                p.setPen(Qt::black);
                p.setFont(QFont("Arial Black",15,700,false));
                p.drawText(QRectF(i*120+250,j*120+180,110,110),QString::number(s[i][j]),QTextOption(Qt::AlignCenter));
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!state)//判断游戏状态 bool型
    {
        return ;
    }
        switch (event->key())//读取键盘操作#include <QKeyEvent>
        {
        case Qt::Key_W:
            Up();
            step++;
            break;

        case Qt::Key_S:
            Down();
            step++;
            break;

        case Qt::Key_A:
            Left();
            step++;
            break;

        case Qt::Key_D:
            Right();
            step++;
            break;

        default:
            return;//忽略其他按钮
        }
        myRand();//随机函数 首先检测有没有空的格子有就生成一个2没有判断游戏是否结束
        update();//强制界面刷新
}
void MainWindow::slotStart()//游戏开始或者重新开始的函数
{

    QMessageBox::about(this,"游戏规则","\n\n\t  WSAD控制方块上下左右移动\t\t\n\n");//#include <QMessageBox>
    score=0;
    step=0;
    count=0;
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            s[i][j]=0;
        }
    }
    button->setText("重新游戏");

    int randi=qrand()%4;//随机生成0~4的数
    int randj=qrand()%4;
    s[randi][randj]=2;

    state=true;

    update();
}
void MainWindow::Up()
{
    //移动
    for (int i=0;i<4;i++)
    {
        for (int j=1;j<4;j++)
        {
            if(s[i][j]==0)continue;
            for (int p=0;p<j;p++)
            {
                //查看前面是否有空格子可移动
                if(s[i][p]==0)
                {
                    s[i][p]=s[i][j];
                    s[i][j]=0;
                    break;
                }
            }
        }
    }
    //相加
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<3;j++)
        {
            if(s[i][j]==s[i][j+1])
            {
                s[i][j]=2*s[i][j];
                s[i][j+1]=0;
                score+=s[i][j];
                for (int p=j+2;p<4;p++)
                {
                    s[i][p-1]=s[i][p];
                }
            }
        }
    }
}
void MainWindow::Down()
{
    //移动
    for (int i=0;i<4;i++)
    {
        for (int j=2;j>=0;j--)
        {
            if(s[i][j]==0)continue;
            for (int p=3;p>j;p--)
            {
                //查看前面是否有空格子可移动
                if(s[i][p]==0)
                {
                    s[i][p]=s[i][j];
                    s[i][j]=0;
                    break;
                }
            }
        }
    }
    //相加
    for (int i=0;i<4;i++)
    {
        for (int j=3;j>0;j--)
        {
            if(s[i][j]==s[i][j-1])
            {
                s[i][j]=2*s[i][j];
                s[i][j-1]=0;
                score+=s[i][j];
                for (int p=j-2;p>=0;p--)
                {
                    s[i][p+1]=s[i][p];
                }
            }
        }
    }
}
void MainWindow::Left()
{
    //移动
    for (int j=0;j<4;j++)
    {
        for (int i=1;i<4;i++)
        {
            if(s[i][j]==0)
            {
                continue;
            }
            for (int p=0;p<i;p++)
            {
                //查看前面是否有空格可移入
                if(s[p][j] == 0)
                {
                    s[p][j] = s[i][j];
                    s[i][j] = 0;
                    break;
                }
            }
        }
    }
    //相加
    for (int j=0;j<4;j++)
    {
        for (int i=0;i<3;i++)
        {
            if(s[i][j]==s[i+1][j])
            {
                s[i][j]=s[i][j]*2;
                score+=s[i][j];
                s[i+1][j]=0;
                for(int p=i+2;p<4;p++)
                {
                    s[p-1][j] = s[p][j];
               }
            }
        }
    }
}
void MainWindow::Right()
{
    //移动
    for (int j=0;j<4;j++)
    {
        for (int i=2;i>=0;i--)
        {
            if(s[i][j]==0)
            {
                continue;
            }
            for (int p=3;p>i;p--)
            {
                //查看前面是否有空格可移入
                if(s[p][j] == 0)
                {
                    s[p][j] = s[i][j];
                    s[i][j] = 0;
                    break;
                }
            }
        }
    }
    //相加
    for (int j=0;j<4;j++)
    {
        for (int i=3;i>=0;i--)
        {
            if(s[i][j]==s[i-1][j])
            {
                s[i][j]=s[i][j]*2;
                s[i-1][j]=0;
                score+=s[i][j];
                for(int p=i-2;p>=0;p--)
                {
                    s[p+1][j] = s[p][j];
                }
            }
        }
    }
}
void MainWindow::myRand()//理解
  {
    int i=0,j=0;
    //找出格子
    Point  n[16];
    int ni=0;//几个空格子
    for (i=0;i<4;i++)
    {
        for (j=0;j<4;j++)
        {
            if(s[i][j]==0)
            {
                n[ni].i=i;
                n[ni].j=j;
                ni++;
            }
        }
    }

    //判断游戏是否结束
    if (ni==0)
    {
        for (i=0;i<4;i++)//上下有没有相同的
        {
            for (j=0;j<3;j++)
            {
                if(s[i][j]==s[i][j+1])
                {
                    return;
                }
            }
        }
        for (j=0;j<4;j++)//左右有没有相同的
        {
            for (i=0;i<3;i++)
            {
                if(s[i][j]==s[i+1][j])
                {
                    return;
                }
            }
        }
       try
        {
            int i=score;
            judge(i);
        }
        catch(int e)
           {QMessageBox::about(this,"异常","\n\n\t程序异常\n\t\t\n\n");}

        QMessageBox::about(this,"游戏结束","\n\n\t 您的最终分数为："+QString::number(score)+" \t\t\n\n");
        arr.a[flag]=score;
        flag++;
        //findmax();
        //如果刷新最高分；
        Point* pi;
        getmax();
        if(score>maxscore)
        {
            maxscore=score;
            pi=this;
            pi->setnewscore();
            QFile file("score.txt");
            file.open(QIODevice::WriteOnly);
            file.close();
            if (file.open(QIODevice::ReadWrite | QIODevice::Text))
            {
                  QTextStream stream(&file);
                  stream.seek(file.size());
                  stream << score << "\n";
                  file.close();
            }

        }


        return;
    }
    int rand=qrand()%ni;//范围在0~ni里面
    s[n[rand].i][n[rand].j]=2;
}
void MainWindow::setnewscore()
{
    QMessageBox::about(this,"最高分更新","\n\n\t恭喜你刷新最高纪录！\t\t\n\t最高分为："+QString::number(score)+" \t\t\n\n");
}

void MainWindow::getmax()
{
    FILE *pf=fopen("score.txt","rw");
    QFile file;
    file.open(pf,QIODevice::ReadWrite);
    if(pf==nullptr)
        file.write("0\n");
    else
    {
        QByteArray line = file.readLine();
        QString str(line);
        maxscore = str.toInt();
    }
    file.close();
}

void MainWindow::findmax()
{
    struct  tscore::fscore* head;
    head=(tscore::fscore*)malloc(sizeof(tscore::fscore));
    head ->next=nullptr;
    tscore::fscore *p=head;
    if (p!=nullptr)
        while(p)
        {
            if(p->a[i]<(p->next)->a[i+1])
            {
                maxscore=(p->next)->a[i+1];
            }
            p=p->next;
            i++;
        }
}

void MainWindow::judge(int x)
{
    if(x==0)
      throw x;
}


//"<font size='10' color='black'>\n\n\t分数为："+QString::number(score)+" \t\t\n\n"
//QPixmap pix;
//pix.load("");
//p.drawPixmap(0,0,this->width(),this->height(),pix);

void Point::setnewscore()
{
   // QMessageBox::about(this,"最高分更新","\n\n\t 恭喜你刷新最高纪录！\n\t 最高分为："+QString::number(score)+" \t\t\n\n");
}
/*int tscore::rank(int x){    arr[arr.size()]=x;
    for(int i=0;i<arr.size();i++){
        if(arr[i]<arr[i+1]){
            int t=arr[i];
            arr[i]=arr[i+1];
            arr[i+1]=t;
        }
    }
    for (int i=0;i<arr.size();i++) {
        if(x==arr[i])
            return i;
    }
}
*/
