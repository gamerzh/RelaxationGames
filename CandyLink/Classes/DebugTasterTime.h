#pragma once
#include "cocos2d.h"

class  DebugTime 
{
public:
	static DebugTime* getInstance();
	void LogTasterTime(std::string logtag);
	long getCurrentTime();
	void setBeginTime();
	long getTasterTime();
	long getTasterTimeNoInit();

	//GAME
	void setGameBeginTime();
	long getGameTaserTime();
	void pauseGameTime();
	void ResumGameTime();
private:
   static DebugTime* instance;
	DebugTime();
	long lasttime;
	long begintime;
	long pausetime;
};



