#pragma once
#include "cocos2d.h"

class Setting :public cocos2d::Layer {
	//
public:
	virtual bool init();
	CREATE_FUNC(Setting);
private:
	float gameTime = 60;//”Œœ∑ ±º‰
	float passTime = 0;
	const float timestep = 0.1f;
	void loadView();
	void update(float dt);
};