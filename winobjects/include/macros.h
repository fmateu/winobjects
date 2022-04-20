#pragma once
#include <cstdio>

//functor section
#ifdef TRACE
	#define DEBUG(...) wprintf( __VA_ARGS__)
#else
	#define DEBUG(...)
#endif

#define SQLSUCCESS(ret) (ret == SQL_SUCCESS) || (ret == SQL_SUCCESS_WITH_INFO)
#define COPY(src, target) memcpy( &target, &src, sizeof(src) )
#define _T(ch) (LPCTSTR)ch
//define _W(ch) (LPWSTR)ch
#define SIZEOF(wch) sizeof(wch)/sizeof(wch[0])
//message section
#define WM_APP_DIALOGREADY ( WM_APP + 1 )
#define ALERT( titulo, descr )	MessageBox( NULL, descr, titulo, MB_ICONEXCLAMATION );
#define RCWIDTH(x) x.right-x.left
#define RCHEIGHT(x) x.bottom-x.top
#define snwprintf _snwprintf