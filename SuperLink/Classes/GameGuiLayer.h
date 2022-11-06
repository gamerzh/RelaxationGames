#ifndef __GAME_GUI_LAYER_H__
#define __GAME_GUI_LAYER_H__
#include "cocos2d.h"
#define wSize Director::getInstance()->getVisibleSize()
USING_NS_CC;

class GameGuiLayer : public Node{
public:
	static GameGuiLayer*getInstance();
	virtual bool init();
	CREATE_FUNC(GameGuiLayer);
	void updateScore();
	void showWaring(float dt);
private:
	static GameGuiLayer*_instance;
	void pauseGame();
	void update(float dt);
	void addTimeBtn();
	void helpTip();
	void refreshBtn();
	Sprite* notime;
	ProgressTimer* right;
	LabelTTF*label;
	LabelTTF*label1;
	LabelTTF*label2;
	CCLabelAtlas* Ascore;
	int count=0;

	LabelTTF* label_timer;
	float    pTime;
	void updateTime(float delta);//一秒刷新一次
	Size visibleSize ;
	Vec2 origin;
	void updateBtnInfo();
};
#endif