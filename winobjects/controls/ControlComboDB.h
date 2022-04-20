#pragma once
#include <windows.h>
#include "BaseMemory.h"
#include "DBRow.h"
#include "ControlCombo.h"
#include "ExceptionControl.h"

class ControlComboDB : public ControlCombo
{
	private:
		BASE::Memory mem;
	public:
		ControlComboDB();
		ControlComboDB(HWND hParent, int nIDDlgItem);
		void Clear();
		DB::Row getRow( int count );
		DB::Row getData();
		int addRow( int display, std::wstring cfmt, DB::Row row );
		~ControlComboDB();
};

