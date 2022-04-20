#include "ControlDateTimePicker.h"
#include "BaseDateTime.h"
#include "ExceptionControl.h"
#include "macros.h"

ControlDateTimePicker::ControlDateTimePicker(  )
{

}

ControlDateTimePicker::ControlDateTimePicker(HWND hParent, int nIDDlgItem) : Control(hParent, nIDDlgItem)
{

}

void ControlDateTimePicker::Clear()
{
	SendMessage( _hwnd, DTM_SETSYSTEMTIME, GDT_NONE, 0 );  
}


std::wstring ControlDateTimePicker::format( std::wstring fmt  )
{
	BASE::DateTime date( (SYSTEMTIME)(*this) );
	return date.format(fmt);
}

void ControlDateTimePicker::setDate( SYSTEMTIME date )
{
	SendMessage( _hwnd, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&date );
}


bool ControlDateTimePicker::isEmpty()
{
	SYSTEMTIME ret = {0};
	return ( SendMessage( _hwnd, DTM_GETSYSTEMTIME, 0, (LPARAM)&ret ) == GDT_VALID ) ? false : true;
}


ControlDateTimePicker::operator SYSTEMTIME() const
{
	SYSTEMTIME ret = {0};
	SendMessage( _hwnd, DTM_GETSYSTEMTIME, 0, (LPARAM)&ret );  
	return ret;
}

ControlDateTimePicker::~ControlDateTimePicker(  )
{

}