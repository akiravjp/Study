/*
|| How to print the contents of a simple STL list. Whew!
*/
#include <iostream>
#include <string>
#include <string>
#include <list>

using namespace std;

int main(void)
{
	list<string> Milkshakes;
	list<string>::iterator MilkshakeIterator;//ΪMilkshakesʵ����������һ��iteratorָ�룺MilkshakeIterator

	Milkshakes.push_back("Chocolate");
	Milkshakes.push_back("Strawberry");
	Milkshakes.push_front("Lime");
	Milkshakes.push_front("Vanilla");

	// print the milkshakes��ӡ
	Milkshakes.push_front("The Milkshake Menu");
	Milkshakes.push_back("*** Thats the end ***");
	for (MilkshakeIterator = Milkshakes.begin(); MilkshakeIterator != Milkshakes.end(); ++MilkshakeIterator)
	{
		// dereference the iterator to get the element
		cout << *MilkshakeIterator << endl; //���
	}

	getchar();

	return 0;
}