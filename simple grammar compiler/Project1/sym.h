#pragma once
#include<string>
#include<vector>
#include<cstdio>
#include <unordered_map>
#include <unordered_set>
#include<iostream>
#include<unordered_map>
using namespace std;
enum category{
	v,    //variety
	o    //other
};
enum typex{
	in1,  //integer
	fl1 //float
};
typedef union{   //��ȷ���Ǻ����������ͣ�int��float��
	int ival;
	float fval;
}vv;
typedef struct list{//������ 
	vv val;
	list *next;
	typex tp;
}List;
List* addlist(List* listnow, int& x); //��ӳ�����ڵ㣺����
List* addlist(List* listnow, float& x); //��ӳ�����ڵ㣺������
typedef struct list_temp {//��ʱ������Ϊ�Ĵ���������׼��
	string name;
	list_temp* next;
	int level=0;
}tList;
tList* addlist(tList* listnow);//�����ʱ������ڵ�

typedef class symbollist{  //���ű�Ľṹ 
	public:
		int n;//����������ض���������
		string name;
		typex typ;
		category cat;
		vv value;
		int offset;
		symbollist* next;//���ű�������ṹ
		List* addr;
		void Setname(string& n){ //�������� 
			name=n;
		}
		void Settype(typex& t){//ȷ���������� 
			typ=t;
		}
		void Setcate(category& c){//ȷ������ 
			cat=c;
		}
		void Setaddr(List *a){ //���ӳ����� 
			addr=a;
		}
		void Setoffser(int& o) { //����ƫ����
			offset = o;
		}
		symbollist* addlist(){ //���ӱ�� 
			symbollist *t=new symbollist;
			this->next=t;
			return t;
		}
}symlist;
void symbegin();
