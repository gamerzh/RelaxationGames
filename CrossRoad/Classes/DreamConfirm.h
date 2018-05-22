#pragma once
#include "cocos2d.h"
USING_NS_CC;

class DreamConfirm : public Node {
public:
	static DreamConfirm* create(int dreamId, Vec2 pos);
	virtual bool init(int dreamId, Vec2 pos);
private:
	int dream_id = 0;
	void confirmDream();
};