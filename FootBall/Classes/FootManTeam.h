#pragma once
#include "cocos2d.h"
#include "FootMan.h"


class FootManTeam : public cocos2d::Ref {
public:
	static FootManTeam* create();
	virtual bool init();
private:
	std::vector<FootMan*> footManVec;
};