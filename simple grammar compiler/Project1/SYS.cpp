#include"SYS.h"
tList* thead = new tList;
tList* tnow = thead;
void SYS::OP(string s)//操作符语义动作
{
    quat temp; //四元式
    temp.op = s;  //传操作符
    temp.arg2 = sem.top();//传操作数
    if (!lookup(temp.arg2))//判断是否已定义2
       cout << "             *******************出现未定义警告:"<< temp.arg2<< "*******************" << endl;
    redefcheck(temp.arg2);//判断是否重定义
    sem.pop();//出栈
    temp.arg1 = sem.top();
    if (!lookup(temp.arg1))//判断是否已定义
       cout << "             *******************出现未定义警告:" << temp.arg1 << "*******************" << endl;
    redefcheck(temp.arg1);//判断是否重定义
    sem.pop();
    tList* tempx = addlist(tnow);//临时变量存储，为目标代码生成做准备
    temp.result = tempx->name;
    tnow = tempx;
    sem.push(temp.result);//将结果压入SEM栈
    qt.emplace_back(temp);//存入四元式数组，为输出四元式做准备
}

void SYS::ASSI()//赋值语句语义动作
{   
    quat temp;
    temp.op = "=";//给op赋=
    temp.arg1 = sem.top();
    lookup(temp.arg1);
    xieru(temp.arg1, in1);//没定义写入符号表
    sem.pop();
    temp.result = sem.top();
    sem.pop();//弹栈
    qt.emplace_back(temp);//将temp存入四元式数组
}

void SYS::IF()//if语义动作
{
    quat temp;
    temp.op = "if";
    temp.arg1 = sem.top();
    sem.pop();
    qt.emplace_back(temp);
}

void SYS::EL()//el语义动作
{
    quat temp;
    temp.op = "el";
    qt.emplace_back(temp);
}

void SYS::IE()//ie语义动作
{
    quat temp;
    temp.op = "ie";
    qt.emplace_back(temp);
}

void SYS::DO()//do语义动作
{
    quat temp;
    temp.op = "do";
    temp.arg1 = sem.top();
    sem.pop();
    qt.emplace_back(temp);
}

void SYS::WH()//wh语义动作
{
    quat temp;
    temp.op = "wh";
    qt.emplace_back(temp);
}

void SYS::WE()//we语义动作
{
    quat temp;
    temp.op = "we";
    qt.emplace_back(temp);
}

void SYS::PUSH(string s)//压入语义栈
{
    sem.push(s);
}

void SYS::pirnt_qt()
{
    cout << "              *******************中间代码为：********************" << endl;	
    system("pause");
    for (quat q : qt)
    {
        cout << "                          (" << q.op << "," << q.arg1 << "," << q.arg2 << "," << q.result << ")" << endl;
    }
    cout << endl;
}

void SYS::print_sem()//显示SEM栈顶
{
    cout << sem.top() << endl;
}