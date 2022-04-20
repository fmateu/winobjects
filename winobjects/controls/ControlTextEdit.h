#pragma once
#include <string>
#include "Control.h"

class ControlTextEdit : public Control
{
	public:
		ControlTextEdit();	
		ControlTextEdit(HWND hParent, int nIDDlgItem);
		void setText( std::wstring str );
		void setText( LONG num );
		void setText( DOUBLE num );
		bool isEmpty();
		int getTextLength( );
		void Clear( );
		std::wstring to_sql();
		std::wstring getText();
		~ControlTextEdit(  );
};

