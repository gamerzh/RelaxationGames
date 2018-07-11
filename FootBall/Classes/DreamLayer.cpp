#include "DreamLayer.h"
#include "Dream.h"
#include "UserData.h"
#include "GameStatus.h"
#include "GameLayer.h"
#include "DreamSecond.h"
USING_NS_CC;

//二次情况下只有复活和神秘礼包

DreamLayer* DreamLayer::create(int dreamId) {
	auto dre = new DreamLayer();
	if (dre && dre->init(dreamId)) {
		dre->autorelease();
		return dre;
	}
	else {
		CC_SAFE_DELETE(dre);
		return nullptr;
	}
}

bool DreamLayer::init(int dreamId) {
	if (!Layer::init()) {
		return false;
	}
	if (Dream::getInstance()->getDreamTimes()) {
		 loadSecondContent(dreamId);//二次的界面
	}
	else {
		loadContent(dreamId);
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *touch, Event *unused_event) {
		return true;
	};
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void DreamLayer::loadContent(int id) {
	auto visiblieSize = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("dream/dream_bg.png");
	bg->setPosition(visiblieSize.width / 2, visiblieSize.height / 2);
	addChild(bg);
	auto box = Sprite::create(getFileNameById(id));
	box->setPosition(visiblieSize.width / 2, visiblieSize.height / 2 + 100);
	addChild(box);

	auto confirmSprite = Sprite::create("dream/confirm.png");
	confirmSprite->setPosition(visiblieSize.width / 2, visiblieSize.height / 2 - 150);
	addChild(confirmSprite);
	auto confirm = MenuItem::create(CC_CALLBACK_1(DreamLayer::doConfirmEvent,this));
	confirm->setTag(id);
	confirm->setContentSize(Size(visiblieSize.width,visiblieSize.height));
	auto confirmMenu = Menu::create(confirm, NULL);
	confirmMenu->setPosition(visiblieSize.width/2, visiblieSize.height / 2);
	addChild(confirmMenu);

	auto y = Sprite::create("dream/twenty.png");
	y->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
	y->setPosition(visiblieSize.width ,5);
	addChild(y);

	auto close = MenuItemImage::create("dream/close.png", "dream/close.png", CC_CALLBACK_1(DreamLayer::closeView, this));
	close->setTag(id);
	auto closeMenu = Menu::create(close, NULL);
	closeMenu->setPosition(visiblieSize.width / 2 + 300, visiblieSize.height / 2 + 320);
	addChild(closeMenu);
}

void DreamLayer::loadSecondContent(int id) {
	auto visiblieSize = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("dream/dream_bg.png");
	bg->setPosition(visiblieSize.width / 2, visiblieSize.height / 2);
	addChild(bg);
	auto box = Sprite::create();
	if (id == 7) {
		box->setTexture("dream/second/second_c_7.png");
	}
	else{
		box->setTexture("dream/second/second_c_7.png");
	}
	box->setPosition(visiblieSize.width / 2, visiblieSize.height / 2 + 40);
	addChild(box);

	auto confirm = MenuItemImage::create("dream/second/second_confirm.png", "dream/second/second_confirm.png", CC_CALLBACK_1(DreamLayer::doSecondConfirmEvent, this));
	confirm->setTag(id);
	auto close = MenuItemImage::create("dream/second/second_cancel.png", "dream/second/second_cancel.png", CC_CALLBACK_1(DreamLayer::closeSecondView, this));
	close->setTag(id);
	auto secondMenu = Menu::create(confirm,close, NULL);
	secondMenu->setPosition(visiblieSize.width / 2 , visiblieSize.height / 2 - 300);
	secondMenu->alignItemsHorizontallyWithPadding(100);
	addChild(secondMenu);
}

std::string DreamLayer::getFileNameById(int id) {
	return StringUtils::format("dream/dream_c_%d.png", id);
}

void DreamLayer::doConfirmEvent(Ref* ref) {
	MenuItem* tem = (MenuItem*)ref;
	int id = tem->getTag();
	//按照编号处理
	Dream::getInstance()->requestEvent(id);
	if (id == 1) {
		//玩家确认金币加100
		UserData::getInstance()->setPlayerGoldNum(UserData::getInstance()->getPlayerGoldNum()+100);
		auto node = DreamLayer::create(2);
		getParent()->addChild(node);
	}
	else if (id == 2) {
		UserData::getInstance()->setPlayerGoldNum(UserData::getInstance()->getPlayerGoldNum() + 100);
		auto node = DreamLayer::create(3);
		getParent()->addChild(node);
	}
	else if (id == 3 || id == 9 || id == 10) {
		UserData::getInstance()->setPlayerGoldNum(UserData::getInstance()->getPlayerGoldNum() + 100);
	}
	else if (id == 5) {
		//双倍
//        GameStatus::getInstance()->setDoubleScore(true);
	}
	else if (id == 6) {
		//无敌
//        GameStatus::getInstance()->setInvincible(true);
	}
	else if (id == 7) {
		//复活
//        GameStatus::getInstance()->setResurgence(true);
	}
	removeFromParent();
}

void DreamLayer::closeView(Ref* ref) {
	MenuItemImage* tem = (MenuItemImage*)ref;
	int id = tem->getTag();
	if (id == 1) {
		auto node = DreamLayer::create(2);
		getParent()->addChild(node);
	}
	else if (id == 2) {
		auto node = DreamLayer::create(3);
		getParent()->addChild(node);
	}
	else if (id == 7) {
		//复活
//        ((GameLayer*)getParent())->showGameOver();
	}
	removeFromParent();
}

void DreamLayer::doSecondConfirmEvent(Ref* ref) {
	MenuItemImage* tem = (MenuItemImage*)ref;
	int id = tem->getTag();
	auto sec = DreamSecond::create(id);
	addChild(sec);
}
void DreamLayer::closeSecondView(Ref* ref) {
	MenuItemImage* tem = (MenuItemImage*)ref;
	int id = tem->getTag();
	if (id == 7) {
		//复活
//        ((GameLayer*)getParent())->showGameOver();
	}
	removeFromParent();
}
