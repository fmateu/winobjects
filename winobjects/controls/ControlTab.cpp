#include "ControlTab.h"
#include "ExceptionWindows.h"
#include "macros.h"


ControlTab::ControlTab()
{
	DEBUG( L"ControlTab::ControlTab()\n");
}

ControlTab::ControlTab(HWND hParent, UINT nIDDlgItem) : Control(hParent, nIDDlgItem)
{
	DEBUG( L"ControlTab::ControlTab(HWND '%i', UINT '%i' )\n", hParent, nIDDlgItem);
}


CDialog* ControlTab::getDialog(UINT dlg)
{
	DEBUG( L"ControlTab::getDialog( %i )\n",dlg);
	return _dialogs[dlg];
}

void ControlTab::addTab(std::wstring caption, CDialog* dlg)
{
	DEBUG( L"ControlTab::addTab(std::wstring, CDialog*)\n");
	TCITEM tcitem = {0};
	tcitem.mask = TCIF_TEXT;
	tcitem.pszText = &caption[0];
	UINT tbcode;
	if (( tbcode = TabCtrl_InsertItem(_hwnd, _tabs.size(), &tcitem)) == -1) throw ExceptionWindows(GetLastError());
	_tabs.insert( std::pair<UINT,CDialog*>(tbcode,dlg) );
	DEBUG( L"(UINT)(*dlg)( %i )\n", (UINT)(*dlg));
	_dialogs.insert( std::pair<UINT,CDialog*>((UINT)(*dlg),dlg) );


}

void ControlTab::showTab(UINT tab)
{
	DEBUG( L"ControlTab::showTab( %i )\n",tab);
	for ( auto it : _tabs )
	{
		it.second->Hide();
	}
	_tabs[tab]->Show();
}


ControlTab::~ControlTab(  )
{
	DEBUG( L"ControlTab::~ControlTab\n");
}