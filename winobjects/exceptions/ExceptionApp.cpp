#include "ExceptionApp.h"
#include "macros.h"


ExceptionApp::ExceptionApp() : Exception( L"ExceptionApp" )
{

}

ExceptionApp::ExceptionApp( std::wstring type, std::wstring descr ) : Exception( type, descr )
{
	
}

ExceptionApp::ExceptionApp( std::wstring descr ) : Exception( L"ExceptionApp", descr )
{
	
}

ExceptionApp::~ExceptionApp()
{

}
