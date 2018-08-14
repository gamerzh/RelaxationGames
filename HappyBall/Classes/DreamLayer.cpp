#include "DreamLayer.h"
#include "Dream.h"
#include "UserData.h"
#include "GameStatus.h"
#include "GameLayer.h"
#include "DreamSecond.h"
#include "DreamEvent.h"
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
	if (id == 9) {
		y->setTexture("dream/ten.png");
	}
	y->setScale(0.8);
	y->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
	y->setPosition(visiblieSize.width-5 ,5);
	addChild(y);


	auto close = MenuItemImage::create("dream/close.png", "dream/close.png", CC_CALLBACK_1(DreamLayer::closeView, this));
	close->setOpacity(100);
	close->setTag(id);
	auto closeMenu = Menu::create(close, NULL);
	closeMenu->setPosition(visiblieSize.width / 2 + 325, visiblieSize.height / 2 + 370);
	addChild(closeMenu);

	if (id == 1) {
		Dream::getInstance()->recordEvent(jfd_1_show, jfd_1_show);
	}
	else  if (id == 2) {
		Dream::getInstance()->recordEvent(jfd_2_show, jfd_2_show);
	}
	else  if (id == 3) {
		Dream::getInstance()->recordEvent(jfd_3_show, jfd_3_show);
	}
	else  if (id == 5) {
		Dream::getInstance()->recordEvent(jfd_5_show, jfd_5_show);
	}
	else  if (id == 6) {
		Dream::getInstance()->recordEvent(jfd_6_show, jfd_6_show);
	}
	else  if (id == 7) {
		Dream::getInstance()->recordEvent(jfd_7_show, jfd_7_show);
	}
	else  if (id == 9) {
		Dream::getInstance()->recordEvent(jfd_9_show, jfd_9_show);
	}
	else  if (id == 10) {
		//添加一个取消按钮
		confirmMenu->setEnabled(false);
		confirmSprite->setVisible(false);
		auto confirm = MenuItemImage::create("dream/confirm.png", "dream/confirm.png",
			CC_CALLBACK_1(DreamLayer::doConfirmEvent, this));
		confirm->setTag(id);
		auto close = MenuItemImage::create("dream/second/second_cancel.png", "dream/second/second_cancel.png",
			CC_CALLBACK_1(DreamLayer::doConfirmEvent, this));
		close->setTag(id);
		auto nineMenu = Menu::create(confirm, close, NULL);
		nineMenu->setPosition(visiblieSize.width / 2, visiblieSize.height / 2 - 150);
		nineMenu->alignItemsHorizontallyWithPadding(100);
		addChild(nineMenu);
		Dream::getInstance()->recordEvent(jfd_10_show, jfd_10_show);
	}
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
		box->setTexture("dream/second/second_c_6.png");
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
		Dream::getInstance()->recordEvent(jfd_1_pay, jfd_1_pay);
	}
	else if (id == 2) {
		UserData::getInstance()->setPlayerGoldNum(UserData::getInstance()->getPlayerGoldNum() + 100);
		auto node = DreamLayer::create(3);
		getParent()->addChild(node);
		Dream::getInstance()->recordEvent(jfd_2_pay, jfd_2_pay);
	}
	else if (id == 3 ) {
		Dream::getInstance()->recordEvent(jfd_3_pay, jfd_3_pay);
		UserData::getInstance()->setPlayerGoldNum(UserData::getInstance()->getPlayerGoldNum() + 100);
	}
	else if (id == 5) {
		//双倍
		Dream::getInstance()->recordEvent(jfd_5_pay, jfd_5_pay);
		GameStatus::getInstance()->setDoubleScore(true);
	}
	else if (id == 6) {
		//无敌
		Dream::getInstance()->recordEvent(jfd_6_pay, jfd_6_pay);
		GameStatus::getInstance()->setInvincible(true);
	}
	else if (id == 7) {
		//复活
		Dream::getInstance()->recordEvent(jfd_7_pay, jfd_7_pay);
		GameStatus::getInstance()->setResurgence(true);
	}
	else if (id == 9) {
		Dream::getInstance()->recordEvent(jfd_9_pay, jfd_9_pay);
		UserData::getInstance()->setPlayerGoldNum(UserData::getInstance()->getPlayerGoldNum() + 500);
	}
	else if (id == 10) {
		Dream::getInstance()->recordEvent(jfd_10_pay, jfd_10_pay);
		UserData::getInstance()->setPlayerGoldNum(UserData::getInstance()->getPlayerGoldNum() + 100);
	}
	removeFromParent();
}

void DreamLayer::closeView(Ref* ref) {
	MenuItemImage* tem = (MenuItemImage*)ref;
	int id = tem->getTag();
	if (id == 1) {
		Dream::getInstance()->recordEvent(jfd_1_close, jfd_1_close);
		auto node = DreamLayer::create(2);
		getParent()->addChild(node);
	}
	else if (id == 2) {
		Dream::getInstance()->recordEvent(jfd_2_close, jfd_2_close);
		auto node = DreamLayer::create(3);
		getParent()->addChild(node);
	}
	else if (id == 3) {
		Dream::getInstance()->recordEvent(jfd_3_close, jfd_3_close);
	}
	else if (id == 5) {
		Dream::getInstance()->recordEvent(jfd_5_close, jfd_5_close);
	}
	else if (id == 6) {
		Dream::getInstance()->recordEvent(jfd_6_close, jfd_6_close);
	}
	else if (id == 7) {
		//复活
		Dream::getInstance()->recordEvent(jfd_7_close, jfd_7_close);
		((GameLayer*)getParent())->showGameOver();
	}
	else if (id == 9) {
		Dream::getInstance()->recordEvent(jfd_9_close, jfd_9_close);
	}
	else if (id == 10) {
		//退出
		Dream::getInstance()->quitGame();
		Dream::getInstance()->recordEvent(jfd_10_close, jfd_10_close);
	}
	removeFromParent();
}

void DreamLayer::doSecondConfirmEvent(Ref* ref) {
	MenuItemImage* tem = (MenuItemImage*)ref;
	int id = tem->getTag();
	if (id == 6) {
		//复活
		Dream::getInstance()->recordEvent(jfd_6_pay, jfd_6_pay);
	}
	else if (id == 7) {
		Dream::getInstance()->recordEvent(jfd_7_pay, jfd_7_pay);
	}
	auto sec = DreamSecond::create(id);
	addChild(sec);
}
void DreamLayer::closeSecondView(Ref* ref) {
	MenuItemImage* tem = (MenuItemImage*)ref;
	int id = tem->getTag();
	if (id == 7) {
		//复活
		Dream::getInstance()->recordEvent(jfd_7_close, jfd_7_close);
		((GameLayer*)getParent())->showGameOver();
	}
	else if (id == 6) {
		Dream::getInstance()->recordEvent(jfd_6_close, jfd_6_close);
	}
	removeFromParent();
}
