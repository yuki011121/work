#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "sym.h"
#include"SemAnalysis.h"
using namespace std;
typedef struct quat//四元式结构体
{
    string op;//操作符
    string arg1, arg2;//操作数
    string result;//结果
}quat;

class SYS
{
private:
    stack<string> sem;//语义

public:
    vector<quat> qt;//四元式类型数组
    void OP(string s);//操作符语义动作
    void ASSI();//赋值语句语义动作
    void IF();//if语义动作
    void EL();//el语义动作
    void IE();//ie语义动作
    void DO();//do语义动作
    void WH();//wh语义动作
    void WE();//we语义动作
    void PUSH(string s);//压入语义作
    void pirnt_qt();
    void print_sem();
};
