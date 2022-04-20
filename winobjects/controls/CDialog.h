#pragma once
#include <windows.h>
#include <map>
#include "Control.h"


class CDialog
{
	private:
		HWND _hwnd;
		int _itemid; 
		std::map<UINT,Control*> items;
	public:
		CDialog();	
		CDialog ( int nIDDlgItem, HWND hParent, DLGPROC DialogProc );
		void addItem(Control* cl);
		Control* getItem(UINT it);
		void Show();
		void Hide();
		void SetFocus();
		bool hasFocus();
		operator UINT() const;
		operator HWND() const;
		~CDialog();
};