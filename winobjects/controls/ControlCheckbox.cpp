#include "ControlCheckbox.h"

ControlCheckbox::ControlCheckbox(  )
{

}

ControlCheckbox::ControlCheckbox(HWND hParent, int nIDDlgItem) : Control(hParent, nIDDlgItem)
{

}

ControlCheckbox::operator bool() const
{
	return ( SendMessage( _hwnd, BM_GETCHECK, 0, 0 ) == BST_CHECKED ) ? true : false;  

}

void ControlCheckbox::Check(  )
{
	SendMessage( _hwnd, BM_SETCHECK, BST_CHECKED, 0 ); 
}

void ControlCheckbox::UnCheck(  )
{
	SendMessage( _hwnd, BM_SETCHECK, BST_UNCHECKED, 0 ); 
}

ControlCheckbox::~ControlCheckbox(  )
{

}