#include <iostream>
#include <boost\smart_ptr.hpp>
#include "class.h"

using namespace std;
using namespace boost;

int main()
{
	scoped_ptr<Sample> p1(new Sample());
	scoped_ptr<Sample> p2(new Sample());
	
	scoped_array<Sample> p4(new Sample[5]);
}