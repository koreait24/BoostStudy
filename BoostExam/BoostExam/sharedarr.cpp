#include <iostream>
#include <boost\smart_ptr.hpp>
#include "class.h"

using namespace std;
using namespace boost;

int main()
{
	boost::shared_array<RefCount>p3(new RefCount[5]);

	for (int i = 0; i < 5; i++)
	{
		p3[i].Count(i);
		p3[i].Print();
	}

	return 0;
}