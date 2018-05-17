#include "GuideLayer.h"

bool GuideLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	auto win = Director::getInstance()->getWinSize();
	auto guide = Sprite::create("guide_layer.png");
	guide->setPosition(win.width/2,win.height/2);
	addChild(guide);


	auto conti = MenuItemImage::create("play_continue.png", "play_continue.png", CC_CALLBACK_0(GuideLayer::closeView, this));
	auto boxMenu = Menu::create( conti, NULL);
	boxMenu->setPosition(win.width / 2, win.height / 4);
	addChild(boxMenu);
	return true;
}

void GuideLayer::closeView() {
	removeFromParent();
}