#pragma once
#include "cocos2d.h"

class Dream : public cocos2d::Ref
{
public:
	static Dream* getInstance();
	void requestEvent(int dreamId);
	void recordEvent(std::string dreamId, std::string action);
	void quitGame();
	bool getDreamTimes();
	const char* getJniPath();
private:
	std::string _jniPath;
	Dream();
	static Dream* _instance;

};
