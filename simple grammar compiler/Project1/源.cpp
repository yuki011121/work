#include "TOKEN.h"
#include "SynaxAnalysis.h"
#include "SemAnalysis.h"
symlist* head = new symlist;
symlist* now = head;
List* lhead = new List;
List* lnow = lhead;
extern vector<pair<char, int> >Token;
unordered_map<string, symbollist*> map_total;
extern SYS sys;
using namespace std;
int main(){
	Token_scan();
	symbegin();
	symlist* tt = head;
	Synax();
	outdaima(sys.qt);
	
}