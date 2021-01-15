#include <iostream>
#include <boost\function.hpp>
#include "class.h"

using namespace std;
using namespace boost;

void test(int a, int b)
{
	cout << a + b << endl;
}

class testcls
{
public:
	void operator()(int a, int b)
	{
		cout << a+b << endl;
	}
	void show(int a, int b)
	{
		cout << a*b << endl;
	}
private:
};

int main()
{
	try
	{
		boost::function<void(int, int)> f = &test;							// �Ϲ� �Լ�
		f(3, 5);

		boost::function<void(int, int)> f2 = testcls();						// �Լ� ��ü
		f2(3, 8);

		testcls tcl;
		boost::function<void(testcls*, int, int)>f3 = &testcls::show;		// ��� �Լ�
		f3(&tcl, 5, 5);
	}
	
	catch (boost::bad_function_call &e)
	{
		cerr << e.what() << endl;
	}

	return 0;
}