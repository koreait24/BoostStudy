#include <iostream>
#include <boost\smart_ptr.hpp>
#include "class.h"

using namespace std;
using namespace boost;


int main()
{
	boost::shared_ptr<Person> p1(new Person());

	p1->setName("���Ǽ�");										// ���۷��� ī���� +1 (������)
	cout << p1->getName() << " , " << p1.use_count() << endl;

	boost::shared_ptr<Person> p2(p1);							// ���۷��� ī���� +2 (���� ����)
	cout << p1->getName() << " , " << p1.use_count() << endl;

	p1.reset();													// ���۷��� ī���� 0 (����)
	cout << "p1 ���۷��� ī����: " << " , " << p1.use_count() << endl;
	return 0;
}