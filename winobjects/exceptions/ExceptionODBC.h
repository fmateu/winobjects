#pragma once
#include "Exception.h"

class ExceptionODBC : public Exception
{
	public:
		ExceptionODBC();	
		ExceptionODBC( std::wstring descr );
		~ExceptionODBC();
};