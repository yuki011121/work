#include"SynaxAnalysis.h"
#include"TOKEN.h"
#include"SYS.h"
using namespace std;
SYS sys; //�м������
string tem;//�ݴ�������ʶ��������������Ԫʽ

int error = 0;//����﷨�����Ƿ�ɹ�
int id = 0;//����Ƿ���ҵ���ʶ��
string nextchar; //������ַ�
string s;		 //�ݴ������ַ�

ifstream in("Token.txt");	//����token����
ofstream out("debug.txt"); //��ʱdebug

void jmp()//TOKEN���еĶ�ȡ����jmp����
{
	string t; //���������ո�ͻ���
	getline(in, s, ' ');
	nextchar = s;
	getline(in, t, '\n');
}

int table1()
{
	for (string temp : I) //���ұ�ʶ����
	{
		if (nextchar == temp)
		{
			id = 1;
		}
	}
	return id;
}

void PZ()  //�����һ��
{
	if (error == 1)
		return;
	out << " PZ" << endl;
	if (nextchar == "int" || nextchar == "float")
	{
		SF();  //����������
	}
	if (nextchar == "if" || nextchar == "while")
	{
		SL();  //��������
	}
	for (int k = 0; k < i; k++)
	{

		if (nextchar == I[k])
		{
			SL();//��������
		}
	}
}

void SF()
{
	if (error == 1)
		return;
	out << " SF" << endl;
	ID();//����ID�ӳ�������Ժ󣬻�����жϣ��ж���һ���ַ��ǲ���SF��First���ϣ��������Ҫ���½���SF�С�
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
	type();//����type����
	IT();//��type���������ʶ������
}

void type()
{
	if (error == 1)
		return;
	out << "type" << endl;
	jmp();//������
}

void IT()
{
	if (error == 1)
		return;
	out << "IT" << endl;
	if (table1())  //���ʶ����
	{
		jmp();
	}
	else  //�鲻��
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
	if (nextchar == "if" || nextchar == "while") //�ж���һ���ַ��ǲ���if��while�����������½���SL
	{
		SL();
	}

	for (int k = 0; k < i; k++)//�ж���һ���ַ��ǲ��Ǳ�ʶ�������������½���SL
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
	if (nextchar == "if")  //����ѭ����ֵ���
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
	jmp(); //��ֵ����һ���ַ�һ����һ����ʶ��
	if (nextchar == "=")//jmp���Ժ�ָ����ƣ��ж���һ���ǲ��ǣ�
	{
		jmp(); //����jmp������AE
	}
	else
	{
		error = 1;//�������
	}
	AE();
	sys.ASSI();
	if (nextchar == ";")
	{
		jmp();
	}
}

void AE() //�������ʽ
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
	if (nextchar == "+")  //�Ӽ��˳�˳��
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
		AE();   //�������ʽ
		if (nextchar == ")")
		{
			jmp();
		}
		else
		{
			error = 1; //����״̬��Ϊ1
			out << "������')'ȱʧ " << endl;
		}
	}
	else //˵��Ϊ��ʶ�����߳���
	{
		sys.PUSH(nextchar);
		jmp();
	}
}

void CS()//�������
{
	if (error == 1)
		return;
	out << "CS" << endl;
	jmp();
	if (nextchar == "(")//jmp��IF���ж���һ���ַ��Ƿ��ǡ�����������������CE���ʽ�������ж��Ƿ���ڡ�����
	{
		jmp();
		CE();
		if (nextchar == ")")
		{
			jmp();
		}
		else
		{
			error = 1; //����״̬��Ϊ1
			out << "������')'ȱʧ' " << endl;
		}
	}
	sys.IF();
	if (nextchar == "{")//�������Լ����������ж��Լ��������ڲ��Ĵ���
	{
		jmp();
		SL();
		if (nextchar == "}")
		{
			jmp();
		}
		else
		{
			error = 1; //����״̬��Ϊ1
			out << "������')'ȱʧ " << endl;
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
				error = 1; //����״̬��Ϊ1
				out << "������')'ȱʧ " << endl;
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

void LS()//ѭ����䡣����˼·�����������ͬ��
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
			error = 1; //����״̬��Ϊ1
			out << "������')'ȱʧ " << endl;
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
			error = 1; //����״̬��Ϊ1
			out << "������')'ȱʧ" << endl;
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
		tem = ">";          //���ݴ�������ʶ����ֵ��Ϊ������Ԫʽ��׼��
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

	cout << "             ********************�﷨�����׶�:********************" << endl;
	cout << endl;
	int number = 0;
	while (!in.eof())  //�����ļ���
	{
		s = "";
		error = 0;
		jmp();
		PZ();
		if (error == 0 && in.eof())
		{
			out << "             ********************�﷨������ȷ!********************" << endl;
			cout << "             ********************�﷨������ȷ!********************" << endl;
			cout << endl;
		}
		else
		{
			out << "             ********************�﷨��������!********************" << endl;
			cout << "             ********************�﷨��������!********************" << endl;
			cout << endl;
		}
		break;
	}
	sys.pirnt_qt();
	return 0;
}
