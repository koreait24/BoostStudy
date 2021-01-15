#include <iostream>
#include <boost\smart_ptr.hpp>
#include "class.h"

using namespace std;
using namespace boost;

int main()
{
	intrusive_ptr<Intrusive> p1(new Intrusive);

	p1->print();
	cout << "林家 : " << p1.get() << endl;

	cout << "reset() 角青" << endl;
	p1.reset();
	cout << "林家 : " << p1.get() << endl;
	
	return 0;
}