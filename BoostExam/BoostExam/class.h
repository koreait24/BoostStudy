#pragma once
#include <iostream>

using namespace std;

class Sample
{
public:
	Sample() 
		:count(0)
	{
		cout << "����" << endl;
		this->count++;
	}
	~Sample()
	{
		this->count--;
		cout << "�Ҹ�)" << "Print: " << this->count << endl;
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
		cout << "�Ҹ��� ȣ��" << endl;
	}
private:
	char* name;
};

class RefCount
{
public:
	RefCount() :ref(0)
	{
		cout << "����" << endl;
	}

	void Print()
	{
		cout << "�迭 ���� : " << ref << endl;
	}

	void Count(int num)
	{
		ref = num;
	}

	~RefCount()
	{
		cout << "�Ҹ� ���� : " << ref << endl;
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
		cout << "Parent ��ü ����" << endl;
	}

	void Action()
	{
		cout << "Parent ���� Action() �߻�" << endl;
	}
	cPtr cld;

	~Parent()
	{
		cout << "Parent ��ü �Ҹ�" << endl;
	}
};

class Child
{
public:
	Child()
	{
		cout << "Child ��ü ����" << endl;
	}

	void Action()
	{
		cout << "Child���� Action() �߻�" << endl;
		pPtr p = wp.lock(); // Shared Ptr ȹ��
		if (p)
		{
			p->Action();
		}
	}

	wpPtr wp;

	~Child()
	{
		cout << "Child ��ü �Ҹ�" << endl;
	}
};

class Intrusive
{
public:
	Intrusive():count(0)
	{
		cout << "��ü ����" << endl;
	}

	~Intrusive()
	{
		cout << "��ü �Ҹ�, ���� Ƚ�� : " << this->count << endl;
	}

	void print()
	{
		cout << "���� Ƚ�� : " << this->count << endl;
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
