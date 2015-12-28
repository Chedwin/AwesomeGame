#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <iostream>
using namespace std;

namespace GAME {

	class Exception : public _exception {

		// I don't need to put this here 
		// It's just here for reference 
#ifndef _EXCEPTION_DEFINED
		struct _exception {
			int type;       /* exception type - see below */
			char *name;     /* name of function where error occured */
			double arg1;    /* first argument to function */
			double arg2;    /* second argument (if any) to function */
			double retval;  /* value to be returned by function */
		};

#define _EXCEPTION_DEFINED
#endif  /* _EXCEPTION_DEFINED */
	};


	// This is a static exception variable in "GLOBAL" scope of namespace GAME outside of the Exception class
	// Everybody in the GAME namespace can use this
	static Exception exc;

} // namespace GAME

#endif