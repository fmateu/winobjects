#include "ExceptionODBC.h"
#include "macros.h"

ExceptionODBC::ExceptionODBC() : Exception( L"ExceptionODBC" )
{

}

ExceptionODBC::ExceptionODBC( std::wstring descr ) : Exception( L"ExceptionODBC", descr )
{
	
}

ExceptionODBC::~ExceptionODBC()
{

}
