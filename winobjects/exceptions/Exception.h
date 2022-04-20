#pragma once
#include <windows.h>
#include <commctrl.h>
#include <string>
#include <exception>

class Exception : public std::exception
{
	protected:
		std::wstring _type;
		std::wstring _descr;
	public:
		Exception();
		Exception( std::wstring type );
		Exception( std::wstring type , std::wstring descr );
		~Exception();
		operator std::wstring() const;
		void PopUp();

};