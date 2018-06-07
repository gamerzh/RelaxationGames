#pragma once
#include "cocos2d.h"
USING_NS_CC;

#define SHARPNESS_VERSION 1//0正常版本,1特殊清晰版本

class DreamNode : public Node {
public:
	static DreamNode* create(int dreamId,Vec2 pos);
	virtual bool init(int dreamId, Vec2 pos);
private:
	bool isHavePride = false;
	Vec2 position;
	CC_SYNTHESIZE(int,dreamId,DreamId);
	std::string getContentById(int dreamId);
	std::string getButtonById(int dreamId);
	void doActionById();
	void closeView();
	void startPride();
};