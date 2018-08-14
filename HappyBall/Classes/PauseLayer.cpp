#include "PauseLayer.h"
#include "SetingLayer.h"
#include "GameScene.h"
#include "GameStatus.h"
#include "GameLayer.h"
USING_NS_CC;

bool PauseLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto mainLayerBg = Sprite::create("main_layer_bg.png");
	mainLayerBg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(mainLayerBg);	

	auto set = SetingLayer::create(2);
	addChild(set);

	auto box = Sprite::create("pause_box.png");
	box->setPosition(visibleSize.width / 2, visibleSize.height / 2-80);
	addChild(box);

	auto gohome = MenuItemImage::create("pause_home.png", "pause_home.png", CC_CALLBACK_0(PauseLayer::goHome,this));
	auto restart = MenuItemImage::create("pause_restart.png", "pause_restart.png", CC_CALLBACK_0(PauseLayer::reStart, this));
	auto conti = MenuItemImage::create("pause_continue.png", "pause_continue.png", CC_CALLBACK_0(PauseLayer::continueGame, this));
	auto menu = Menu::create(gohome, restart, conti, NULL);
	menu->alignItemsVerticallyWithPadding(80);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 100);
	addChild(menu);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *touch, Event *unused_event) {
		return true;
	};
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}


void PauseLayer::goHome() {
	GameStatus::getInstance()->setScore(0);
	GameStatus::getInstance()->setLevel(0);
	Director::getInstance()->replaceScene(TransitionFade::create(0.3f, GameScene::create()));
}

void PauseLayer::reStart() {
	//Çå³þÊý¾Ý
	GameStatus::getInstance()->setScore(0);
	GameStatus::getInstance()->setLevel(0);
	((GameLayer*)(getParent()->getParent()))->resumeGame();
	removeFromParent();
}

void PauseLayer::continueGame() {
	removeFromParent();
}