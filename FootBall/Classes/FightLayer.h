#pragma once
#include "cocos2d.h"

/*
	球队选择界面
*/
class FightLayer : public cocos2d::Layer {
public:
	//static FightLayer* create();
	virtual bool init();
	CREATE_FUNC(FightLayer);
	void setMenuCallback(const cocos2d::ccMenuCallback& back);
private:
	cocos2d::MenuItemImage* img;
};