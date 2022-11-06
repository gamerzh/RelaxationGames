#pragma once
#include "cocos2d.h"
#include "RoleShow.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

struct RoleListNode
{
	RoleShow* spRole;
	Sprite* spHead;
	int _index;
	int _posIndex;
	RoleListNode* _late;
};


class RolePanel : public Node
{
public:
	CREATE_FUNC(RolePanel);
	void hide();
	void show();
private:
	RolePanel();
	bool init();
	void createList();
	void createRoleChoose();
	void createHeadChoose();
	void updateRoleShow(int curindex);
	void createCommonUI();
	void BtnCallback(Ref*psend, TouchEventType type);
	bool onTouchBegin(Touch*touch, Event*event);
private:
	void getIndexBy1_12(int &index);
	int getPrice(int index);
private:
	RoleListNode* roleNode=nullptr;
	Vec2 rolePos[13];
	int _curindex = 1;
	Node*left;
	Node*right;
};
