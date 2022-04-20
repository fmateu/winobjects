#pragma once
#include "Exception.h"

class ExceptionControl : public Exception
{
	public:
		ExceptionControl();
		ExceptionControl( std::wstring descr );
		~ExceptionControl();
};