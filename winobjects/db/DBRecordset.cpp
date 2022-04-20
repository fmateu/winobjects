#include "DBRecordset.h"
#include "ExceptionODBC.h"
#include "macros.h"


using DB::C_BIT;
using DB::C_LONG;
using DB::C_DOUBLE;
using DB::C_DATETIME;
using DB::C_STRINGA;
using DB::C_STRINGW;
using DB::C_BLOB;

DB::Recordset::Recordset()
{


}


DB::Recordset::Recordset(SQLHSTMT  hStmt) :  hStmt(hStmt), storage(1024)
{
	DEBUG( L"DB::Recordset::Recordset(SQLHSTMT) \n");
	SQLRETURN ret;
	SQLSMALLINT cCols = 0;
	ret = SQLNumResultCols(hStmt, &cCols);
	for ( SQLSMALLINT i = 1; i <= cCols; i++ )
	{
		//DEBUG(L"for\n");
		Column* aColumn =  new( storage.Get(sizeof(Column)) ) Column;
		ret = SQLDescribeCol ( hStmt, i, (SQLWCHAR*)&aColumn->ColumnName, 256, &aColumn->NameLength, &aColumn->DataType, &aColumn->ColumnSize, &aColumn->DecimalDigits, &aColumn->Nullable );
		aColumn->type	= SQLToLibMapping(aColumn->DataType);
		aColumn->c_type = SQLToCMapping(aColumn->DataType);
		Columns.insert ( std::pair<SQLSMALLINT, Column*>(i,aColumn) );	
		//DEBUG( L"index( %i ), colname('%s'), datatype( %i )\n", i, aColumn->ColumnName, aColumn->type );
	}	
}

bool DB::Recordset::MoveNext()
{
	//DEBUG( L"DB::Recordset::MoveNext\n");
	SQLRETURN ret;
	ret = SQLFetch(hStmt);
	if ( SQLSUCCESS(ret) ) return true;	
	else
	{
		SQLFreeStmt(hStmt, SQL_CLOSE);
		return false;
	}
		
}

void DB::Recordset::fillRow( DB::Row row )
{
	//DEBUG( L"DB::Recordset::fillRow\n");
	SQLRETURN ret;
	SQLSMALLINT cCols = Columns.size();

	for ( SQLSMALLINT i = 1; i <= cCols; i++ )
	{
		DEBUG(L"for\n");
		switch ( Columns[i]->type )
		{
			case C_BIT:
			{
				SQLCHAR value;
				SQLLEN cbFetched = 0;
				ret = SQLGetData(hStmt, i, SQL_C_BIT, &value, sizeof(value), &cbFetched);
				//DEBUG( L"index(%i) : column ('%s'), datatype(C_BIT), sqltype(%i), value('%i')\n", i, Columns[i]->ColumnName, Columns[i]->c_type, value);
				if ( cbFetched > 0 ) row[i].assign( value );
				break;
			}
			case C_LONG:
			{
				SQLINTEGER value;
				SQLLEN cbFetched = 0;
				ret = SQLGetData(hStmt, i, SQL_C_SLONG, &value, sizeof(value), &cbFetched);
				//DEBUG( L"index(%i) : column ('%s'), datatype(C_LONG), sqltype(%i), value('%i')\n", i, Columns[i]->ColumnName, Columns[i]->c_type, value);
				if ( cbFetched > 0 ) row[i].assign( value );
				break;
			}
			case C_DOUBLE:
			{
				SQLDOUBLE value;
				SQLLEN cbFetched = 0;
				ret = SQLGetData(hStmt, i, SQL_C_DOUBLE, &value, sizeof(value), &cbFetched);
				//DEBUG( L"index(%i) : column ('%s'), datatype(C_DOUBLE), sqltype(%i), value('%f')\n", i, Columns[i]->ColumnName, Columns[i]->c_type, value);
				if ( cbFetched > 0 ) row[i].assign( value );
				break;
			}
			case C_DATETIME:
			{
				TIMESTAMP_STRUCT value;
				SQLLEN cbFetched = 0;
				ret = SQLGetData(hStmt, i, SQL_C_TYPE_TIMESTAMP, &value, sizeof(value), &cbFetched);
				//DEBUG( L"index(%i) : column ('%s'), datatype(C_DATETIME), sqltype(%i), value('%i')\n", i, Columns[i]->ColumnName, Columns[i]->c_type, value);
				if ( cbFetched > 0 ) row[i].assign( value );
				break;
			}
			case C_STRINGA:
			{
				
				SQLCHAR value[1024];
				SQLLEN cbFetched = 0;
				ret = SQLGetData(hStmt, i, SQL_C_CHAR, &value, sizeof(value), &cbFetched);
				//DEBUG( L"index(%i) : column ('%s'), datatype(C_STRINGA), sqltype(%i), value('%i')\n", i, Columns[i]->ColumnName, Columns[i]->c_type, value);
				if ( cbFetched > 0 ) row[i].assign( value );
				break;
			}
			case C_STRINGW:
			{
				
				SQLWCHAR value[1024];
				SQLWCHAR empty[1] = {L""};
				SQLLEN cbFetched = 0;
				ret = SQLGetData(hStmt, i, SQL_WCHAR, &value, SIZEOF(value), &cbFetched);
				//DEBUG( L"index(%i) : column ('%s'), datatype(C_STRINGW), sqltype(%i), value('%i')\n", i, Columns[i]->ColumnName, Columns[i]->c_type, value);
				if ( cbFetched > 0 ) row[i].assign( value );
				break;
			}
			case C_BLOB:
			{
				PBYTE value = 0;  
				SQLINTEGER  pIndicators[2];  
				if ( SQLGetData(hStmt, i, SQL_C_BINARY, value, 0, &pIndicators[1] ) == SQL_SUCCESS_WITH_INFO )  
				{  
					value = storage.Get( pIndicators[1] );
					if (SQLGetData(hStmt, i, SQL_C_DEFAULT, value, pIndicators[1], &pIndicators[1]) == SQL_SUCCESS)  
					{  
						//DEBUG( L"index(%i) : column ('%s'), datatype(C_BLOB), sqltype(%i), value('%i')\n", i, Columns[i]->ColumnName, Columns[i]->c_type, value);
						if ( pIndicators[1] > 0 ) row[i].assign( value, pIndicators[1]);
					
					}  
				}
				break;
			}
			default:
			{
				break;
			}
		} 
	}
}


SQLSMALLINT DB::Recordset::SQLToCMapping( SQLSMALLINT SQLType )
{
	switch (SQLType)
	{
		case SQL_CHAR:
		{
			//DEBUG( L"SQL_CHAR\n");
			return SQL_CHAR;
		}
		case SQL_VARCHAR:
		{
			//DEBUG( L"SQL_VARCHAR\n");
			return SQL_VARCHAR;
		}
		case SQL_LONGVARCHAR:
		{
			//DEBUG( L"SQL_LONGVARCHAR\n");
			return SQL_LONGVARCHAR;
		}
		case SQL_WCHAR:
		{
			//DEBUG( L"SQL_WCHAR\n");
			return SQL_WCHAR;
		}
		case SQL_WVARCHAR:
		{
			//DEBUG( L"SQL_WVARCHAR\n");
			return SQL_WVARCHAR;
		}
		case SQL_WLONGVARCHAR:
		{
			//DEBUG( L"SQL_WLONGVARCHAR\n");
			return SQL_WLONGVARCHAR;
		}
		case SQL_DECIMAL:
		{
			//DEBUG( L"SQL_DECIMAL\n");
			return SQL_DECIMAL;
		}
		case SQL_NUMERIC:
		{
			//DEBUG( L"SQL_NUMERIC\n");
			return SQL_NUMERIC;
		}
		case SQL_SMALLINT:
		{
			//DEBUG( L"SQL_SMALLINT\n");
			return SQL_SMALLINT;
		}
		case SQL_INTEGER:
		{
			//DEBUG( L"SQL_INTEGER\n");
			return SQL_INTEGER;
		}
		case SQL_REAL:
		{
			//DEBUG( L"SQL_REAL\n");
			return SQL_REAL;
		}
		case SQL_FLOAT:
		{
			//DEBUG( L"SQL_FLOAT\n");
			return SQL_FLOAT;
		}
		case SQL_DOUBLE:
		{
			//DEBUG( L"SQL_DOUBLE\n");
			return SQL_DOUBLE;
		}
		case SQL_BIT:
		{
			//DEBUG( L"SQL_BIT\n");
			return SQL_BIT;
		}
		case SQL_TINYINT:
		{
			//DEBUG( L"SQL_TINYINT\n");
			return SQL_TINYINT;
		}
		case SQL_BIGINT:
		{
			//DEBUG( L"SQL_BIGINT\n");
			return SQL_BIGINT;
		}
		case SQL_BINARY:
		{
			//DEBUG( L"SQL_BINARY\n");
			return SQL_BINARY;
		}
		case SQL_VARBINARY:
		{
			//DEBUG( L"SQL_VARBINARY\n");
			return SQL_VARBINARY;
		}
		case SQL_LONGVARBINARY:
		{
			//DEBUG( L"SQL_LONGVARBINARY\n");
			return SQL_LONGVARBINARY;
		}
		case SQL_TYPE_DATE:
		{
			//DEBUG( L"SQL_TYPE_DATE\n");
			return SQL_TYPE_DATE;
		}
		case SQL_TYPE_TIME:
		{
			//DEBUG( L"SQL_TYPE_TIME\n");
			return SQL_TYPE_TIME;
		}
		case SQL_TYPE_TIMESTAMP:
		{
			//DEBUG( L"SQL_TYPE_TIMESTAMP\n");
			return SQL_TYPE_TIMESTAMP;
		}
		case SQL_INTERVAL_MONTH:
		{
			//DEBUG( L"SQL_INTERVAL_MONTH\n");
			return SQL_INTERVAL_MONTH;
		}
		case SQL_INTERVAL_YEAR:
		{
			//DEBUG( L"SQL_INTERVAL_YEAR\n");
			return SQL_INTERVAL_YEAR;
		}
		case SQL_INTERVAL_YEAR_TO_MONTH:
		{
			//DEBUG( L"SQL_INTERVAL_YEAR_TO_MONTH\n");
			return SQL_INTERVAL_YEAR_TO_MONTH;
		}
		case SQL_INTERVAL_DAY:
		{
			//DEBUG( L"SQL_INTERVAL_DAY\n");
			return SQL_INTERVAL_DAY;
		}
		case SQL_INTERVAL_HOUR:
		{
			//DEBUG( L"SQL_INTERVAL_HOUR\n");
			return SQL_INTERVAL_HOUR;
		}
		case SQL_INTERVAL_MINUTE:
		{
			//DEBUG( L"SQL_INTERVAL_MINUTE\n");
			return SQL_INTERVAL_MINUTE;
		}
		case SQL_INTERVAL_SECOND:
		{
			//DEBUG( L"SQL_INTERVAL_SECOND\n");
			return SQL_INTERVAL_SECOND;
		}
		case SQL_INTERVAL_DAY_TO_HOUR:
		{
			//DEBUG( L"SQL_INTERVAL_DAY_TO_HOUR\n");
			return SQL_INTERVAL_DAY_TO_HOUR;
		}
		case SQL_INTERVAL_DAY_TO_MINUTE:
		{
			//DEBUG( L"SQL_INTERVAL_DAY_TO_MINUTE\n");
			return SQL_INTERVAL_DAY_TO_MINUTE;
		}
		case SQL_INTERVAL_DAY_TO_SECOND:
		{
			//DEBUG( L"SQL_INTERVAL_DAY_TO_SECOND\n");
			return SQL_INTERVAL_DAY_TO_SECOND;
		}
		case SQL_INTERVAL_HOUR_TO_MINUTE:
		{
			//DEBUG( L"SQL_INTERVAL_HOUR_TO_MINUTE\n");
			return SQL_INTERVAL_HOUR_TO_MINUTE;
		}
		case SQL_INTERVAL_HOUR_TO_SECOND:
		{
			//DEBUG( L"SQL_INTERVAL_HOUR_TO_SECOND\n");
			return SQL_INTERVAL_HOUR_TO_SECOND;
		}
		case SQL_INTERVAL_MINUTE_TO_SECOND:
		{
			//DEBUG( L"SQL_INTERVAL_MINUTE_TO_SECOND\n");
			return SQL_INTERVAL_MINUTE_TO_SECOND;
		}
		case SQL_GUID:
		{
			//DEBUG( L"SQL_GUID\n");
			return SQL_GUID;
		}
		default: return 0;
	}
	return 0;
}



DB::DATATYPE DB::Recordset::SQLToLibMapping( SQLSMALLINT SQLType )
{
	switch (SQLType)
	{
		case SQL_CHAR: return C_STRINGA;
		case SQL_VARCHAR: return C_STRINGA;
		case SQL_LONGVARCHAR: return C_STRINGA;
		case SQL_WCHAR: return C_STRINGW;
		case SQL_WVARCHAR: return C_STRINGW;
		case SQL_WLONGVARCHAR: return C_STRINGW;
		case SQL_DECIMAL: return C_DOUBLE;
		case SQL_NUMERIC: return C_DOUBLE;
		case SQL_SMALLINT: return C_LONG;
		case SQL_INTEGER: return C_LONG;
		case SQL_REAL: return C_DOUBLE;
		case SQL_FLOAT: return C_DOUBLE;
		case SQL_DOUBLE: return C_DOUBLE;
		case SQL_BIT: return C_BIT;
		case SQL_TINYINT: return C_LONG;
		case SQL_BIGINT: return C_LONG;
		case SQL_BINARY: return C_LONG;
		case SQL_VARBINARY: return C_BLOB;
		case SQL_LONGVARBINARY: return C_BLOB;
		case SQL_TYPE_DATE: return C_DATETIME;
		case SQL_TYPE_TIME: return C_DATETIME;
		case SQL_TYPE_TIMESTAMP: return C_DATETIME;
		case SQL_INTERVAL_MONTH: return C_LONG;
		case SQL_INTERVAL_YEAR: return C_LONG;
		case SQL_INTERVAL_YEAR_TO_MONTH: return C_LONG;
		case SQL_INTERVAL_DAY: return C_LONG;
		case SQL_INTERVAL_HOUR: return C_LONG;
		case SQL_INTERVAL_MINUTE: return C_LONG;
		case SQL_INTERVAL_SECOND: return C_LONG;
		case SQL_INTERVAL_DAY_TO_HOUR: return C_LONG;
		case SQL_INTERVAL_DAY_TO_MINUTE: return C_LONG;
		case SQL_INTERVAL_DAY_TO_SECOND: return C_LONG;
		case SQL_INTERVAL_HOUR_TO_MINUTE: return C_LONG;
		case SQL_INTERVAL_HOUR_TO_SECOND: return C_LONG;
		case SQL_INTERVAL_MINUTE_TO_SECOND: return C_LONG;
		case SQL_GUID: return C_STRINGA;
		default: return C_NIL;
	}
	return C_NIL;
}

DB::Recordset::~Recordset()
{

}
