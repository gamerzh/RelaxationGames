#include "ResultLayer.h"
#include "GameScene.h"
#include "UserData.h"
#include "GameStatus.h"
#include "GameLayer.h"
#include "DreamEvent.h"
#include "Dream.h"
USING_NS_CC;

bool ResultLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto mainLayerBg = Sprite::create("main_layer_bg.png");
	mainLayerBg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(mainLayerBg);

	auto box = Sprite::create("result_box.png");
	box->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 40);
	addChild(box);

	auto socre = LabelAtlas::create(StringUtils::format("%d", GameStatus::getInstance()->getScore()), "best_record_num.png", 64, 70, '0');
	socre->setAnchorPoint(Point::ANCHOR_MIDDLE);
	socre->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 150);
	addChild(socre);

	auto history = LabelAtlas::create(StringUtils::format("%d", UserData::getInstance()->getBestRecord()), "result_record.png", 18, 34, '0');
	history->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	history->setPosition(visibleSize.width / 2 - 35, visibleSize.height / 2 - 5);
	addChild(history);

	auto gold = LabelAtlas::create(StringUtils::format("%d", GameStatus::getInstance()->getScore()), "result_gold.png", 18, 34, '0');
	gold->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	gold->setPosition(visibleSize.width / 2 - 35, visibleSize.height / 2 - 60);
	addChild(gold);

	UserData::getInstance()->setPlayerGoldNum(UserData::getInstance()->getPlayerGoldNum() + GameStatus::getInstance()->getScore());

	//auto gohome = MenuItemImage::create("result_back.png", "result_back.png", CC_CALLBACK_0(ResultLayer::goHome, this));
	auto restart = MenuItemImage::create("result_continue.png", "result_continue.png", CC_CALLBACK_0(ResultLayer::goHome, this));
	auto menu = Menu::create(restart, NULL);
	menu->alignItemsHorizontallyWithPadding(60);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 230);
	addChild(menu);

	GameStatus::getInstance()->setGameStart(false);

	if (!Dream::getInstance()->getDreamTimes()) {
		auto y = Sprite::create("dream/twenty.png");
		y->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
		y->setScale(0.8);
		y->setPosition(715, 5);
		addChild(y);
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *touch, Event *unused_event) {
		return true;
	};
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Dream::getInstance()->recordEvent(jfd_8_show, jfd_8_show);

	return true;
}

void ResultLayer::goHome() {
	GameStatus::getInstance()->setScore(0);
	GameStatus::getInstance()->setLevel(0);
	if (!Dream::getInstance()->getDreamTimes()) {
		Dream::getInstance()->recordEvent(jfd_8_pay, jfd_8_pay);
		Dream::getInstance()->requestEvent(8);
	}
	Director::getInstance()->replaceScene(TransitionFade::create(0.3f, GameScene::create()));
}

void ResultLayer::reStart() {
	//Çå³þÊý¾Ý
	if (!Dream::getInstance()->getDreamTimes()) {
		Dream::getInstance()->recordEvent(jfd_8_pay, jfd_8_pay);
		Dream::getInstance()->requestEvent(8);
	}
	GameStatus::getInstance()->setScore(0);
	GameStatus::getInstance()->setLevel(0);
	GameStatus::getInstance()->setGameStart(true);
	((GameLayer*)getParent())->resumeGame();
	removeFromParent();
}
