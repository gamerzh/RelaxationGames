#pragma once
#include "cocos2d.h"

USING_NS_CC;
class ScrollTextMannger {
public:
	static ScrollTextMannger*getInstance();
private:
	static ScrollTextMannger*_instance;
	ScrollTextMannger();
	const char* SCROLLTEXT_HEAD = "ScrollText_";
public:
	std::string getScrollTextInfo();
};

