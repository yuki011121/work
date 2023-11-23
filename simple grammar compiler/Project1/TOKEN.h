#pragma once
#include<unordered_map>
#include<string>
#include<vector>
#include"sym.h"
using namespace std;
extern string K[20];
extern string P[20];
extern vector<string>I;//±êÊ¶·û±í
extern vector<float>C;
extern vector<int>C1;
extern vector<float>C2;
extern int i ; 
extern int c ;
extern int p ;
extern int l ;
extern symbollist sym;
int Token_scan();
void judge(string& a, ofstream& cy);
void lc(string n, ofstream& cy);
void li(string n, ofstream& cy);
int lpp(string n, ofstream& cy);
int lp(string n, ofstream& cy);
int lk(string n, ofstream& cy);
void print_token();