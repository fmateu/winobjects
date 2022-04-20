#pragma once
#include <windows.h>
#include <commctrl.h>
#include <string>
#include "macros.h"
#include "DBRow.h"
#include "BaseMemory.h"
#include "Control.h"
#include <map>
#include <vector>

class ControlListview : public Control
{
	private:

		class Column
		{
			public:
				std::wstring cfmt;
				Column(){};
				Column(std::wstring cfmt):
					cfmt(cfmt) {};
		};
	
		std::map<int,Column> Columns;
		std::vector<std::wstring> query;	
		BASE::Memory mem;
	public:
		ControlListview(  );
		ControlListview(HWND hParent, int nIDDlgItem);
		std::wstring getQueryPart(int i);
		void setQueryPart( int i, std::wstring str );
		std::wstring getQuery();
		void addColumn( UINT iSubItem, UINT fmt, UINT cx, std::wstring pszText, UINT iImage, std::wstring cfmt );
		void deleteItem(int item);
		int getCount();
		int getSelectedIndex();
		void Clear();
		int addRow( DB::Row row, int count);
		DB::Row getRow( int colcount );
		DB::Row getItemData(int index);
		~ControlListview();

};