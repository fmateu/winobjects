#pragma once
#include <windows.h>

class Control
{
	
	protected:
		HWND _hwnd;
		int _itemid; 
	public:
		Control();	
		Control (HWND hParent, UINT nIDDlgItem);
		~Control();
		operator HWND() const;
		operator UINT() const;
		bool hasFocus();
		void SetFocus();
		void Enable();
		void Disable();
		void Show();
		void Hide();
};