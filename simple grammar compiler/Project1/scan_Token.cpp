#include<iostream>
#include<cstdio>
#include<string>
#include <fstream>
#include <ctype.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include<vector>
#include"TOKEN.h"
#include"sym.h"
using namespace std;
string K[20] = { "int","void","break","float","while","do","struct",
"const","case","for","return","if","default","else","main" };
string P[20] = { "-","/","(",")","==","<=","<","+","*",">","=",",",
";","++","{","}" ,">=","!=" };
extern vector<string>I(100); //标识符表
extern vector<float>C(100);  //常数表
extern vector<int>C1(100);  //常整数表
extern vector<float>C2(100);//常实数表
int i = 0;//标识符个数
int c = 0;//常数个数
int p = 0;//整数数字个数
int l = 0;//小数数字个数
extern vector<pair<char, int> >Token;
extern symlist* head;//符号表头指针
extern symlist* now;
extern List* lhead;//常数表头指针
extern List* lnow;
extern unordered_map<string, symbollist*> map_total;
extern tList* thead;//临时表量表头指针
extern tList* tnow;
symbollist sym;
int lk(string n, ofstream& cy)//判断是否是关键字
{
	for (int j = 0; j <= 13; j++)
	{
		if (n == K[j]) {
			cy << n << "  :   " << "(K " << j + 1 << ")" << endl;//向文件写入
			Token.push_back(make_pair('K', j + 1));//连接到Token序列
			return 1;
		}
	}
	return 0;
}
int lp(string n, ofstream& cy)//是否是两个相连的界符
{
	for (int j = 0; j <= 17; j++)
	{
		if (n == P[j])
		{
			cy << n << "  :   " << "(P " << j + 1 << ")" << endl;
			Token.push_back(make_pair('P', j + 1));
			return 1;
		}

	}
	return 0;
}
int lpp(string n, ofstream& cy)//判断是否是单个界符
{
	for (int j = 0; j <= 17; j++)
	{
		if (n == P[j])
		{
			return 1;
		}
	}
	return 0;
}
void li(string n, ofstream& cy)//查填标识符表
{
	for (int j = 0; j <= i; j++)
	{
		if (n == I[j])
		{
			cy << n << "  :   " << "(I " << j + 1 << ")" << endl;
			Token.push_back(make_pair('I', j + 1));
			return;
		}
	}
	I[i] = n;
	i++;
	cy << n << "  :   " << "(I " << i << ")" << endl;//增添标识符
	Token.push_back(make_pair('I', i));
	return;
}
void lc(string n, ofstream& cy)//查填常数表
{
	string a, b = "";//a为小数点前整数部分，b为小数点后小数部分
	float m = 0;//转换
	int v = 0;
	string g;
	a = n.substr(0, 1);//将字符串n从0开始拷贝1个字符给a
	g = n.substr(v + 1, 1);//将字符串n从1开始拷贝1个字符给g
	while (g[0] >= '0' && g[0] <= '9')//如果是数字则继续读入
	{
		v++;
		a = n.substr(0, v + 1);
		g = n.substr(v + 1, 1);
	}
	if (g[0] == '.')//如果是小数点则将小数赋给b
	{
		b = n.substr(v + 2);
	}
	int j = a.length();//j为小数点前数字的长度
	int k = 0;
	for (int i = 0; i <= a.length() - 1; i++)
	{
		float u = a[i] - '0';
		for (int h = 0; h <= j - 2; h++)//常数处理器将字符串转换为数字
		{
			u = u * 10;
		}
		j--;
		m += u;
	}
	if (b == "")//无小数
	{
		C1[l] = m;
		l++;
		List* Ltemp;
		int inttemp = m;
		Ltemp = addlist(lnow, inttemp);//在常数表尾部插入常数
	}
	else if (b != "")
	{
		for (int i = 0; i <= b.length() - 1; i++)//常数处理器将字符串转换为数字
		{
			float o = b[i] - '0';
			for (int h = 0; h <= k; h++)
			{
				o = o / 10;
			}
			k++;
			m += o;
			List* Ltemp;
			Ltemp = addlist(lnow, m);
		}
		C2[p] = m;
		p++;

	}
	for (int j = 0; j <= c; j++)
	{
		if (m == C[j])
		{
			cy << m << "  :   " << "(C " << j + 1 << ")" << endl;
			Token.push_back(make_pair('C', j + 1));
			return;
		}
	}
	C[c] = m;
	c++;
	cy << m << "  :   " << "(C " << c << ")" << endl;
	Token.push_back(make_pair('C', j + 1));
	return;
}
void judge(string& a, ofstream& cy)//扫描，判断是标识符、界符、常数
{
	int v = 0;
	string m, g;
	m = a.substr(0, 1);//将读入字符型数字赋给m
	g = a.substr(v + 1, 1);
	if (m[0] == ' ')
		goto er;
	if (m[0] >= '0' && m[0] <= '9')
	{
		while (v < (a.length() - 1) && g[0] >= '0' && g[0] <= '9')
		{
			v++;
			m = a.substr(0, v + 1);
			g = a.substr(v + 1, 1);
		}
		if (g[0] == '.')
		{
			v++;
			m = a.substr(0, v + 1);
			g = a.substr(v + 1, 1);
			while (v < (a.length() - 1) && g[0] >= '0' && g[0] <= '9')
			{
				v++;
				m = a.substr(0, v + 1);
				g = a.substr(v + 1, 1);
			}
		}
		lc(m, cy);
		goto er;
	}
	if (lpp(m, cy) == 1)
	{
		if (lpp(g, cy) == 1)
		{
			v++;
			m = a.substr(0, v + 1);
		}
		if (lp(m, cy) == 0)
		{
			v--;
			m = a.substr(0, v + 1);
			int h = lp(m, cy);
			goto er;
		}
		else
			goto er;
	}
	while (v < (a.length() - 1) && lpp(g, cy) == 0 && g[0] != ' ')
	{
		v++;
		m = a.substr(0, v + 1);
		g = a.substr(v + 1, 1);
	}
	if (lk(m, cy) == 1)
		goto er;
	li(m, cy);
er:
	a = a.substr(v + 1);
}
void print_token()
{
	int n = Token.size();
	cout << "             ********************Token序列为:********************" << endl;
	system("pause");
	for (int k = 0; k < n; k++)
	{
		cout << "                    (" << Token[k].first << "," << Token[k].second << ")"<<endl;
	}
	cout << endl;
}
int Token_scan()
{
	cout << "             ********************词法分析阶段:********************" << endl;
	ifstream inf("shuru.txt");
	string a, line;
	while (!inf.eof()) {
		getline(inf, line);
		a += line;
	}
	//cout<<a;
	ofstream outf("Token.txt");
	while (a.length() != 0)
	{
		judge(a, outf);
	}
	print_token();
	return 0;
}
