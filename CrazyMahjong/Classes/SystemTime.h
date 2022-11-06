#pragma once
#include "cocos2d.h"

class SystemTime
{
public:
	SystemTime(const std::string &formatString);
	~SystemTime();

	int getYear() const;
	int getMonth() const;
	int getDay() const;
	static SystemTime*getToday();
	const std::string& getFormatString() const;
	static int diffDayByAandB(SystemTime*dayA, SystemTime*dayB);
private:
	DISALLOW_COPY_AND_ASSIGN(SystemTime);
private:
	int _year;
	int _month;
	int _day;
	std::string _formatString;
	///日期B与日期A间隔多少天,日期B-日期A
private:
	//utill
	
	static int getDayBymonthandyear(int year, int month);
	static int getDayByyear(int year);

	static int getday(int year, int month, int day);//算出谋一年的天数；
	static long getyearday(int year, int month, int day);//算出某一年到 元年 元月 元日 的天数；

	
};
