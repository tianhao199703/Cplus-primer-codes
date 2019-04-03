#include "Query.h"
using namespace std;


int main(){
	ifstream file("test.txt");
	TextQuery tq(file);
	print(cout,tq.query("fuck"));
	print(cout,tq.query("suck"));

	Query q = Query("fuck")&Query("suck") | Query("lack");
	print (cout,q.eval(tq));
	cout << q.rep();
	return 0;
}
