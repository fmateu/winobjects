#pragma once
#include <windows.h>
#include "Control.h"

class ControlCombo : public Control
{
	public:
		ControlCombo();
		ControlCombo(HWND hParent, int nIDDlgItem);
		void setSelected(int index);
		int getSelected();
		int getCount();
		virtual void Clear();
		void Reset();
		~ControlCombo();
};

