#include "ControlCombo.h"

ControlCombo::ControlCombo(  )
{

}

ControlCombo::ControlCombo(HWND hParent, int nIDDlgItem) : Control(hParent, nIDDlgItem)
{

}

ControlCombo::~ControlCombo(  )
{

}

int ControlCombo::getSelected()
{
	return SendMessage( _hwnd,CB_GETCURSEL,0 ,0 );
}

void ControlCombo::setSelected(int index)
{
	SendMessage( _hwnd,CB_SETCURSEL,index ,0 );
}

int ControlCombo::getCount()
{
	return SendMessage( _hwnd, CB_GETCOUNT,0 ,0 );
}


void ControlCombo::Clear()
{
	SendMessage( _hwnd, CB_RESETCONTENT,0 , 0);
}

void ControlCombo::Reset()
{
	SendMessage( _hwnd, CB_SETCURSEL, -1, 0);
}
