#pragma once
#include "cocos2d.h"
USING_NS_CC;

class DreamSecond : public Layer {
public:
	static DreamSecond* create(int dreamId);
	virtual bool init(int dreamId);
private:
	void confirmDream(Ref* ref);
	void closeView(Ref* ref);
};