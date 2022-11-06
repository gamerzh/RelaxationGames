#include "DebugTasterTime.h"

USING_NS_CC;
DebugTime* DebugTime::instance = nullptr;

DebugTime* DebugTime::getInstance()
{
	if (!instance)
		instance = new DebugTime();
	return instance;
}

DebugTime::DebugTime() {

}

long DebugTime::getCurrentTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void DebugTime::LogTasterTime(std::string logtag)
{
	//auto size = Director::getInstance()->getVisibleSize();
	//static float i = 0.1;
	//auto str = String::createWithFormat((logtag + ":%ld").c_str(), getCurrentTime() - lasttime);
	//auto labeltime = LabelTTF::create(str->getCString(), "Arial", 28);
	//labeltime->setPosition(size.width*0.9, size.height*i);
	//parents->addChild(labeltime);
	//i = i + 0.1;
	log((logtag + ":%ld").c_str(), getCurrentTime() - lasttime);
	setBeginTime();
}

void DebugTime::setBeginTime()
{
	lasttime = getCurrentTime();
}

long DebugTime::getTasterTime()
{
	long time = getCurrentTime() - lasttime;
	setBeginTime();
	return time;
}

long DebugTime::getTasterTimeNoInit()
{
	long time = getCurrentTime() - lasttime;
	return time;
}

void DebugTime::setGameBeginTime()
{
	begintime = getCurrentTime();
}

long DebugTime::getGameTaserTime()
{
	return getCurrentTime() - begintime;
}

void DebugTime::pauseGameTime()
{
	
	pausetime = getCurrentTime();
	log("pausetime %ld", pausetime);
}
void DebugTime::ResumGameTime()
{
	log("resumtime1 %ld", begintime);
	begintime +=(getCurrentTime()-pausetime);
	log("resumtime2 %ld", begintime);
}
