#pragma once
#include <iostream>

using namespace std;

class Sample
{
public:
	Sample() 
		:count(0)
	{
		cout << "»ý¼º" << endl;
		this->count++;
	}
	~Sample()
	{
		this->count--;
		cout << "¼Ò¸ê)" << "Print: " << this->count << endl;
	}
	void Print()
	{
		cout << "Print: " << this->count << endl;
	}

private:
	int count;
};

class Person
{
public:
	char* getName()
	{
		return name;
	}
	
	void setName(char* _name)
	{
		name = _name;
	}

	~Person()
	{
		cout << "¼Ò¸êÀÚ È£Ãâ" << endl;
	}
private:
	char* name;
};

class RefCount
{
public:
	RefCount() :ref(0)
	{
		cout << "»ý¼º" << endl;
	}

	void Print()
	{
		cout << "¹è¿­ ¼ø¹ø : " << ref << endl;
	}

	void Count(int num)
	{
		ref = num;
	}

	~RefCount()
	{
		cout << "¼Ò¸ê ¼ø¹ø : " << ref << endl;
	}

private:
	int ref;
};

#include <boost\smart_ptr.hpp>

class Parent;
class Child;

typedef boost::shared_ptr<Parent> pPtr;
typedef boost::weak_ptr<Parent> wpPtr;
typedef boost::shared_ptr<Child> cPtr;

class Parent
{
public:
	Parent()
	{
		cout << "Parent °´Ã¼ »ý¼º" << endl;
	}

	void Action()
	{
		cout << "Parent ¿¡¼­ Action() ¹ß»ý" << endl;
	}
	cPtr cld;

	~Parent()
	{
		cout << "Parent °´Ã¼ ¼Ò¸ê" << endl;
	}
};

class Child
{
public:
	Child()
	{
		cout << "Child °´Ã¼ »ý¼º" << endl;
	}

	void Action()
	{
		cout << "Child¿¡¼­ Action() ¹ß»ý" << endl;
		pPtr p = wp.lock(); // Shared Ptr È¹µæ
		if (p)
		{
			p->Action();
		}
	}

	wpPtr wp;

	~Child()
	{
		cout << "Child °´Ã¼ ¼Ò¸ê" << endl;
	}
};

class Intrusive
{
public:
	Intrusive():count(0)
	{
		cout << "°´Ã¼ »ý¼º" << endl;
	}

	~Intrusive()
	{
		cout << "°´Ã¼ ¼Ò¸ê, ÂüÁ¶ È½¼ö : " << this->count << endl;
	}

	void print()
	{
		cout << "ÂüÁ¶ È½¼ö : " << this->count << endl;
	}

	friend void intrusive_ptr_add_ref(Intrusive *p) 
	{
		++(p->count);
	}
	friend void intrusive_ptr_release(Intrusive *p)
	{
		if (--(p->count) == 0)  delete p;
	}
private:
	int count;
};

class thread1
{
public:
	thread1() :ref(0)
	{
	}

	void thread()
	{
		while (ref <= 100)
		{
			cout << "Hello" << endl;
			ref++;
		}
	}

	~thread1()
	{
	}

private:
	int ref;
};

class thread2 :public thread1
{
public:
	thread2() :ref(0)
	{
	}
	void thread()
	{
		while (ref <= 100)
		{
			cout << ", World!" << endl;
			ref++;
		}
	}
	~thread2()
	{
	}
private:
	int ref;
};
