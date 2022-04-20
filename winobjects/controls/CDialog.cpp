#include "CDialog.h" 
#include "ExceptionWindows.h" 
#include "macros.h" 


CDialog::CDialog()
{
	//DEBUG( L"CDialog::CDialog()\n");
}	

CDialog::CDialog ( int nIDDlgItem, HWND hParent, DLGPROC DialogProc )
{
	//DEBUG( L"CDialog::CDialog ( int, HWND, DLGPROC )\n");
	if ( ( _hwnd  = CreateDialogParam( GetModuleHandle(0), MAKEINTRESOURCE(nIDDlgItem), hParent, DialogProc, 0) ) == NULL )
		throw ExceptionWindows(GetLastError());	 
	_itemid = nIDDlgItem;
    SetWindowLongPtr( _hwnd, GWLP_USERDATA, (LONG_PTR)this );
	SendMessage( _hwnd, WM_APP_DIALOGREADY, 0, 0 );
}

void CDialog::addItem(Control* cl)
{
	//DEBUG( L"CDialog::addItem()\n");
	items.insert( std::pair<UINT,Control*>( (UINT)(*cl), cl ) );
}

CDialog::operator UINT() const
{
	//DEBUG( L"CDialog::operator UINT() const\n");
	return _itemid;
}


Control* CDialog::getItem(UINT it)
{
	////DEBUG( L"CDialog::getItem( %i )\n", it);
	return items[it];
}


CDialog::operator HWND() const
{
	//DEBUG( L"CDialog::operator HWND() const { %i }\n", _hwnd);
	return _hwnd;
}

void CDialog::Show()
{
	ShowWindow( _hwnd, SW_SHOW );
}	

void CDialog::Hide()
{
	ShowWindow( _hwnd, SW_HIDE );
}	

void CDialog::SetFocus()
{
	::SetFocus( _hwnd);
}


bool CDialog::hasFocus()
{
	return (::GetFocus() == _hwnd ) || (GetForegroundWindow() == _hwnd);
}

CDialog::~CDialog()
{
	for( auto it = items.begin(); it != items.end(); )
	{
		delete it->second;
		it = items.erase(it);	
	}	
	EndDialog(_hwnd, 0);
}	