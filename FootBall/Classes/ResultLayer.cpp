#include "ResultLayer.h"
USING_NS_CC;

ResultLayer* ResultLayer::create(bool win) {
	auto ret = new ResultLayer();
	if (ret && ret->init(win)) {
		ret->autorelease();
		return ret;
	}
	else {
		CC_SAFE_DELETE(ret);
		return NULL;
	}
}

bool ResultLayer::init(bool win) {
	if (!Layer::init()) {
		return false;
	}

	auto black = LayerColor::create(Color4B(0, 0, 0, 100), 1280, 720);
	addChild(black);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create();
	bg->setPosition(visibleSize.width/2, visibleSize.height/2+70);
	addChild(bg);
	if (win) {
		bg->setTexture("sl.png");
	}
	else {
		bg->setTexture("sb.png");
	}

	auto img1 = MenuItemImage::create("result_lobby.png","result_lobby.png",CC_CALLBACK_0(ResultLayer::continueGame, this));
	auto img2 = MenuItemImage::create("result_con.png", "result_con.png",CC_CALLBACK_0(ResultLayer::gotoLobby, this));
	auto menu = Menu::create(img1, img2,NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2-180);
	menu->alignItemsHorizontallyWithPadding(50);
	addChild(menu);

	return true;
}

void ResultLayer::continueGame(){
    
}

void ResultLayer::gotoLobby(){
    
}
