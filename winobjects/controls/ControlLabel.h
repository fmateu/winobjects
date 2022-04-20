#pragma once
#include "Control.h"

class ControlLabel : public Control
{
	public:
		ControlLabel();	
		ControlLabel(HWND hParent, int nIDDlgItem);
		~ControlLabel(  );
};

