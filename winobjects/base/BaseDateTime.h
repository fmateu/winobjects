#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <ctime>
#include <string>

namespace BASE
{
	class DateTime
	{
		private:
			time_t _time;
		public:
			DateTime();
			DateTime(time_t value );
			DateTime(int yr, int mon, int day, int hr, int mn, int sc);
			DateTime( TIMESTAMP_STRUCT timestamp );
			DateTime( SYSTEMTIME systime );
			std::wstring format( std::wstring fmt );
			operator SYSTEMTIME() const;
			operator TIMESTAMP_STRUCT() const;
			bool operator > (DateTime const &another);
			bool operator >= (DateTime const &another);
			bool operator < (DateTime const &another);
			bool operator <= (DateTime const &another);
			bool operator == (DateTime const &another);
			~DateTime();
	};

}