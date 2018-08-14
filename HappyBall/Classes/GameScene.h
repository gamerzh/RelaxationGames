#pragma once
#include "cocos2d.h"

class GameScene : public cocos2d::Scene {
public:
	virtual bool init();
	CREATE_FUNC(GameScene);
	void onEnter();
private:
	void addPhysicsToScene();
	void addLayerToScene();
};