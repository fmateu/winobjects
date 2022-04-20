#include "macros.h"
#include "DBConnection.h"
#include "ExceptionODBC.h"

DB::Connection::Connection()
{

}

DB::Connection::Connection(std::wstring connstr)
{
	SQLRETURN ret;
	SQLWCHAR _out[1024];
    SQLSMALLINT _cbOut;


	SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hEnv);
	SQLSetEnvAttr(hEnv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC,hEnv,&hDbc);
	ret=SQLDriverConnect(hDbc,NULL,(SQLWCHAR *)connstr.c_str(),connstr.length(),_out, 1024,&_cbOut, SQL_DRIVER_NOPROMPT);

	if (!SQLSUCCESS(ret)) 
	{
		int i=1;
		SQLWCHAR SqlState[6], msg[255];
		SQLINTEGER NativeError;
		SQLSMALLINT msglen;
		std::wstring error_details;

		wchar_t buffer[1024];

		while ( SQLGetDiagRec(SQL_HANDLE_DBC, hDbc, i, SqlState, &NativeError, msg, SIZEOF(msg), &msglen)!= SQL_NO_DATA )
		{
				snwprintf(buffer,SIZEOF(buffer),L"%s\n",msg);
				error_details.append(buffer);
				i++;
		}
		throw ExceptionODBC(error_details);
	}
	
	ret = SQLAllocHandle(SQL_HANDLE_STMT,hDbc,&hStmt);
	if (!SQLSUCCESS(ret)) throw ExceptionODBC( L"SQLAllocHandle failed" );
}



SQLHSTMT DB::Connection::Execute(std::wstring sqlcmd)
{
	DEBUG(L"DB::Connection::Execute('%s')\n",sqlcmd.c_str());
	SQLRETURN ret;							
	ret=SQLExecDirect(hStmt,(SQLWCHAR*)sqlcmd.c_str(), sqlcmd.length());
	if (SQLSUCCESS(ret)) return hStmt;
	else
	{
		int i=1;
		SQLINTEGER NativeError;
		SQLWCHAR SqlState[6], msg[255];
		SQLSMALLINT msglen;
		std::wstring error;
		wchar_t buffer[256];
		while ( SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, i, SqlState, &NativeError, msg, SIZEOF(msg), &msglen) != SQL_NO_DATA )
		{
			snwprintf(buffer,SIZEOF(buffer),L"%s\n",(LPCTSTR)msg);
			error.append(buffer);
			i++;
		}
		throw ExceptionODBC(error);
	}
}

SQLHSTMT DB::Connection::ExecQuery(std::wstring sqlcmd)
{
	return Execute(sqlcmd);
}

void DB::Connection::ExecStatement(std::wstring sqlcmd)
{
		Execute(sqlcmd);
}


DB::Connection::~Connection()
{
	if (hStmt)	SQLFreeHandle(SQL_HANDLE_STMT,hStmt);
	if (hDbc)	SQLDisconnect(hDbc);
	if (hDbc)	SQLFreeHandle(SQL_HANDLE_DBC,hDbc);
	if (hEnv)	SQLFreeHandle(SQL_HANDLE_ENV,hEnv);
}
