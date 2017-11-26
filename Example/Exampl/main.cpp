#include "Construct.h"
using namespace std;

int main()
{
	cout << "A :  ->  B :  ->  if A ? B -> Y -> message 1" << endl;
	cout << "                       |                    " << endl;
	cout << "                       N                    " << endl;
	cout << "                       |                    " << endl;
	cout << "                     message 2              " << endl;
	var<int> a(0);
	a._name = "A";
	var<int> b(0);
	b._name = "B";
	cout << "Input variable a: " << endl;
	cin >> a;
	cout << "Input variable b: " << endl;
	cin >> b;
	cout << "Input ?-log.op : " << endl;
	string op;
	cin >> op;
	CaseStat<int> if_stat(&a, op, &b);
	cout << "Input message 1 : " << endl;
	string msg1;
	cin >> msg1;
	cout << "Input message 2 : " << endl;
	string msg2;
	cin >> msg2;
	output<int> mesg1(msg1, nullptr);
	output<int> mesg2(msg2, nullptr);
	a.next = &b;
	b.next = &if_stat;
	if_stat._next1 = &mesg1;
	if_stat._next0 = &mesg2;
	cout << endl << endl;
	cout << "Program Spindle" << endl;
	cout << "Begin" << endl;
	a.DoSmth();
	b.DoSmth();
	if_stat.DoSmth();
	cout << "End." << endl;
	cout << endl << ">>" << if_stat << endl;

	
	system("pause");
}