#include "SemAnalysis.h"
vector<pair<char, int>> token;
extern symlist* head;
extern symlist* now;
symlist* tail = now;
extern unordered_map<string, symbollist*> map_total;
int err=0;
int q=0;
int offsetx = 0;
//语义分析 
void xieru(string m, typex ty)      //若未定义则填写符号表 
{
	symlist* temp = map_total[m];
	if (temp == NULL) return;
	if (temp->n == 0)  //n：定义次数
	{
		temp->n = 1;  
		temp->typ = ty;
		temp->cat = v;
		temp->offset = offsetx;
		offsetx += 4;
	}
	if (temp->n == 1)  
	{
		cout << "             *******************出现重复定义警告:"<<temp->name << "*******************" << endl;   //n=1：重复定义
	}
}
void redefcheck(string m) {
	symlist* temp;
	int i = 0;
	temp = head;
	if (m[0] == 't') return ;  //为临时变量或数字就不填表
	if (m[0] <= '9' && m[0] >= '0') return ;//为临时变量或数字就不填表
	while (temp != NULL)
	{
		if (m == temp->name)  //重名记录重名次数
		{
			i ++;
		}
		if (i > 1)
		{
			cout << "             *******************出现重复定义警告:" << temp->name << "*******************" << endl; //提示重名
			return;
		}
		temp = temp->next;
	}
}
int lookup(string m)//检查变量是否已经定义 
{
	symlist* temp;
	if (m[0] == 't') return 1;
	if (m[0] <= '9' && m[0] >= '0') return 1;
	int i = 0;
	temp = head;
	while (temp != NULL)
	{
		if (m == temp->name)  
		{
			i = 1;
			break;
		}
		temp = temp->next;
	}
	return i; //返回i，在sys里检查重名
}

void outdaima(vector<quat> &qt)//目标代码输出
{
	int n = 0;
	if (err == 0)//语法分析无错误进入
	{
		cout << endl;
		//system("pause");
		cout << endl;
		cout << "             *******************目标代码为："<<"*******************";
		cout << endl;
		system("pause");
		int m = qt.size();//m为四元式数量
		for (int i = 0; i < m; i++)//对每个四元式进行输出目标代码指令
		{
			if (qt[i].op == "+")
			{
				cout << "                             " << n++ << ":" << "LD" << " " << "R" << "," << qt[i].arg1 << endl;
				cout << "                             " << n++ << ":" << "ADD" << " " << "R" << "," << qt[i].arg2 << endl;
				cout << "                             " << n++ << ":" << "MOV" << " " << qt[i].result << "," << "R" << endl;
			}
			if (qt[i].op == "*")
			{
				cout << "                             " << n++ << ":" << "MOV" << " " << "R" << "," << qt[i].arg1 << endl;
				cout << "                             " << n++ << ":" << "MUL" << " " << "R" << "," << qt[i].arg2 << endl;
				cout << "                             " << n++ << ":" << "ST" << " " << "R" << "," << qt[i].result << endl;
			}
			if (qt[i].op == "-")
			{
				cout << "                             " << n++ << ":" << "LD" << " " << "R" << "," << qt[i].arg1 << endl;
				cout << "                             " << n++ << ":" << "SUB" << " " << "R" << "," << qt[i].arg2 << endl;
				cout << "                             " << n++ << ":" << "MOV" << " " << qt[i].result << "," << "R" << endl;
			}
			if (qt[i].op == "/")
			{
				cout << "                             " << n++ << ":" << "MOV" << " " << "R" << "," << qt[i].arg1 << endl;
				cout << "                             " << n++ << ":" << "DIV" << " " << "R" << "," << qt[i].arg2 << endl;
				cout << "                             " << n++ << ":" << "ST" << " " << "R" << "," << qt[i].result << endl;
			}
			if (qt[i].op == "=")
			{
				cout << "                             " << n++ << ":" << "MOV" << " " << "R" << "," << qt[i].arg1 << endl;
				cout << "                             " << n++ << ":" << "ST" << " " << "R" << "," << qt[i].result << endl;
			}
			if (qt[i].op == ">")
			{
				cout << "                             " << n++ << ":" << "LD" << " " << "R" << "," << qt[i].arg1 << endl;
				cout << "                             " << n++ << ":" << "GT" << " " << "R" << "," << qt[i].arg2 << endl;
			}
			if (qt[i].op == "<")
			{
				cout << "                             " << n++ << ":" << "LD" << " " << "R" << "," << qt[i].arg1 << endl;
				cout << "                             " << n++ << ":" << "LT" << " " << "R" << "," << qt[i].arg2 << endl;
			}
			if (qt[i].op == ">=")
			{
				cout << "                             " << n++ << ":" << "LD" << " " << "R" << "," << qt[i].arg1 << endl;
				cout << "                             " << n++ << ":" << "GE" << " " << "R" << "," << qt[i].arg2 << endl;
			}
			if (qt[i].op == "<=")
			{
				cout << "                             " << n++ << ":" << "LD" << " " << "R" << "," << qt[i].arg1 << endl;
				cout << "                             " << n++ << ":" << "LE" << " " << "R" << "," << qt[i].arg2 << endl;
			}
			if (qt[i].op == "if")
			{
				cout <<"                             " << n++ << ":" << "FJ" << " " << "R" << "," << "?" << endl;
			}
			if (qt[i].op == "el")
			{
				cout << "                             " << n++ << ":" << "JMP" << " " << "?" << endl;
				cout << "                             " << "if?:" << n + 1 << endl;
			}
			if (qt[i].op == "ie")
			{
				cout << "                             " << "el?:" << n + 1 << endl;
			}
			if (qt[i].op == "wh")
			{
				q = n + 1;
			}
			if (qt[i].op == "do")
			{
				cout << "                             " << n++ << ":" << "FJ" << " " << "R" << "," << "?" << endl;
			}
			if (qt[i].op == "we")
			{
				cout << "                             " << n++ << ":" << "JMP" << " " << q << endl;
				cout << "                             " << "?:" << n + 1 << endl;
				q = 0;
			}
		}
	}
}
