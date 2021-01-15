#include <iostream>
#include <boost\smart_ptr.hpp>
#include "class.h"

using namespace std;
using namespace boost;

int main()
{
	pPtr pptr(new Parent());
	cPtr cptr(new Child());
	
	cout << "Parent�� �������� : " << pptr.use_count() << endl;
	cout << "Child��  �������� : " << cptr.use_count() << endl;

	pptr->cld = cptr;
	cptr->wp = pptr;

	cout << "Parent�� �������� : " << pptr.use_count() << endl;
	cout << "Child��  �������� : " << cptr.use_count() << endl;

	cptr->Action();
	pptr.reset();

	return 0;
}