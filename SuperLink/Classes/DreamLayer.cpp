#include "DreamLayer.h"
USING_NS_CC;

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
	loadContent(dreamId);
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


std::string DreamLayer::getFileNameById(int id) {
	return StringUtils::format("dream/dream_c_%d.png", id);
}

void DreamLayer::doConfirmEvent(Ref* ref) {
	MenuItem* tem = (MenuItem*)ref;
	int id = tem->getTag();
	removeFromParent();
}

void DreamLayer::closeView(Ref* ref) {
	MenuItemImage* tem = (MenuItemImage*)ref;
	int id = tem->getTag();
	removeFromParent();
}

