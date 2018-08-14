#pragma once
#include "cocos2d.h"

class ResultScene : public cocos2d::Scene {
public:
	virtual bool init();
	CREATE_FUNC(ResultScene);
private:
	void addLayerToScene();
};