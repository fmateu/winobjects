#include "ExceptionWindows.h"
#include "macros.h"

ExceptionWindows::ExceptionWindows() : Exception( L"ExceptionWindows" )
{

}

ExceptionWindows::ExceptionWindows( DWORD err ) : Exception( L"ExceptionWindows" )
{
	wchar_t buf[1024];
	FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL,  err, 0, buf, SIZEOF(buf), NULL);
	_descr = buf;
}



ExceptionWindows::ExceptionWindows( std::wstring descr ) : Exception( L"ExceptionWindows", descr )
{
	
}

ExceptionWindows::~ExceptionWindows()
{

}
