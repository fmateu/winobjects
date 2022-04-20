#include "Exception.h"

Exception::Exception()
{

}

Exception::Exception( std::wstring type ) : _type(type), _descr(L"")
{

}

Exception::Exception( std::wstring type , std::wstring descr ) : _type(type), _descr(descr)
{

}
Exception::operator std::wstring() const
{
	return _descr;
}


void Exception::PopUp()
{
	MessageBox( NULL, _descr.c_str(), _type.c_str(), MB_ICONEXCLAMATION );
}

Exception::~Exception()
{

}


		

