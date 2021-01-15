#include <iostream>
#include <boost\timer\timer.hpp>
#include "class.h"

using namespace std;
using namespace boost;

int main()
{
	timer::cpu_timer Timer;
	timer::cpu_times sTimer;
	timer::auto_cpu_timer aTimer;

	int i = 0;

	while (i != 50000)
	{
		pow(1.234, i);
		i++;
	}

	cout << Timer.format() << "°æ°ú" << endl;

	return 0;
}