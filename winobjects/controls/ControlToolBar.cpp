#include "ControlToolBar.h"
#include "macros.h"

ControlToolBar::ControlToolBar(  )
{

}

ControlToolBar::ControlToolBar(HWND hParent, int nIDDlgItem) : Control(hParent, nIDDlgItem)
{
	SendMessage( _hwnd, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);
}

void ControlToolBar::setimagelist( HIMAGELIST imglist )
{
	SendMessage(_hwnd, TB_SETIMAGELIST, 0, (LPARAM)imglist);
}


void ControlToolBar::addbuttons( int num, TBBUTTON buttons[])
{
	SendMessage(_hwnd, TB_ADDBUTTONS, num, (LPARAM)buttons);
}


void ControlToolBar::autosize(  )
{
	SendMessage( _hwnd, TB_AUTOSIZE, 0, 0);
}


void ControlToolBar::adddialog(CDialog* dlg)
{
	_dialogs.insert( std::pair<UINT,CDialog*>((UINT)(*dlg),dlg) );
}


void ControlToolBar::showtab(int cmd)
{
	for (auto const& it : _dialogs)
	{
		SendMessage(_hwnd, TB_SETSTATE, it.first, MAKELONG(TBSTATE_ENABLED,0));
		it.second->Hide();
	}	
	SendMessage(_hwnd, TB_SETSTATE, cmd, MAKELONG( TBSTATE_ENABLED | TBSTATE_PRESSED,0 ));
	_dialogs[cmd]->Show();
}

CDialog* ControlToolBar::getdialog(int cmd)
{
	return _dialogs[cmd];
}


ControlToolBar::~ControlToolBar(  )
{

}