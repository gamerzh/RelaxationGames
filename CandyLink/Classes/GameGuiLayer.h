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
	CCLabelAtlas*label;
	CCLabelAtlas*label1;
	CCLabelAtlas*label2;
	CCLabelAtlas* Ascore;
	int count=0;

	LabelAtlas* label_timer;
	float    pTime;
	void updateTime(float delta);//һ��ˢ��һ��
	Size visibleSize ;
	Vec2 origin;
	void updateBtnInfo();
};
#endif