#pragma once
#include <windows.h>
#include "DBDataType.h"
#pragma once
#include "ExceptionApp.h"
#include "macros.h"
#include <ctime>
#include <string>
#include <sql.h>

namespace DB
{
	class Value
	{
		private:
			DATATYPE datatype;
			BYTE storage[256];
		public:
			Value();
			void assign(SQLCHAR* value);
			void assign(SQLWCHAR* value);
			void assign(SQLCHAR value);
			void assign(SQLINTEGER value);
			void assign(SQLDOUBLE value);
			void assign(TIMESTAMP_STRUCT value);
			void assign(PBYTE value, SQLINTEGER sz);
			std::wstring format(std::wstring cfmt);
			DATATYPE getDATATYPE();
			bool isEmpty();
			operator SYSTEMTIME() const;
			operator TIMESTAMP_STRUCT() const;
			operator std::wstring() const;
			operator bool() const;
			operator LONG()const;
			operator DOUBLE()const;

			~Value();
	};
}