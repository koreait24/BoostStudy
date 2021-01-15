#include "class.h"
#include <iostream>
#include <boost\smart_ptr.hpp>

using namespace boost;

int main()
{
	// Sample *p1, *p2;
	// p1 = new Sample();
	// p2 = new Sample();

	// scoped_ptr<Sample> p3(new Sample());
	// scoped_ptr<Sample> p4(new Sample());

	unique_ptr<Sample> p5(new Sample());
	unique_ptr<Sample> p6(new Sample());

	// p1->Print();
	// p2->Print();

	// p3->Print();
	// p4->Print();

	p5->Print();
	p6->Print();

	p6.release();

	// p1->~Sample();
	// p2->~Sample();

	return 0;
}
