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
typedef union{   //不确定是何种数据类型（int、float）
	int ival;
	float fval;
}vv;
typedef struct list{//常数表 
	vv val;
	list *next;
	typex tp;
}List;
List* addlist(List* listnow, int& x); //添加常数表节点：整型
List* addlist(List* listnow, float& x); //添加常数表节点：浮点型
typedef struct list_temp {//临时变量表，为寄存器分配做准备
	string name;
	list_temp* next;
	int level=0;
}tList;
tList* addlist(tList* listnow);//添加临时变量表节点

typedef class symbollist{  //符号表的结构 
	public:
		int n;//语义分析：重定义次数检查
		string name;
		typex typ;
		category cat;
		vv value;
		int offset;
		symbollist* next;//符号表用链表结构
		List* addr;
		void Setname(string& n){ //输入名字 
			name=n;
		}
		void Settype(typex& t){//确定数据类型 
			typ=t;
		}
		void Setcate(category& c){//确定种类 
			cat=c;
		}
		void Setaddr(List *a){ //链接常数表 
			addr=a;
		}
		void Setoffser(int& o) { //定义偏移量
			offset = o;
		}
		symbollist* addlist(){ //增加表格 
			symbollist *t=new symbollist;
			this->next=t;
			return t;
		}
}symlist;
void symbegin();
