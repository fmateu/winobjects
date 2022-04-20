#pragma once
#include <windows.h>
#include <string>
#include <map>
#include "Control.h"
#include "CDialog.h"


class ControlTab : public Control
{
	private:
		std::map<UINT,CDialog*> _tabs;
		std::map<UINT,CDialog*> _dialogs;
	public:
		ControlTab();
		ControlTab(HWND hParent, UINT nIDDlgItem);
		CDialog* getDialog(UINT dlg);
		void addTab(std::wstring caption, CDialog* dlg);
		void showTab(UINT tab);
		~ControlTab();
};

