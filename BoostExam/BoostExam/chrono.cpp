#include <iostream>
#include <boost\chrono.hpp>
#include <boost\thread.hpp>
#include "class.h"

using namespace std;
using namespace boost;
using namespace chrono;

void thread1();
void thread2();

int main()
{
	thread threadObject(thread1);
	thread threadObject2(thread2);

	this_thread::sleep(posix_time::seconds(5));

	threadObject.join();
	threadObject2.join();

	cout << system_clock::now() << "\n\n";
	cout << steady_clock::now() << "\n\n";
	cout << high_resolution_clock::now() << "\n\n";
	cout << process_real_cpu_clock::now() << "\n\n";
	cout << process_user_cpu_clock::now() << "\n\n";
	cout << process_system_cpu_clock::now() << "\n\n";
	cout << process_cpu_clock::now() << "\n\n";
	cout << thread_clock::now() << "\n\n";
	return 0;
}

void thread1() {}
void thread2() {}