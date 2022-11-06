#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;


class ConfigDebugTest {
    
public:
	ConfigDebugTest();
	static ConfigDebugTest* getInstance();
	bool LoadConfig();
private:
	static ConfigDebugTest* _instance;

};

