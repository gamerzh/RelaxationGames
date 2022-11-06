#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;


class PayEventPointConfig {

public:
	PayEventPointConfig();
	static PayEventPointConfig* getInstance();

	bool LoadConfig();
	int getPayeventVersion(){ return version; };
	
private:
	static PayEventPointConfig* _instance;
	int version;

};

