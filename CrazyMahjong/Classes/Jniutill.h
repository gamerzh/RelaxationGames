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
	//�
	bool IsHdOpen();
	void showHdDialog();
	std::string JniGetHDname();
	//ǩ��
	bool isSignToday();
	bool notSignToday();
	int getCurrentSignDayas();
	void sign();

	//ͳ��
	void logEvent(std::string eventName, std::string  tag = "");
	std::string getImei();
	void logEventShowPayPanel(int paypoint, int state);
private:
	std::string _jniPath;
	Jniutill();
	static Jniutill* _instance;
};

