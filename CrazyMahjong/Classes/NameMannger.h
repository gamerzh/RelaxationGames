#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class NameMannger{
public:
	static std::string getName();
private:
	static std::vector < std::string > nameCache;
	static void loadName();
};

	