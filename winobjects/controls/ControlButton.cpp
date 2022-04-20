
#include "ControlButton.h"

ControlButton::ControlButton(  )
{

}

ControlButton::ControlButton(HWND hParent, int nIDDlgItem ) : Control(hParent, nIDDlgItem)
{



}

ControlButton::ControlButton(HWND hParent, int nIDDlgItem, COLORREF bgcolor, COLORREF txtcolor, int height, std::wstring txt ) : Control(hParent, nIDDlgItem)
{
	RECT rc; 
	HFONT hFont,hOldFont; 
	GetClientRect(_hwnd,&rc);
	HDC hDC = GetDC(_hwnd);
	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rc.right, rc.bottom);
	SelectObject(hMemDC, hBitmap);
	SetDCBrushColor(hMemDC, bgcolor);
	FillRect(hMemDC, &rc, (HBRUSH)GetStockObject(DC_BRUSH));
	SetBkColor(hMemDC,bgcolor);
	SetTextColor(hMemDC,txtcolor);
	hFont = CreateFont(height, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Ms Shell Dlg");
	if (hOldFont = (HFONT)SelectObject(hMemDC, hFont)) 
	{
		// Display the text string.  
		DrawText( hMemDC, txt.c_str(), txt.length(), &rc, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		// Restore the original font.        
		SelectObject(hMemDC, hOldFont); 
	}

	
	DeleteDC(hMemDC);
	ReleaseDC(_hwnd, hDC);
	SendMessage(_hwnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
}


ControlButton::~ControlButton(  )
{

}