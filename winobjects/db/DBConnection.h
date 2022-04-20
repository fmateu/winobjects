#pragma once
#include <windows.h>
#include <string>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

namespace DB
{
	class Connection
	{
		private:
			SQLHENV hEnv;							
			SQLHDBC hDbc;							
			SQLINTEGER AffectCount;					
			SQLHSTMT hStmt;							
			SQLSMALLINT nCol;						
			SQLHSTMT Execute(std::wstring sqlcmd);
		public:
			Connection();								
			Connection(std::wstring connstr);								
			~Connection();								
			SQLHSTMT ExecQuery(std::wstring sqlcmd);
			void ExecStatement(std::wstring sqlcmd);
	};
}