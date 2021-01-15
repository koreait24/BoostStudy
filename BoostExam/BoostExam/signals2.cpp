#include <iostream>
#include <boost\signals2.hpp>
#include <boost\bind.hpp>

using namespace std;

struct Helloworld
{
	void helloworld() const
	{
		cout << "Hello, World!" << endl;
	}
};

struct GoodMorning
{
	void operator()() const
	{
		cout << "...and good morning!" << endl;
	}
};

class Hello
{
public:
	void hello() const
	{
		cout << "Hello, " << endl;
	}
};

int addFunc(int a, int b)
{
	return a + b;
}

int main()
{
	boost::signals2::signal<void()> sig;
	boost::signals2::signal<int(int, int)>  intsig;						// int�� �Լ�

	intsig.connect(&addFunc);
	cout << "intsig(3,5) = " << *intsig(3, 5) << endl;
	

	boost::scoped_ptr<Helloworld> hw(new Helloworld());
	boost::scoped_ptr<Hello> h(new Hello());

	sig.connect(2, boost::bind(&Helloworld::helloworld, hw.get()));		// ����ü�� ����Լ�
	sig.connect(2, boost::bind(&Hello::hello, h.get()));				// Ŭ������ ����Լ�
	sig.connect(2, GoodMorning());										// ����ü�� �����ε�
	sig();
	cout << "a number of slot : " << sig.num_slots() << endl; // ������ ����

	return 0;
}