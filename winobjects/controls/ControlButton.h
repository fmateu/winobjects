#pragma once
#include <windows.h>
#include <string>
#include "Control.h"

class ControlButton : public Control
{
	public:
		ControlButton();
		ControlButton(HWND hParent, int nIDDlgItem );
		ControlButton(HWND hParent, int nIDDlgItem, COLORREF bgcolor, COLORREF txtcolor, int height, std::wstring txt );
		~ControlButton();
};

