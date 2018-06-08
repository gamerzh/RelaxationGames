#include "FightLayer.h"
USING_NS_CC;

//FightLayer* FightLayer::create()
//{
//	FightLayer *ret = new FightLayer();
//	if (ret && ret->init())
//	{
//		ret->autorelease();
//		return ret;
//	}
//	CC_SAFE_DELETE(ret);
//	return nullptr;
//}


bool FightLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto back = LayerColor::create(Color4B(255,255,255,255), visibleSize.width,visibleSize.height);
	addChild(back, -1);

	img = MenuItemImage::create("play-circle-o.png", "play-circle-o.png");
	auto menu = Menu::create(img, NULL);
	menu->setPosition(visibleSize.width/2,visibleSize.height/6);
	addChild(menu);

	return true;
}

void FightLayer::setMenuCallback(const cocos2d::ccMenuCallback& back) {
	if (nullptr != img) {
		img->setCallback(back);
	}
}