#pragma once
#include <windows.h>
#include <commctrl.h>
#include <string>
#include "Control.h"

class ControlDateTimePicker : public Control
{
	public:
		ControlDateTimePicker();
		ControlDateTimePicker(HWND hParent, int nIDDlgItem);
		std::wstring format( std::wstring fmt );
		bool isEmpty();
		void Clear();
		operator SYSTEMTIME() const;
		void setDate( SYSTEMTIME date );
		~ControlDateTimePicker();
};

