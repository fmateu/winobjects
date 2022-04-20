#pragma once
#include <windows.h>
#include "Control.h"
#include "CDialog.h"
#include <windows.h>
#include <commctrl.h>

class ControlToolBar : public Control
{
	protected:
		std::map<UINT,CDialog*> _dialogs;
	public:
		ControlToolBar();
		ControlToolBar(HWND hParent, int nIDDlgItem);
		void setimagelist( HIMAGELIST imglist );
		void addbuttons( int num, TBBUTTON buttons[]);
		void autosize();
		void adddialog(CDialog* dlg);
		CDialog* getdialog(int cmd);
		void showtab(int cmd);
		~ControlToolBar();
};

