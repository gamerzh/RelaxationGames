#pragma once
//支付方法
#include "cocos2d.h"
USING_NS_CC;

#define GOV_CHECK_VERSION  1 //正常版本1,审核版本0

class Dream : public Ref
{
public:
	static Dream* getInstance();
	void requestEvent(int dreamId);
	void recordEvent(std::string dreamId, std::string action);
	void quitGame();
	const char* getJniPath();
private:
	std::string _jniPath;
	Dream();
	static Dream* _instance;

};