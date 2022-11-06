#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class DeviceInfo{
public:
	static const char* getImei();
	static std::string getChannel_id();
	static const char*  getHd_type();
	static const char*  getHd_factory();
	static int getVesion();

};

