#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;



class ConfigManager {
    
public:
	ConfigManager();
	static ConfigManager* getInstance();
    
	void LoadConfig();

	bool isDebugConfig(){ return true; };
private:
	static ConfigManager* _instance;
};

