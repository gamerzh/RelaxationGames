#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Jniutill{
public:
	void showMoreGame();
	
	void quit();
	static Jniutill* getInstance();
	void requestEvent(int eventId);
	void queryOrder();
	void getUipointByEventpoint(int eventid);
	const char* getJniPath();
	void doPay(int paypoint);
	//活动
	bool IsHdOpen();
	void showHdDialog();
	std::string JniGetHDname();
	//签到
	bool isSignToday();
	bool notSignToday();
	int getCurrentSignDayas();
	void sign();

	//统计
	void logEvent(std::string eventName, std::string  tag = "");
	std::string getImei();
	void logEventShowPayPanel(int paypoint, int state);
private:
	std::string _jniPath;
	Jniutill();
	static Jniutill* _instance;
};

