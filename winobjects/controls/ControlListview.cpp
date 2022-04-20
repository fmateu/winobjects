#include "ControlListview.h"
#include "ExceptionControl.h"


ControlListview::ControlListview()
{
}

ControlListview::ControlListview(HWND hParent, int nIDDlgItem) : Control(hParent, nIDDlgItem)
{
	ListView_SetExtendedListViewStyle(_hwnd, LVS_EX_FULLROWSELECT);
	query = { L" ", L" ", L" ", L" ", L" ", L" " };
}

DB::Row ControlListview::getRow( int colcount )
{
	return new( mem.Get( sizeof(DB::Field)*colcount ) ) DB::Field[colcount];
}

DB::Row ControlListview::getItemData(int index)
{
  LVITEM lvI;
  lvI.mask = LVIF_PARAM;
  lvI.iItem = index;
  lvI.iSubItem = 0;
  if ( ListView_GetItem(_hwnd, &lvI) == FALSE ) throw ExceptionControl( L"item is not available" );
  return (DB::Row)lvI.lParam;
}

int ControlListview::getSelectedIndex()
{
  int iSelect = ListView_GetNextItem(_hwnd, -1, LVNI_SELECTED);
  return iSelect;
}


int ControlListview::addRow( DB::Row row, int count)
{
	
	int index = getCount();
	LVITEM lvI;
	std::wstring pszText;
	lvI.mask = LVIF_TEXT | LVIF_PARAM;
	lvI.iItem = index;
	lvI.iSubItem = 0;
	lvI.lParam = (LPARAM)row;
	pszText = &( row[1].format( Columns[1].cfmt.c_str() ) )[0];
	lvI.pszText = (LPWSTR)pszText.c_str();
	ListView_InsertItem(_hwnd, &lvI);
	for (int col = 2; col <= count ; col++)
	{
		lvI.mask = LVIF_TEXT;
		lvI.iSubItem = col-1;
		DEBUG(L"cfmt { %s }\n",Columns[col].cfmt.c_str());
		pszText = row[col].format( Columns[col].cfmt.c_str() );
		lvI.pszText = (LPWSTR)pszText.c_str();
		ListView_SetItem(_hwnd, &lvI);
	}
	return index;
}

std::wstring ControlListview::getQueryPart( int i)
{
	return query[i];
}

void ControlListview::setQueryPart( int i, std::wstring str )
{
	query[i].assign(str);
}

std::wstring ControlListview::getQuery()
{
	wchar_t buffer[1024];
	snwprintf(buffer, SIZEOF(buffer), query[0].c_str(), query[1].c_str(), query[2].c_str(), query[3].c_str(), query[4].c_str(), query[5].c_str(), query[6].c_str() );
	return buffer;
}


void ControlListview::deleteItem(int item)
{ 
	ListView_DeleteItem(_hwnd, item );
}

int ControlListview::getCount()
{ 
	return ListView_GetItemCount(_hwnd);
}



void ControlListview::addColumn( UINT iSubItem, UINT fmt, UINT cx, std::wstring pszText, UINT iImage, std::wstring cfmt )
{
	LVCOLUMN lvColumn = {0};
	lvColumn.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT;
	lvColumn.iOrder = iSubItem;
	lvColumn.iSubItem = iSubItem;
	lvColumn.fmt = fmt;
	lvColumn.cx = cx;
	lvColumn.iImage = iImage;
	lvColumn.pszText = &pszText[0];
	Columns[iSubItem] = Column(cfmt);
	ListView_InsertColumn(_hwnd, iSubItem, &lvColumn);
}



void ControlListview::Clear()
{
	mem.Clear();
	ListView_DeleteAllItems(_hwnd);
}


ControlListview::~ControlListview( )
{

}
