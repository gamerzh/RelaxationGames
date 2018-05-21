#pragma once
#include "cocos2d.h"
USING_NS_CC;

class DreamNode : public Node {
public:
	static DreamNode* create(int dreamId,Vec2 pos);
	virtual bool init(int dreamId, Vec2 pos);
private:
	CC_SYNTHESIZE(int,dreamId,DreamId);
	std::string getContentById(int dreamId);
	std::string getButtonById(int dreamId);
	void doActionById();
	void closeView();
};