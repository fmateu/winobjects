#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include <map>
#include "BaseMemory.h"
#include "DBDataType.h"
#include "DBRow.h"


namespace DB
{
	class Recordset
	{
		private:
			SQLHSTMT  hStmt;
			struct Column
			{
				char ColumnName[256];
				SQLSMALLINT NameLength;
				SQLSMALLINT DataType;
				SQLUINTEGER	ColumnSize;
				SQLSMALLINT	DecimalDigits;
				SQLSMALLINT	Nullable;
				SQLSMALLINT c_type;
				DATATYPE type;
			};
			std::map< SQLSMALLINT, Column* > Columns;
			BASE::Memory storage;
			DATATYPE SQLToLibMapping( SQLSMALLINT SQLType );
			SQLSMALLINT SQLToCMapping( SQLSMALLINT SQLType );
		public:
			Recordset();
			Recordset(SQLHSTMT  hStmt);
			void fillRow( DB::Row row );
			bool MoveNext();
			~Recordset();

	};
}
