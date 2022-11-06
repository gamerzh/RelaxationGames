#pragma once
#include "cocos2d.h"

class SystemTime
{
public:
	SystemTime(const std::string &formatString);
	~SystemTime();
	//////BΪ���죬AΪ�ϴ�ǩ������
	static bool isContinuousByAandB(SystemTime*dayA, SystemTime*dayB);
	///����B������A���������,����B-����A
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

int getday(int year, int month, int day);//���ıһ���������
long getyearday(int year, int month, int day);//���ĳһ�굽 Ԫ�� Ԫ�� Ԫ�� ��������