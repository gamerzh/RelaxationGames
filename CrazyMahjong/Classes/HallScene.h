//´óÌü
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Room.h"
USING_NS_CC;
using namespace ui;
class HallScene :public Layer
{
public:
	static Scene* createScene();

	CREATE_FUNC(HallScene);
	
	void hide();
	void show();
private:
	void addCoinCallback(Ref* pSender, TouchEventType type);
	void BtnCallback(Ref*psend, TouchEventType type);
	void RoomCallback(Ref*psend, TouchEventType type);
	void EnterRoom(ROOM roomid);
	bool init();
	void update(float delta);
	bool showVipAddCoin();
private:
	LabelTTF* userCoin;

	Node*left;
	Node*right;
};


