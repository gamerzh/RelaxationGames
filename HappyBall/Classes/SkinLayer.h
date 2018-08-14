#pragma once
#include "cocos2d.h"

#define SKIN_0 "0"
#define SKIN_1 "1"
#define SKIN_2 "2"
#define SKIN_3 "3"
#define SKIN_4 "4"
#define SKIN_5 "5"
#define SKIN_6 "6"

#define SKIN_BTN_0 100
#define SKIN_BTN_1 101
#define SKIN_BTN_2 102
#define SKIN_BTN_3 103
#define SKIN_BTN_4 104
#define SKIN_BTN_5 105
#define SKIN_BTN_6 106

class SkinLayer : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(SkinLayer);
private:
	cocos2d::MenuItemImage* skinBtn_0;
	cocos2d::MenuItemImage* skinBtn_1;
	cocos2d::MenuItemImage* skinBtn_2;
	cocos2d::MenuItemImage* skinBtn_3;
	cocos2d::MenuItemImage* skinBtn_4;
	cocos2d::MenuItemImage* skinBtn_5;
	cocos2d::MenuItemImage* skinBtn_6;

	void closeView();
	void changeSkin(cocos2d::Ref* ref);
	std::string getSkinIdByTag(int tag);
	int getPriceByName(std::string name);
	void updateSkinState(std::string name);
	void updateButtonState();
};