#include "SetingLayer.h"
#include "SkinLayer.h"
#include "PauseLayer.h"
#include "UserData.h"
#include "Audio.h"
#include "GameLayer.h"
USING_NS_CC;

SetingLayer* SetingLayer::create(int style) {
	SetingLayer* set = new SetingLayer();
	if (set && set->init(style)) {
		set->autorelease();
		return set;
	}
	else {
		CC_SAFE_DELETE(set);
		return nullptr;
	}
}

bool SetingLayer::init(int style) {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	//选中状态精灵
	auto musicOnSpr = Sprite::create("sound_on.png");
	//未选中状态精灵
	auto musicOffSpr = Sprite::create("sound_off.png");
	auto musicOn = MenuItemSprite::create(musicOnSpr, musicOnSpr);
	auto musicOff = MenuItemSprite::create(musicOffSpr, musicOffSpr);
	//创建MenuItemToggle，第一个参数是回调函数 后面依次是要显示的MenuItem，最后必须为NULL
	musicItemToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetingLayer::soundMenuCallBack, this), musicOn, musicOff, NULL);
	if (UserData::getInstance()->getMusicStatus() == 0) {
		musicItemToggle->setSelectedIndex(1);
	}
	auto menu = Menu::create(musicItemToggle, NULL);
	menu->setPosition(80, visibleSize.height - 100);
	menu->setVisible(false);
	this->addChild(menu);

	auto goldBg = Sprite::create("gold_bg.png");
	goldBg->setPosition(visibleSize.width / 2, visibleSize.height - 100);
	goldBg->setVisible(false);
	addChild(goldBg);

	auto goldNum = LabelAtlas::create(StringUtils::format("%d",UserData::getInstance()->getPlayerGoldNum()), "gold_num.png", 39, 46, '0');
	goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	goldNum->setTag(1024);
	goldNum->setPosition(visibleSize.width / 2 + 30, visibleSize.height - 100);
	goldNum->setVisible(false);
	addChild(goldNum);

	auto skinImg = MenuItemImage::create("skin_btn.png", "skin_btn.png", CC_CALLBACK_0(SetingLayer::showSkinLayer, this));
	auto skinMenu = Menu::create(skinImg, NULL);
	skinMenu->setPosition(visibleSize.width - 80, visibleSize.height - 100);
	skinMenu->setVisible(false);
	addChild(skinMenu);

	auto pauseImg = MenuItemImage::create("pause_btn.png", "pause_btn.png", CC_CALLBACK_0(SetingLayer::showPauseLayer, this));
	auto pauseMenu = Menu::create(pauseImg, NULL);
	pauseMenu->setPosition(visibleSize.width - 80, visibleSize.height - 100);
	pauseMenu->setVisible(false);
	addChild(pauseMenu);

	if (style == 0) {
		//主界面的ui显示类型
		menu->setVisible(true);
		goldNum->setVisible(true);
		goldBg->setVisible(true);
		skinMenu->setVisible(true);
	}else if(style == 1){
		//游戏界面的ui显示类型
		menu->setVisible(true);
		pauseMenu->setVisible(true);
	}
	else if (style == 2) {
		//暂停界面的ui显示类型
		menu->setVisible(true);
		//pauseMenu->setVisible(true);
		goldBg->setVisible(true);
		goldNum->setVisible(true);
	}
	scheduleUpdate();
	return true;
}

void SetingLayer::soundMenuCallBack(cocos2d::Ref* ref) {
	//TODO 音效控制
	auto item = (MenuItemToggle*)ref;
	int in = item->getSelectedIndex();
	if (in == 0) {
		Audio::getInstance()->controllSound(true);
	}
	else {
		Audio::getInstance()->controllSound(false);
	}
	//item->setSelectedIndex(in);
}

void SetingLayer::showSkinLayer() {
	auto skin = SkinLayer::create();
	addChild(skin);
}

void SetingLayer::showPauseLayer() {
	auto pause = PauseLayer::create();
	addChild(pause);
}

void SetingLayer::updateHeroSkin() {
	//((GameLayer*)this->getParent())->updateHeroSkin();
}

void SetingLayer::update(float dt) {
	if (NULL != getChildByTag(1024) && getChildByTag(1024)->isVisible()) {
		((LabelAtlas*)getChildByTag(1024))->setString(StringUtils::format("%d", UserData::getInstance()->getPlayerGoldNum()));
	}
	if (UserData::getInstance()->getMusicStatus() == 0) {
		musicItemToggle->setSelectedIndex(1);
	}
	else {
		musicItemToggle->setSelectedIndex(0);
	}
}