#include "DBValue.h"
#include "shlwapi.h"
#include "ExceptionODBC.h"

DB::Value::Value() : datatype(C_NIL)
{

}

DB::DATATYPE DB::Value::getDATATYPE()
{
	return datatype;
}

DB::Value::operator bool() const
{
	if (datatype == C_NIL) throw ExceptionODBC(L"Campo vazio");
	if (datatype == C_BIT) return ( (BYTE)(*storage) == 1 ) ? true : false;
	else throw ExceptionODBC(L"Tipo incompatível 'C_BIT'");
}


DB::Value::operator std::wstring() const
{
	if (datatype == C_NIL) throw ExceptionODBC(L"Campo vazio");
	if (datatype == C_STRINGW ) return (wchar_t*)storage;
	else throw ExceptionODBC(L"Tipo incompatível 'C_STRINGW'");
}


DB::Value::operator DOUBLE()const
{
	if (datatype == C_NIL) throw ExceptionODBC(L"Campo vazio");
	if (datatype == C_DOUBLE)
	{
		DOUBLE* ret = (DOUBLE*)storage;
		return (*ret);
	}
	else throw ExceptionODBC(L"Tipo incompatível 'C_DOUBLE'");
}


DB::Value::operator LONG()const
{
	if (datatype == C_NIL) throw ExceptionODBC(L"Campo vazio");
	if (datatype == C_LONG)
	{
		LONG* ret = (LONG*)storage;
		return (*ret);
	} 
	else throw ExceptionODBC(L"Tipo incompatível 'C_LONG'");
}

DB::Value::operator TIMESTAMP_STRUCT() const
{
	if (datatype == C_NIL) throw ExceptionODBC(L"Campo está vazio");
	if (datatype == C_DATETIME)
	{
		TIMESTAMP_STRUCT* ret = (TIMESTAMP_STRUCT*)storage;
		return (*ret);
	}
	else throw ExceptionODBC(L"Tipo incompatível 'C_DATETIME'");
}


DB::Value::operator SYSTEMTIME() const
{
	if (datatype == C_NIL) throw ExceptionODBC(L"Campo vazio");
	if (datatype == C_DATETIME)
	{
		SYSTEMTIME ret;
		TIMESTAMP_STRUCT* timestamp = (TIMESTAMP_STRUCT*)storage;
		ret.wYear = timestamp->year;
		ret.wMonth = timestamp->month;
		ret.wDay = timestamp->day;
		ret.wHour = timestamp->hour; 
		ret.wMinute = timestamp->minute;
		ret.wSecond = timestamp->second;
		ret.wMilliseconds = timestamp->fraction;
		return ret; 	
	} 
	else throw ExceptionODBC(L"Tipo incompatível 'C_DATETIME'");
}


std::wstring DB::Value::format(std::wstring cfmt)
{ 
	wchar_t ret[128]; 
	switch (datatype)
	{
		case C_NIL:
		{
			return  L"";
		}

		case C_BIT:
		{
			return ( (BYTE)(*storage) == 1 ) ? L"S" : L"N";
		}
		case C_LONG:
		{
			LONG* input = (LONG*)storage;
			snwprintf( ret, SIZEOF(ret), cfmt.c_str(), (*input) );
			return ret;
		}
		case C_DOUBLE:
		{
			DOUBLE* input = (DOUBLE*)storage;
			snwprintf( ret, SIZEOF(ret) ,cfmt.c_str(), (*input) );
			return ret;
		}
		case C_DATETIME:
		{
			TIMESTAMP_STRUCT* timestamp = (TIMESTAMP_STRUCT*)storage;
			struct tm timeinfo;
			timeinfo.tm_mday = (*timestamp).day;
			timeinfo.tm_mon = ((*timestamp).month - 1);
			timeinfo.tm_year = ((*timestamp).year-1900);
			timeinfo.tm_hour = (*timestamp).hour;
			timeinfo.tm_min = (*timestamp).minute;
			timeinfo.tm_sec = (*timestamp).second;
			wcsftime(ret, SIZEOF(ret), cfmt.c_str(), &timeinfo );
			return ret;
		
		}
		case C_STRINGA:
		{
			return L"";
		}

		case C_STRINGW:
		{
			snwprintf( ret, SIZEOF(ret) ,cfmt.c_str(), (LPWSTR)&storage[0] );
			return ret;
		}

		case C_BLOB:
		{
			throw ExceptionODBC(L"format::c_blob not implemented" );
		}
	}
	return L"";
}

bool DB::Value::isEmpty()
{
	return (datatype == C_NIL) ? true : false;

}

void DB::Value::assign(SQLCHAR value)
{ 
	datatype = C_BIT;
	COPY( value , storage);
}

void DB::Value::assign(SQLCHAR* value)
{ 
	datatype = C_STRINGA;
	StrCpyA( (LPSTR)&storage, (LPSTR)value );
}

void DB::Value::assign(SQLWCHAR* value)
{ 
	datatype = C_STRINGW;
	StrCpyW( (LPWSTR)&storage, value );
}

void DB::Value::assign(SQLINTEGER value)
{ 
	datatype = C_LONG;
	COPY( value , storage);
}

void DB::Value::assign(SQLDOUBLE value)
{ 
	datatype = C_DOUBLE;
	COPY( value , storage);
}

void DB::Value::assign(TIMESTAMP_STRUCT value)
{ 
	datatype = C_DATETIME;
	COPY( value, storage );
}



void DB::Value::assign(PBYTE value, SQLINTEGER sz)
{ 
	datatype = C_BLOB;
	memcpy( storage, value , sz);
}


DB::Value::~Value()
{
}

	