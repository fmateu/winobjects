#include "ControlComboDB.h"

ControlComboDB::ControlComboDB(  )
{

}
ControlComboDB::ControlComboDB(HWND hParent, int nIDDlgItem) : ControlCombo(hParent, nIDDlgItem)
{

}

DB::Row ControlComboDB::getRow( int colcount )
{
	return new( mem.Get( sizeof(DB::Field)*colcount ) ) DB::Field[colcount];
}

int ControlComboDB::addRow( int display, std::wstring cfmt, DB::Row row )
{
	int index = getCount();
	std::wstring lParam = row[display].format(cfmt.c_str());
	SendMessage( _hwnd, CB_ADDSTRING, index, (LPARAM)lParam.c_str());
	SendMessage( _hwnd, CB_SETITEMDATA,index,(LPARAM)row );  
	return index;
}

DB::Row ControlComboDB::getData()
{
	int selected;
	if ( ( selected = getSelected() ) == CB_ERR ) throw ExceptionControl(); 
	DB::Row ret = (DB::Row)SendMessage(_hwnd, CB_GETITEMDATA, selected, 0);  
	return ret;
}

void ControlComboDB::Clear()
{
	mem.Clear();
	SendMessage( _hwnd, CB_RESETCONTENT,0 , 0);
}

ControlComboDB::~ControlComboDB(  )
{

}