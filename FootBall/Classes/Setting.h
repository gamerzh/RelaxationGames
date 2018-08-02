#pragma once
#include "cocos2d.h"

class Setting :public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(Setting);
private:
	cocos2d::MenuItemToggle * musicItemToggle;
	int gameTime;
	float passTime = 0;
	const float timestep = 1.0f;
	void loadView();
	void soundMenuCallBack(Ref* ref);
	void pauseGame();
	void update(float dt);
};
