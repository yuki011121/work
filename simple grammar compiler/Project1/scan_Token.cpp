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
extern vector<string>I(100); //��ʶ����
extern vector<float>C(100);  //������
extern vector<int>C1(100);  //��������
extern vector<float>C2(100);//��ʵ����
int i = 0;//��ʶ������
int c = 0;//��������
int p = 0;//�������ָ���
int l = 0;//С�����ָ���
extern vector<pair<char, int> >Token;
extern symlist* head;//���ű�ͷָ��
extern symlist* now;
extern List* lhead;//������ͷָ��
extern List* lnow;
extern unordered_map<string, symbollist*> map_total;
extern tList* thead;//��ʱ������ͷָ��
extern tList* tnow;
symbollist sym;
int lk(string n, ofstream& cy)//�ж��Ƿ��ǹؼ���
{
	for (int j = 0; j <= 13; j++)
	{
		if (n == K[j]) {
			cy << n << "  :   " << "(K " << j + 1 << ")" << endl;//���ļ�д��
			Token.push_back(make_pair('K', j + 1));//���ӵ�Token����
			return 1;
		}
	}
	return 0;
}
int lp(string n, ofstream& cy)//�Ƿ������������Ľ��
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
int lpp(string n, ofstream& cy)//�ж��Ƿ��ǵ������
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
void li(string n, ofstream& cy)//�����ʶ����
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
	cy << n << "  :   " << "(I " << i << ")" << endl;//�����ʶ��
	Token.push_back(make_pair('I', i));
	return;
}
void lc(string n, ofstream& cy)//�������
{
	string a, b = "";//aΪС����ǰ�������֣�bΪС�����С������
	float m = 0;//ת��
	int v = 0;
	string g;
	a = n.substr(0, 1);//���ַ���n��0��ʼ����1���ַ���a
	g = n.substr(v + 1, 1);//���ַ���n��1��ʼ����1���ַ���g
	while (g[0] >= '0' && g[0] <= '9')//������������������
	{
		v++;
		a = n.substr(0, v + 1);
		g = n.substr(v + 1, 1);
	}
	if (g[0] == '.')//�����С������С������b
	{
		b = n.substr(v + 2);
	}
	int j = a.length();//jΪС����ǰ���ֵĳ���
	int k = 0;
	for (int i = 0; i <= a.length() - 1; i++)
	{
		float u = a[i] - '0';
		for (int h = 0; h <= j - 2; h++)//�������������ַ���ת��Ϊ����
		{
			u = u * 10;
		}
		j--;
		m += u;
	}
	if (b == "")//��С��
	{
		C1[l] = m;
		l++;
		List* Ltemp;
		int inttemp = m;
		Ltemp = addlist(lnow, inttemp);//�ڳ�����β�����볣��
	}
	else if (b != "")
	{
		for (int i = 0; i <= b.length() - 1; i++)//�������������ַ���ת��Ϊ����
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
void judge(string& a, ofstream& cy)//ɨ�裬�ж��Ǳ�ʶ�������������
{
	int v = 0;
	string m, g;
	m = a.substr(0, 1);//�������ַ������ָ���m
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
	cout << "             ********************Token����Ϊ:********************" << endl;
	system("pause");
	for (int k = 0; k < n; k++)
	{
		cout << "                    (" << Token[k].first << "," << Token[k].second << ")"<<endl;
	}
	cout << endl;
}
int Token_scan()
{
	cout << "             ********************�ʷ������׶�:********************" << endl;
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
