#pragma once
#include <windows.h>
#include "Control.h"
#include <string>

class ControlCheckbox : public Control
{
	public:
		ControlCheckbox();
		ControlCheckbox(HWND hParent, int nIDDlgItem);
		operator bool() const;
		void Check();
		void UnCheck();
		~ControlCheckbox();
};

