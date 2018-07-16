#pragma once
#include "cocos2d.h"

class Setting :public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(Setting);
private:
	cocos2d::MenuItemToggle * musicItemToggle;
	float gameTime = 90;
	float passTime = 0;
	const float timestep = 0.1f;
	void loadView();
	void showTeamScore(int teamId);
	void soundMenuCallBack(Ref* ref);
	void pauseGame();
	void update(float dt);
};
