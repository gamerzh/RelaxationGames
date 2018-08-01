#include "StartLayer.h"
#include "DreamLayer.h"
USING_NS_CC;

bool StartLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create("start_bg.png");
	bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(bg);

	auto logo = Sprite::create("logo.png");
	logo->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(logo);

	auto btn = MenuItemImage::create("start_btn.png", "start_btn.png",CC_CALLBACK_0(StartLayer::startGame,this));
	auto menu = Menu::create(btn,NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2-260);
	addChild(menu);

    auto dream1 = DreamLayer::create(1);
    addChild(dream1);
    
	return true;
}

void StartLayer::startGame() {
	removeFromParent();
}
