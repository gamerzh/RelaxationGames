#pragma once
#include "cocos2d.h"
#include "server/HttpMannger.h"
#include "LogEventFish.h"
#include "LogEventMagnate.h"
#include "LogEventMermaid.h"
#include "LogEventBankrupt.h"
#include "LogEventUseSkill.h"
#include "LogEventPageChange.h"
#include "LogEventSpcEvent.h"
using namespace cocos2d;


class LogEventMannger {

public:
	static LogEventMannger* getInstance();
	void init();
	void clearData(int type);
	void sendMsg();
private:
	LogEventMannger();
    
	static LogEventMannger* _instance;
};


