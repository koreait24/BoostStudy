#include <iostream>
#include <boost\smart_ptr.hpp>
#include "class.h"

using namespace std;
using namespace boost;

int main()
{
	intrusive_ptr<Intrusive> p1(new Intrusive);

	p1->print();
	cout << "�ּ� : " << p1.get() << endl;

	cout << "reset() ����" << endl;
	p1.reset();
	cout << "�ּ� : " << p1.get() << endl;
	
	return 0;
}