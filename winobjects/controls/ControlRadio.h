#pragma once
#include <windows.h>
#include "Control.h"

class ControlRadio : public Control
{
	public:
		ControlRadio();
		ControlRadio(HWND hParent, int nIDDlgItem);
		~ControlRadio();
};

