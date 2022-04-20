#pragma once
#include "Exception.h"

class ExceptionWindows : public Exception
{
	public:
		ExceptionWindows();
		ExceptionWindows( std::wstring descr );
		ExceptionWindows( DWORD err );
		~ExceptionWindows();
};