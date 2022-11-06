#pragma once

#include "cocos2d.h"
USING_NS_CC;

/************************************************************************/
/* 数据库管理单例类                                                     */
/************************************************************************/

class DBManager
{


public:
	static DBManager* GetInstance();
	~DBManager(void);

	
public:	//音量设置

	//获取背景音乐音量
	float GetBgmVolume();

	//设置背景音乐音量
	void SetBgmVolume(float volume);


public:
	int GetDayGameTimes();
	void AddDayGameTimes();
	void initDayGameTimes();

public:	//计费点相关
	CC_SYNTHESIZE(int, _longLineEventCount, LongLineEventCount);

	//活动

	CC_SYNTHESIZE(std::string, HDname, HDNAME);
	bool  getISTaskSuccess();
private:
	DBManager(void);

};

