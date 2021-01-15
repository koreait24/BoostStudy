#include <iostream>
using namespace std;

int main()
{
	int a = 5;
	int b = 2;

	int result_1 = [](int c, int d)->int {return c + d;}(a, b);
	int result_2 = [=]()->int {return a + b; }(); // = call by value, & call by reference

	cout << result_1 << endl;
	cout << result_2 << endl;

	return 0;
}