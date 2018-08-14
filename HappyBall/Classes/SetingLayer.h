#pragma once
#include "cocos2d.h"

class SetingLayer : public cocos2d::Layer {
public:
	static SetingLayer* create(int style);
	virtual bool init(int style);
	void updateHeroSkin();
private:
	cocos2d::MenuItemToggle * musicItemToggle;
	void showSkinLayer();
	void showPauseLayer();
	void soundMenuCallBack(cocos2d::Ref* ref);
	void update(float dt);
};