#pragma once
//Ö§¸¶·½·¨
#include "cocos2d.h"
USING_NS_CC;

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