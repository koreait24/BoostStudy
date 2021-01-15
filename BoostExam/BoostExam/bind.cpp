#include <iostream>
#include <vector>
#include <boost\bind.hpp>
#include <boost\ref.hpp>
#include <boost\function.hpp>
#include "class.h"

using namespace std;
using namespace boost;

struct overloading
{
	int operator()(int a, int b) { return a * b; }
	long operator()(long a, long b) { return a + b; }
};

class clsfunc
{
public:
	int executeBind(int a, int b, int c){ return a + b + c;	}
};

int fun2(int a, int b, int c) { return a + b + c; }

int main()
{
	int temp = 10;
	// 상수 2개와 변수1개
	auto p2 = bind(fun2, 3, 5, temp);
	cout << "bind(fun2, 3, 5, temp)\n" << p2() << endl;
	// 상수 2개와 변수 참조1번
	auto  p3 = bind(fun2, 3, 5, boost::ref(temp));
	cout << "bind(fun2, 3, 5, boost::ref(temp))\n" << p3() <<endl;
	// 변수 3개와 매개변수 순서
	int x = 3, y = 7, z = 9;
	auto p4 = bind(fun2, _1, _2, _3)(x, y, z);
	cout << "bind(fun2, _1, _2, _3)(x, y, z)\n" << p4 << endl;
	// 구조체 연산자 오버로딩 바인드
	overloading ol;
	auto p5 = boost::bind<int>(ol, _1, _2)(x, y);
	cout << "bind<int>(ol, _1, _2)(x, y)\n" << p5 << endl;
	// 함수 포인터 바인드
	clsfunc cf;
	boost::function<int(clsfunc*, int, int, int)> f1 = &clsfunc::executeBind;
	f1(&cf, x, y, z);
	auto p6 = boost::bind<int>(f1, &cf, _1, _2, _3)(x, y, z);
	cout << "bind<int>(f1, &cf, _1, _2, _3)(x, y, z))\n" << p6 << endl;
	return 0;
}