#include <cstdio>
#include <ctime>
#include <iostream>
#include <regex>
#include "BaseDateTime.h"
#include "macros.h"

using namespace std;


BASE::DateTime::DateTime()
{
	time( &_time );
}



BASE::DateTime::DateTime( time_t value ) : _time(value)
{

}

BASE::DateTime::DateTime(int yr, int mon, int day, int hr, int mn, int sc)
{
    
	struct tm timeinfo;
	timeinfo.tm_mday = day;
	timeinfo.tm_mon = (mon - 1);
	timeinfo.tm_year = (yr-1900);
	timeinfo.tm_hour = hr;
	timeinfo.tm_min = mn;
	timeinfo.tm_sec = sc;
	_time = mktime ( &timeinfo );	
}

BASE::DateTime::DateTime( TIMESTAMP_STRUCT timestamp )
{
	struct tm timeinfo;
	timeinfo.tm_mday = timestamp.day;
	timeinfo.tm_mon = (timestamp.month - 1);
	timeinfo.tm_year = (timestamp.year-1900);
	timeinfo.tm_hour = timestamp.hour;
	timeinfo.tm_min = timestamp.minute;
	timeinfo.tm_sec = timestamp.second;
	_time = mktime ( &timeinfo );	
}

BASE::DateTime::DateTime( SYSTEMTIME systime )
{
	struct tm timeinfo;
	timeinfo.tm_mday = systime.wDay;
	timeinfo.tm_mon = (systime.wMonth - 1);
	timeinfo.tm_year = (systime.wYear-1900);
	timeinfo.tm_hour = systime.wHour;
	timeinfo.tm_min = systime.wMinute;
	timeinfo.tm_sec = systime.wSecond;
	_time = mktime ( &timeinfo );	
}


BASE::DateTime::operator SYSTEMTIME() const
{
	struct tm* timeinfo;
	timeinfo = localtime( &_time );
	SYSTEMTIME ret;
	ret.wDay	= timeinfo->tm_mday ;
	ret.wMonth	= timeinfo->tm_mon + 1;
	ret.wYear	= timeinfo->tm_year+1900 ;
	ret.wHour	= timeinfo->tm_hour ;
	ret.wMinute	= timeinfo->tm_min ;
	ret.wSecond	= timeinfo->tm_sec ;
	ret.wMilliseconds = 0;
	return ret;
}

BASE::DateTime::operator TIMESTAMP_STRUCT() const
{
	struct tm* timeinfo;
	timeinfo = localtime( &_time );
	TIMESTAMP_STRUCT ret;
	ret.day		=  timeinfo->tm_mday;
	ret.month	= timeinfo->tm_mon + 1;
	ret.year	= timeinfo->tm_year+1900;
	ret.hour	= timeinfo->tm_hour;
	ret.minute	= timeinfo->tm_min;
	ret.second	= timeinfo->tm_sec;
	ret.fraction = 0;
	return ret;
}

 std::wstring BASE::DateTime::format( std::wstring fmt )
{
	wchar_t buffer[80];
	struct tm *timeinfo;
	timeinfo = localtime( &_time );
	wcsftime(buffer, SIZEOF(buffer), fmt.c_str(), timeinfo );
	return buffer;
}


 bool BASE::DateTime::operator > (DateTime const &another)
{ 
	return ( _time > another._time );
} 

bool BASE::DateTime::operator >= (DateTime const &another)
{ 
	return ( _time >= another._time );
} 

bool BASE::DateTime::operator < (DateTime const &another)
{ 
	return ( _time < another._time );
} 

bool BASE::DateTime::operator <= (DateTime const &another)
{ 
	return ( _time <= another._time );
} 

bool BASE::DateTime::operator == (DateTime const &another)
{ 
	return ( _time == another._time );
} 

BASE::DateTime::~DateTime()
{

}