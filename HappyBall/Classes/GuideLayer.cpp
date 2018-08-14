#include "GuideLayer.h"
#include "Dream.h"
#include "DreamEvent.h"
#include "DreamLayer.h"
USING_NS_CC;

bool GuideLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	auto bg = Sprite::create("yd.png");
	bg->setPosition(360,640);
	addChild(bg);
	auto gold = Sprite::create("gold_100.png");
	gold->setPosition(360, 155);
	addChild(gold);
	auto menuImg = MenuItemImage::create("finish.png", "finish.png", CC_CALLBACK_0(GuideLayer::finishGuide,this));
	auto quan = MenuItem::create(CC_CALLBACK_0(GuideLayer::finishGuide, this));
	quan->setContentSize(Size(720,1280));
	auto menu = Menu::create(menuImg, quan,NULL);
	menu->setPosition(360, 70);
	addChild(menu);

	if (!Dream::getInstance()->getDreamTimes()) {
		auto y = Sprite::create("dream/twenty.png");
		y->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
		y->setScale(0.8);
		y->setPosition(715, 5);
		addChild(y);
	}
	Dream::getInstance()->recordEvent(jfd_4_show, jfd_4_show);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *touch, Event *unused_event) {
		return true;
	};
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void GuideLayer::finishGuide() {
	if (!Dream::getInstance()->getDreamTimes()) {
		Dream::getInstance()->recordEvent(jfd_4_pay, jfd_4_pay);
		Dream::getInstance()->requestEvent(4);
		DreamLayer* login = DreamLayer::create(5);
		getParent()->addChild(login);
	}
	removeFromParent();
}