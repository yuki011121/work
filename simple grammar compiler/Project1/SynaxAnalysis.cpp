#include"SynaxAnalysis.h"
#include"TOKEN.h"
#include"SYS.h"
using namespace std;
SYS sys; //中间代码类
string tem;//暂存条件标识符，用于生成四元式

int error = 0;//标记语法分析是否成功
int id = 0;//标记是否查找到标识符
string nextchar; //读入的字符
string s;		 //暂存读入的字符

ifstream in("Token.txt");	//读入token序列
ofstream out("debug.txt"); //暂时debug

void jmp()//TOKEN序列的读取运用jmp函数
{
	string t; //用于跳过空格和换行
	getline(in, s, ' ');
	nextchar = s;
	getline(in, t, '\n');
}

int table1()
{
	for (string temp : I) //查找标识符表
	{
		if (nextchar == temp)
		{
			id = 1;
		}
	}
	return id;
}

void PZ()  //进入第一条
{
	if (error == 1)
		return;
	out << " PZ" << endl;
	if (nextchar == "int" || nextchar == "float")
	{
		SF();  //进入声明表
	}
	if (nextchar == "if" || nextchar == "while")
	{
		SL();  //进入语句表
	}
	for (int k = 0; k < i; k++)
	{

		if (nextchar == I[k])
		{
			SL();//进入语句表
		}
	}
}

void SF()
{
	if (error == 1)
		return;
	out << " SF" << endl;
	ID();//当在ID子程序出来以后，会进行判断，判断下一个字符是不是SF的First集合，如果是则要重新进入SF中。
	if (nextchar == "int")
	{
		SF();
	}
	else if (nextchar == "float")
	{
		SF();
	}
}

void ID()
{
	if (error == 1)
		return;
	out << "ID" << endl;
	type();//进入type函数
	IT();//从type出来进入标识符表函数
}

void type()
{
	if (error == 1)
		return;
	out << "type" << endl;
	jmp();//继续读
}

void IT()
{
	if (error == 1)
		return;
	out << "IT" << endl;
	if (table1())  //查标识符表
	{
		jmp();
	}
	else  //查不到
	{
		error = 1;
	}
	if (nextchar == ",")
	{
		jmp();
		IT();
	}
	if (nextchar == ";")
	{
		jmp();
	}
}

void SL()
{
	if (error == 1)
		return;
	out << "SL" << endl;
	S();
	if (nextchar == "if" || nextchar == "while") //判断下一个字符是不是if或while，是则又重新进入SL
	{
		SL();
	}

	for (int k = 0; k < i; k++)//判断下一个字符是不是标识符，是则又重新进入SL
	{
		if (nextchar == I[k])
		{
			SL();
		}
	}
}

void S()
{
	if (error == 1)
		return;
	out << "S" << endl;
	if (nextchar == "if")  //条件循环或赋值语句
	{
		CS();
	}
	else if (nextchar == "while")
	{
		LS();
	}
	for (int k = 0; k < i; k++)
	{
		if (nextchar == I[k])
		{
			sys.PUSH(nextchar);
			AS();
		}
	}
}

void AS()
{
	if (error == 1)
		return;
	out << "AS" << endl;
	jmp(); //赋值语句第一个字符一定是一个标识符
	if (nextchar == "=")//jmp掉以后（指针后移）判断下一个是不是＝
	{
		jmp(); //是则jmp掉进入AE
	}
	else
	{
		error = 1;//否则错误
	}
	AE();
	sys.ASSI();
	if (nextchar == ";")
	{
		jmp();
	}
}

void AE() //算术表达式
{
	if (error == 1)
		return;
	out << "AE" << endl;
	Z();
	T();
}

void Z() //AE->ZT
{
	if (error == 1)
		return;
	out << " Z" << endl;
	if (nextchar == "+")  //加减乘除顺序
	{
		jmp();
		T();
		Z();
		sys.OP("+");
	}
	else if (nextchar == "-")
	{
		jmp();
		T();
		Z();
		sys.OP("-");
	}
	else if (nextchar == "*")
	{
		jmp();
		F();
		Z();
		sys.OP("*");
	}
	else if (nextchar == "/")
	{
		jmp();
		F();
		Z();
		sys.OP("/");
	}
}

void T()//AE->ZT
{
	if (error == 1)
		return;
	out << "T" << endl;
	F();
	Z();
}

void F()  //
{
	if (error == 1)
		return;
	out << "F" << endl;
	if (nextchar == "(")
	{
		jmp();
		AE();   //算数表达式
		if (nextchar == ")")
		{
			jmp();
		}
		else
		{
			error = 1; //错误状态置为1
			out << "右括号')'缺失 " << endl;
		}
	}
	else //说明为标识符或者常数
	{
		sys.PUSH(nextchar);
		jmp();
	}
}

void CS()//条件语句
{
	if (error == 1)
		return;
	out << "CS" << endl;
	jmp();
	if (nextchar == "(")//jmp掉IF后判断下一个字符是否是“（”，如果是则进入CE表达式，并有判断是否存在“）”
	{
		jmp();
		CE();
		if (nextchar == ")")
		{
			jmp();
		}
		else
		{
			error = 1; //错误状态置为1
			out << "右括号')'缺失' " << endl;
		}
	}
	sys.IF();
	if (nextchar == "{")//“｛”以及“｝”的判断以及大括号内部的处理
	{
		jmp();
		SL();
		if (nextchar == "}")
		{
			jmp();
		}
		else
		{
			error = 1; //错误状态置为1
			out << "右括号')'缺失 " << endl;
		}
	}
	if (nextchar == "else")
	{
		sys.EL();
		jmp();
		if (nextchar == "{")
		{
			jmp();
			SL();
			if (nextchar == "}")
			{
				jmp();
			}
			else
			{
				error = 1; //错误状态置为1
				out << "右括号')'缺失 " << endl;
			}
		}
	}
	sys.IE();
}

void CE()
{
	if (error == 1)
		return;
	out << "CE" << endl;
	AE();
	ZYZ();
	AE();
	sys.OP(tem);
}

void LS()//循环语句。大体思路与条件语句相同。
{
	if (error == 1)
		return;
	out << "LS" << endl;
	sys.WH();
	jmp();
	if (nextchar == "(")
	{
		jmp();
		CE();
		if (nextchar == ")")
		{
			jmp();
		}
		else
		{
			error = 1; //错误状态置为1
			out << "右括号')'缺失 " << endl;
		}
	}
	sys.DO();
	if (nextchar == "{")
	{
		jmp();
		SL();
		if (nextchar == "}")
		{
			jmp();
		}
		else
		{
			error = 1; //错误状态置为1
			out << "右括号')'缺失" << endl;
		}
	}
	sys.WE();
}

void ZYZ()
{
	if (error == 1)
		return;
	out << "ZYZ" << endl;
	if (nextchar == ">")
	{
		tem = ">";          //给暂存条件标识符赋值，为生成四元式做准备
		jmp();
	}
	else if (nextchar == "<")
	{
		tem = "<";
		jmp();
	}
	else if (nextchar == ">=")
	{
		tem = ">=";
		jmp();
	}
	else if (nextchar == "<=")
	{
		tem = "<=";
		jmp();
	}
	else if (nextchar == "==")
	{
		tem = "==";
		jmp();
	}
	else if (nextchar == "!=")
	{
		tem = "!=";
		jmp();
	}
	else
	{
		error = 1;
	}
}

int Synax()
{

	cout << "             ********************语法分析阶段:********************" << endl;
	cout << endl;
	int number = 0;
	while (!in.eof())  //读入文件流
	{
		s = "";
		error = 0;
		jmp();
		PZ();
		if (error == 0 && in.eof())
		{
			out << "             ********************语法分析正确!********************" << endl;
			cout << "             ********************语法分析正确!********************" << endl;
			cout << endl;
		}
		else
		{
			out << "             ********************语法分析错误!********************" << endl;
			cout << "             ********************语法分析错误!********************" << endl;
			cout << endl;
		}
		break;
	}
	sys.pirnt_qt();
	return 0;
}
