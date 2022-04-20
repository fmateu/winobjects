#pragma once
#include "Exception.h"

class ExceptionApp : public Exception
{
	public:
		ExceptionApp();
		ExceptionApp( std::wstring descr );
		ExceptionApp( std::wstring type, std::wstring descr );
		~ExceptionApp();
};