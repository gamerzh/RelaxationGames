#include "MainLayer.h"
#include "SetingLayer.h"
#include "UserData.h"
#include "DreamLayer.h"
#include "Dream.h"
#include "DreamEvent.h"
#include "GameStatus.h"
#include "GuideLayer.h"
USING_NS_CC;

bool MainLayer::init() {

	if (!Layer::init()) {
		return false;
	}
	GameStatus::getInstance()->setGameStart(false);
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto mainLayerBg = Sprite::create("main_layer_bg.png");
	mainLayerBg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(mainLayerBg);
	auto gameName = Sprite::create("game_name.png");
	gameName->setPosition(visibleSize.width / 2, visibleSize.height / 2+240);
	addChild(gameName);
	
	

	auto bestRecord = Sprite::create("best_record.png");
	bestRecord->setPosition(visibleSize.width / 2, visibleSize.height / 2+20);
	addChild(bestRecord);

	auto bestRecordNum = LabelAtlas::create(StringUtils::format("%d",UserData::getInstance()->getBestRecord()), "best_record_num.png", 64, 70, '0');
	bestRecordNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	bestRecordNum->setPosition(visibleSize.width / 2, visibleSize.height / 2 -120);
	addChild(bestRecordNum);

	auto startImg = MenuItemImage::create("start_btn.png", "start_btn.png",CC_CALLBACK_0(MainLayer::startGame,this));
	auto startMenu = Menu::create(startImg,NULL);
	startMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 320);
	addChild(startMenu);

	auto set = SetingLayer::create(0);
	addChild(set);

	if (!Dream::getInstance()->getDreamTimes()) {
		auto dreamLayer = DreamLayer::create(1);
		addChild(dreamLayer);
	}


	Dream::getInstance()->recordEvent(main_show, main_show);
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e) {
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK: {
			if (!Dream::getInstance()->getDreamTimes()) {
				if (NULL == getChildByTag(1025)) {
					DreamLayer* nod = DreamLayer::create(10);
					nod->setTag(1025);
					addChild(nod,10);
				}
			}
			else {
				Dream::getInstance()->quitGame();
			}
			break;
		}
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = [=](Touch *touch, Event *unused_event) {
		return true;
	};
	listener2->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2,this);

	return true;
}

void MainLayer::startGame() {
	GameStatus::getInstance()->setGameStart(true);
	if (UserData::getInstance()->getShowgGuide()) {
		if (!Dream::getInstance()->getDreamTimes()) {
			DreamLayer* login = DreamLayer::create(5);
			getParent()->addChild(login, 1);
		}
	}
	else {
		//展示引导界面
		auto guide = GuideLayer::create();
		getParent()->addChild(guide, 1);
		UserData::getInstance()->setShowGuide(true);
	}
	removeFromParentAndCleanup(true);
}

