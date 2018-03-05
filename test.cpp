#include "Desk.h"
#include <iostream>
using namespace std;


int main() {
	desk testDesk;
	size_t id = 0;
	string varsNames = "abcdefg";
	testDesk.add(new var());
	testDesk.add(new assig());
	testDesk.add(new circle_while());
	testDesk.add(new output());
	testDesk.brk(4);
	testDesk.link_with_circle(3, 4);
	testDesk.add(new assig());
	testDesk.brk(5);
	testDesk.link(4, 5);
	testDesk.link(5, 3);
	testDesk.change(1, "int|n");
	testDesk.change(2, "n||10");
	testDesk.change(3, "n > 0");
	testDesk.change(4, "n");
	testDesk.change(5, "n||n - 1");
	cout << testDesk.generate();

	system("pause");
}