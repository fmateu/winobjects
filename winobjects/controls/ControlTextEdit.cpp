#include "ControlTextEdit.h"
#include "macros.h"
#include <regex>

ControlTextEdit::ControlTextEdit()
{

}

ControlTextEdit::ControlTextEdit(HWND hParent, int nIDDlgItem): Control(hParent,nIDDlgItem)
{

}

void ControlTextEdit::Clear( )
{
	SendMessage (_hwnd, WM_SETTEXT,0, (LPARAM)L"");  
}


void ControlTextEdit::setText( std::wstring txt )
{
	SendMessage (_hwnd, WM_SETTEXT,0, (LPARAM) txt.c_str());  
}

void ControlTextEdit::setText( LONG num )
{
	wchar_t buffer[256];
	snwprintf(buffer, SIZEOF(buffer),L"%i", num);
	SendMessage (_hwnd, WM_SETTEXT, 0, (LPARAM)&buffer);  
}

void ControlTextEdit::setText( DOUBLE num )
{
	wchar_t buffer[256];
	snwprintf(buffer, SIZEOF(buffer),L"%.2f", num);
	SendMessage (_hwnd, WM_SETTEXT,0, (LPARAM)&buffer);  
}

int ControlTextEdit::getTextLength( )
{
	return (int)SendMessage(_hwnd, WM_GETTEXTLENGTH, 0, 0);
}


std::wstring ControlTextEdit::getText( )
{
	int length = getTextLength( ) + 1;
	wchar_t* ret = new wchar_t[length];
	SendMessage (_hwnd, WM_GETTEXT, length, (LPARAM)&ret);
	return ret;
}

std::wstring ControlTextEdit::to_sql()
{
	std::wstring ret = getText( );
	//std::regex_replace(edtfreightprice->getText(), std::wregex(L","),  L".")
	ret = std::regex_replace(ret, std::wregex(L"'"),  L"''");
	return ret.c_str();
}



bool ControlTextEdit::isEmpty()
{
	return ( SendMessage(_hwnd, WM_GETTEXTLENGTH, 0, 0) > 0 ) ? false : true;
}


ControlTextEdit::~ControlTextEdit()
{

}

