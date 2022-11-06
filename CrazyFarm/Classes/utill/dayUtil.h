#pragma once
#include "cocos2d.h"

class SystemTime
{
public:
	SystemTime(const std::string &formatString);
	~SystemTime();
	//////B为今天，A为上次签到日期
	static bool isContinuousByAandB(SystemTime*dayA, SystemTime*dayB);
	///日期B与日期A间隔多少天,日期B-日期A
	static int diffDayByAandB(SystemTime*dayA, SystemTime*dayB);
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	static SystemTime*getToday();
	static SystemTime*getdaytime();
	static int getNowHour();
	const std::string& getFormatString() const;

private:
	DISALLOW_COPY_AND_ASSIGN(SystemTime);
private:
	int _year;
	int _month;
	int _day;


	std::string _formatString;
};
int getDayBymonthandyear(int year, int month);
int getDayByyear(int year);

int getday(int year, int month, int day);//算出谋一年的天数；
long getyearday(int year, int month, int day);//算出某一年到 元年 元月 元日 的天数；