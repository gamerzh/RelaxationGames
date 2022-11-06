#include "dayUtil.h"

#include "network/HttpRequest.h"

#include <cstdio>

USING_NS_CC;
using namespace network;
using namespace std;



SystemTime::SystemTime(const string &formatString)
{
	// Format: 2015-08-19 17:51:36
	int num = sscanf(formatString.c_str(), "%d-%d-%d",
		&_year, &_month, &_day);

	_formatString = formatString;
}

SystemTime::~SystemTime()
{
}
int SystemTime::getYear() const
{
	return _year;
}

int SystemTime::getMonth() const
{
	return _month;
}

int SystemTime::getDay() const
{
	return _day;
}

const std::string& SystemTime::getFormatString() const
{
	return _formatString;
}

bool SystemTime::isContinuousByAandB(SystemTime*dayA, SystemTime*dayB)
{
	///同年
    if (dayB->getYear() == dayB->getYear())
    {
		///同月
		if (dayA->getMonth()==dayB->getMonth())
		{
			if (dayB->getDay()-dayA->getDay() == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//不同月
		else
		{
			//上下月
			if (dayB->getMonth()-dayA->getMonth()==1)
			{
				if (dayB->getDay()+getDayBymonthandyear(dayA->getYear(),dayA->getMonth())-dayA->getDay()==1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
    }
	//不同年
	else
	{
		//上下年
		if (dayB->getYear() - dayA->getYear() == 1)
		{
			if (dayB->getDay() + getDayByyear(dayA->getYear()) - dayA->getDay() == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}



int SystemTime::diffDayByAandB(SystemTime*dayA, SystemTime*dayB)
{
	int day1 = getyearday(dayA->getYear(), dayA->getMonth(), dayA->getDay());
	int day2 = getyearday(dayB->getYear(), dayB->getMonth(), dayB->getDay());
	return day2 - day1;
}

SystemTime*SystemTime::getToday()
{
	struct tm *ptm;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	struct timeval now;
	gettimeofday(&now, NULL);
	ptm = localtime(&now.tv_sec);
#endif

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	time_t timep;
	time(&timep);
	ptm = localtime(&timep);
#endif

	// Format: 2015-08-19 17:51:36
	char buffer[128] = { 0 };
	sprintf(buffer, "%d-%02d-%02d %02d:%02d:%02d",
		ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday,
		ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	SystemTime* today = new SystemTime(buffer);
	return today;
}


SystemTime*SystemTime::getdaytime()
{
	struct tm *ptm;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	struct timeval now;
	gettimeofday(&now, NULL);
	ptm = localtime(&now.tv_sec);
#endif

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	time_t timep;
	time(&timep);
	ptm = localtime(&timep);
#endif

	// Format: 2015-08-19 17:51:36
	char buffer[128] = { 0 };
	sprintf(buffer, "%d-%02d-%02d",
		ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday);
	CCLOG("%s", buffer);
	SystemTime* today = new SystemTime(buffer);
	return today;
}
int SystemTime::getNowHour()
{
	struct tm *ptm;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	struct timeval now;
	gettimeofday(&now, NULL);
	ptm = localtime(&now.tv_sec);
#endif

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	time_t timep;
	time(&timep);
	ptm = localtime(&timep);
#endif

  
	return ptm->tm_hour;
}
int getDayBymonthandyear(int year, int month)
{
	switch (month)
	{
	case 1:
	case 5:
	case 3:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
		break;
	case 2:
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		{
			return 29;
		}
		else
		{
			return 28;
		}
	default:
		return -1;
		break;
	}
}

int getDayByyear(int year)
{
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
	{
		return 366;
	}
	else
	{
		return 365;
	}
}


int getday(int year, int month, int day){

	int days[2][13] = { { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } };//1wei run nian;
	int sum = day;
	int flag = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0 ? 1 : 0;
	for (int i = 0; i < month; i++)
		sum += days[flag][i];

	return sum;

}


long getyearday(int year, int month, int day){
	long sumallday = 0;//作为返回值；
	long sumyearday = 0;//很多年的天数；
	long sumday = 0;//一年中的天数；
	for (int i = 1; i < year; i++)
		sumyearday += getday(i, 12, 31);
	sumday = getday(year, month, day);
	sumallday = sumyearday + sumday;

	return sumallday;

}