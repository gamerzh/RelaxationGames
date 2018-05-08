#include "GameOver.h"
#include "GameScene.h"

bool GameOver::init() {
	if (!Layer::init()) {
		return false;
	}
	auto win = Director::getInstance()->getWinSize();

	auto swa = MenuItem::create();
	swa->setContentSize(Size(win.width,win.height));
	auto swam = Menu::create(swa, NULL);
	addChild(swam);

	auto bg0 = LayerColor::create(Color4B(0, 0, 0, 204), win.width, win.height);
	addChild(bg0);

	auto hint = Label::createWithSystemFont("Game Over","Arial",30);
	hint->setTextColor(Color4B::WHITE);
	addChild(hint);
	hint->setPosition(win.width/2,win.height/2);

	auto closeImage = MenuItemImage::create("close_btn_1.png", "close_btn_1.png", CC_CALLBACK_0(GameOver::closeView, this));
	auto closeMenu = Menu::create(closeImage, NULL);
	closeMenu->setPosition(win.width *0.9, win.height *0.9);
	addChild(closeMenu);

	return true;
}

void GameOver::closeView() {
	removeFromParent();
	Director::getInstance()->replaceScene(GameScene::createScene());
}