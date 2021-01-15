#include <iostream>
#include <boost\smart_ptr.hpp>
#include "class.h"

using namespace std;
using namespace boost;


int main()
{
	boost::shared_ptr<Person> p1(new Person());

	p1->setName("조건섭");										// 레퍼런스 카운터 +1 (생성자)
	cout << p1->getName() << " , " << p1.use_count() << endl;

	boost::shared_ptr<Person> p2(p1);							// 레퍼런스 카운터 +2 (복사 참조)
	cout << p1->getName() << " , " << p1.use_count() << endl;

	p1.reset();													// 레퍼런스 카운터 0 (리셋)
	cout << "p1 레퍼런스 카운터: " << " , " << p1.use_count() << endl;
	return 0;
}