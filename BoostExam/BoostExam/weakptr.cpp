#include <iostream>
#include <boost\smart_ptr.hpp>
#include "class.h"

using namespace std;
using namespace boost;

int main()
{
	pPtr pptr(new Parent());
	cPtr cptr(new Child());
	
	cout << "Parent의 참조개수 : " << pptr.use_count() << endl;
	cout << "Child의  참조개수 : " << cptr.use_count() << endl;

	pptr->cld = cptr;
	cptr->wp = pptr;

	cout << "Parent의 참조개수 : " << pptr.use_count() << endl;
	cout << "Child의  참조개수 : " << cptr.use_count() << endl;

	cptr->Action();
	pptr.reset();

	return 0;
}