#include "PauseLayer.h"
#include "LobbyScene.h"
#include "GameScene.h"
USING_NS_CC;

bool PauseLayer::init(){
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto pause_bg = Sprite::create("pause_bg.png");
	pause_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(pause_bg);

	auto img1 = MenuItemImage::create("pause_con.png", "pause_con.png",CC_CALLBACK_0(PauseLayer::continuePlay, this));
	auto img2 = MenuItemImage::create("pause_re.png", "pause_re.png",CC_CALLBACK_0(PauseLayer::reStartGame, this));
	auto img3 = MenuItemImage::create("pause_lobby.png", "pause_lobby.png",CC_CALLBACK_0(PauseLayer::gobackLobby, this));
	auto menu = Menu::create(img1, img2, img3,NULL);
	menu->alignItemsVerticallyWithPadding(15);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2-20);
	addChild(menu);
    Director::getInstance()->pause();
	return true;
}

void PauseLayer::continuePlay(){
    Director::getInstance()->resume();
    removeFromParent();
}

void PauseLayer::reStartGame(){
    Director::getInstance()->resume();
    getParent()->getParent()->getParent()->cleanup();
    Director::getInstance()->replaceScene(GameScene::create());
}

void PauseLayer::gobackLobby(){
    Director::getInstance()->resume();
    Director::getInstance()->replaceScene(LobbyScene::create());
}
