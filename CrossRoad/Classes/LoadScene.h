#pragma once
#include "cocos2d.h"
USING_NS_CC;

class LoadScene : public Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoadScene);
private:
	void loadView();
	void showChangView();
	void startGame();
};