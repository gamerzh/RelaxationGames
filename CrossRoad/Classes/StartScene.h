#pragma once
#include "cocos2d.h"
USING_NS_CC;

class StartScene : public Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(StartScene);
private:
	void loadView();
	void startGame();
	void soundManage(Ref* ref);
	void changePlayerModle();
	void updateSound(MenuItemImage* imge);
	void showDreamLogin();
	void showDreamDay();
	void showDreamHappy();
	void update(float dt);
};