#include "sym.h"
using namespace std;
vector<pair<char, int> >Token;
extern symlist* head;//���ű�
extern symlist* now;
extern List* lhead;//������
extern List* lnow;
extern unordered_map<string, symbollist*> map_total;
extern tList* thead;//��ʱ������
extern tList* tnow;
extern vector<pair<char, int> >Token;
extern vector<string>I;
List* addlist(List* listnow, int& x) {//��ӳ�����ڵ㣺����
	List* newt = new List;
	listnow->next = newt;
	newt ->val.ival = x;
	newt ->tp = in1;
	return newt;
}
List* addlist(List* listnow, float& x) {//��ӳ�����ڵ㣺������
	List* newt = new List;
	listnow->next = newt;
	newt->val.fval = x;
	newt->tp = fl1;
	return newt;
}
void symbegin()
{
	for (int ls = 0; ls < Token.size();ls++) {  //
		if (Token[ls].first == 'K' && (Token[ls].second == 1 || Token[ls].second == 4)) {//K[1]:INT  K[4]:FLOAT
			while (1) {
				ls++;
				if (Token[ls].second == 13 && Token[ls].first == 'P') {  //K[13]:;
					break;
				}
				if (Token[ls].first == 'I') {
					symlist* temp = now->addlist();
					now->Setname(I[Token[ls].second-1]);
					map_total.insert(make_pair(I[Token[ls].second-1], now));//�⺯�������롢�ϳ�
					now = temp;
				}
			}
		}
	}
}
tList* addlist(tList* listnow) {//�����ʱ������ڵ㣬�������Ĵ���
	tList* newt = new tList;
	listnow->next = newt;
	newt->level = listnow->level + 1;
	newt->name = "t";
	newt->name += to_string(newt->level);
	return newt;
}

