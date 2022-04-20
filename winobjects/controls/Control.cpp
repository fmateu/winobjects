#include "Control.h" 
#include "ExceptionWindows.h" 

Control::Control()
{

}	

Control::Control (HWND hParent, UINT nIDDlgItem)
{

	if (( _hwnd = GetDlgItem( hParent, nIDDlgItem ) ) == NULL ) throw ExceptionWindows(GetLastError());
	_itemid = nIDDlgItem;
    SetWindowLongPtr( _hwnd, GWLP_USERDATA, (LONG_PTR)this );
}	

Control::operator UINT() const
{
	return _itemid;
}

Control::operator HWND() const
{
	return _hwnd;
}

void Control::Show()
{
	ShowWindow( _hwnd, SW_SHOW );
}	

void Control::Hide()
{
	ShowWindow( _hwnd, SW_HIDE );
}	

void Control::SetFocus()
{
	::SetFocus( _hwnd);
}


bool Control::hasFocus()
{
	return (::GetFocus() == _hwnd ) || (GetForegroundWindow() == _hwnd);
}

void Control::Enable()
{
	EnableWindow( _hwnd , TRUE );
}

void Control::Disable()
{
	EnableWindow( _hwnd , FALSE );
}


Control::~Control ()
{

}	
