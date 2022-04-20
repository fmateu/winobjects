#include "ExceptionControl.h"
#include "macros.h"

ExceptionControl::ExceptionControl()
{

}


ExceptionControl::ExceptionControl( std::wstring descr ) : Exception( L"ExceptionControl", descr )
{
	
}

ExceptionControl::~ExceptionControl()
{

}
